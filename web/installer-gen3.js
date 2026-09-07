const log = (message) => {
  const element = document.getElementById('log');
  element.style.display = 'block';
  element.textContent += message + '\n';
  element.scrollTop = element.scrollHeight;
};

const supported = 'serial' in navigator;
let port;
let reader;
let writer;
let lineBuf = '';
let serialBusy = false;
let serialClosing = false;

function setConnectedUi(connected) {
  document.getElementById('full').disabled = !connected || serialBusy;
  document.getElementById('connect').disabled = connected || serialBusy || !supported;
}

if (!supported) {
  document.getElementById('unsupported').style.display = 'block';
  setConnectedUi(false);
}

const bounded = (promise, timeoutMs = 1500) => Promise.race([
  Promise.resolve(promise).catch(() => undefined),
  new Promise((resolve) => setTimeout(resolve, timeoutMs))
]);

async function disconnectBoard(message) {
  if (serialClosing) return;
  serialClosing = true;
  const oldReader = reader;
  const oldWriter = writer;
  const oldPort = port;
  reader = writer = port = undefined;
  lineBuf = '';
  setConnectedUi(false);
  try {
    if (oldReader) {
      await bounded(oldReader.cancel('TamaPoke serial connection closed'));
      try { oldReader.releaseLock(); } catch (_) {}
    }
    if (oldWriter) {
      await bounded(oldWriter.abort('TamaPoke serial connection closed'));
      try { oldWriter.releaseLock(); } catch (_) {}
    }
    if (oldPort) await bounded(oldPort.close());
  } finally {
    serialClosing = false;
    if (message) log(message);
  }
}

async function readLine(timeoutMs = 6000) {
  const deadline = Date.now() + timeoutMs;
  while (true) {
    const newline = lineBuf.indexOf('\n');
    if (newline >= 0) {
      const line = lineBuf.slice(0, newline).trim();
      lineBuf = lineBuf.slice(newline + 1);
      return line;
    }
    const remaining = deadline - Date.now();
    if (remaining <= 0) {
      await disconnectBoard('Board response timed out. Reconnect and try again.');
      throw new Error('Board response timed out');
    }
    const activeReader = reader;
    if (!activeReader) throw new Error('Board is not connected');
    const timeoutToken = {};
    let timer;
    let result;
    try {
      result = await Promise.race([
        activeReader.read(),
        new Promise((resolve) => { timer = setTimeout(() => resolve(timeoutToken), remaining); })
      ]);
    } catch (error) {
      clearTimeout(timer);
      await disconnectBoard('USB read failed. Reconnect and try again.');
      throw new Error('USB read failed: ' + error.message);
    }
    clearTimeout(timer);
    if (result === timeoutToken) {
      await disconnectBoard('Board response timed out. Reconnect and try again.');
      throw new Error('Board response timed out');
    }
    if (result.done) {
      await disconnectBoard('Board disconnected. Connect it again to continue.');
      throw new Error('Board disconnected');
    }
    lineBuf += new TextDecoder().decode(result.value);
  }
}

async function writeSerial(data, timeoutMs = 6000) {
  const activeWriter = writer;
  if (!activeWriter) throw new Error('Board is not connected');
  const timeoutToken = {};
  let timer;
  let result;
  try {
    result = await Promise.race([
      activeWriter.write(data).then(() => true),
      new Promise((resolve) => { timer = setTimeout(() => resolve(timeoutToken), timeoutMs); })
    ]);
  } catch (error) {
    clearTimeout(timer);
    await disconnectBoard('USB write failed. Reconnect and try again.');
    throw new Error('USB write failed: ' + error.message);
  }
  clearTimeout(timer);
  if (result === timeoutToken) {
    await disconnectBoard('USB write timed out. Reconnect and try again.');
    throw new Error('USB write timed out');
  }
}

async function waitFor(token, timeoutMs = 6000) {
  const deadline = Date.now() + timeoutMs;
  while (Date.now() < deadline) {
    const line = await readLine(deadline - Date.now());
    if (line === token) return true;
    if (line === 'ERR') return false;
  }
  return false;
}

function parsePak(buffer) {
  const bytes = new Uint8Array(buffer);
  const view = new DataView(buffer);
  const decoder = new TextDecoder();
  if (bytes.length < 6 || decoder.decode(bytes.slice(0, 4)) !== 'TPAK') {
    throw new Error('invalid bundle header');
  }
  const count = view.getUint16(4, true);
  let offset = 6;
  const items = [];
  for (let index = 0; index < count; index++) {
    if (offset >= bytes.length) throw new Error('truncated bundle index');
    const nameLength = view.getUint8(offset++);
    if (offset + nameLength + 4 > bytes.length) throw new Error('truncated bundle entry');
    const name = decoder.decode(bytes.slice(offset, offset + nameLength));
    offset += nameLength;
    const size = view.getUint32(offset, true);
    offset += 4;
    items.push({ name, size });
  }
  let dataOffset = offset;
  for (const item of items) {
    if (dataOffset + item.size > bytes.length) throw new Error('truncated bundle data');
    item.data = bytes.slice(dataOffset, dataOffset + item.size);
    dataOffset += item.size;
  }
  if (dataOffset !== bytes.length) throw new Error('unexpected bundle data');
  return items;
}

const encoder = new TextEncoder();

async function sendOne(name, data) {
  await writeSerial(encoder.encode(`PUT ${name} ${data.length}\n`));
  if (!await waitFor('OK')) throw new Error('board rejected ' + name);
  for (let offset = 0; offset < data.length; offset += 2048) {
    await writeSerial(data.slice(offset, offset + 2048));
    if (!await waitFor('#')) throw new Error('transfer failed for ' + name);
  }
  if (!await waitFor('DONE', 30000)) throw new Error('board did not finish ' + name);
}

async function fetchBundle(path) {
  const response = await fetch(path);
  if (!response.ok) throw new Error(path + ': HTTP ' + response.status);
  return parsePak(await response.arrayBuffer());
}

async function loadBundles(paths) {
  if (!writer) { log('Connect the board first.'); return; }
  if (serialBusy) return;
  serialBusy = true;
  setConnectedUi(true);
  const bar = document.getElementById('bar');
  const fill = bar.firstElementChild;
  bar.style.display = 'block';
  fill.style.width = '0%';
  let completed = 0;
  const totalFiles = 774;
  const expectedCounts = {
    'sprites.pak': 503,
    'sprites-gen3-update.pak': 271
  };
  try {
    for (let packageIndex = 0; packageIndex < paths.length; packageIndex++) {
      const path = paths[packageIndex];
      log(`Downloading package ${packageIndex + 1}/2: ${path}...`);
      const items = await fetchBundle(path);
      if (items.length !== expectedCounts[path]) {
        throw new Error(`${path}: expected ${expectedCounts[path]} files, received ${items.length}`);
      }
      log(`Sending package ${packageIndex + 1}/2 (${items.length} files)...`);
      for (const item of items) {
        await sendOne(item.name, item.data);
        completed++;
        fill.style.width = (completed / totalFiles * 100) + '%';
      }
    }
    fill.style.width = '100%';
    log('Complete: all 386 Pokémon sprites installed. Restart the board with PWR.');
  } catch (error) {
    log('Transfer stopped: ' + error.message);
  } finally {
    serialBusy = false;
    setConnectedUi(Boolean(writer));
  }
}

document.getElementById('connect').onclick = async () => {
  try {
    port = await navigator.serial.requestPort();
    await port.open({ baudRate: 115200 });
    reader = port.readable.getReader();
    writer = port.writable.getWriter();
    lineBuf = '';
    setConnectedUi(true);
    log('Connected. Now install all 386 sprites.');
  } catch (error) {
    await disconnectBoard();
    log('Could not connect: ' + error.message);
  }
};

document.getElementById('full').onclick = () =>
  loadBundles(['sprites.pak', 'sprites-gen3-update.pak']);

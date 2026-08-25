import assert from 'node:assert/strict';
import fs from 'node:fs';
import vm from 'node:vm';

const html = fs.readFileSync(new URL('../web/dev.html', import.meta.url), 'utf8');
const match = html.match(/<script>\n([\s\S]*?)<\/script>/);
assert(match, 'inline dev installer script not found');
assert(match[1].includes("loadBundles(['sprites.pak', 'sprites-gen3-update.pak']"),
       'full install must send the base and Gen-3 bundles in sequence');
assert(!match[1].includes("loadBundle('sprites-gen3-full.pak'"),
       'full install must not depend on a GitHub-blocked file over 100 MB');

class FakeElement {
  constructor() {
    this.disabled = false;
    this.style = {};
    this.textContent = '';
    this.innerHTML = '';
    this.value = '';
    this.children = [];
  }
  appendChild(child) { this.children.push(child); return child; }
  replaceChildren(...children) { this.children = children; }
  addEventListener() {}
}

class FakeOption extends FakeElement {
  constructor(text = '', value = '') {
    super();
    this.textContent = text;
    this.value = value;
  }
}

const elements = new Map();
const document = {
  getElementById(id) {
    if (!elements.has(id)) elements.set(id, new FakeElement());
    return elements.get(id);
  },
  createElement() { return new FakeElement(); },
  querySelectorAll() { return []; }
};

const context = vm.createContext({
  console,
  document,
  navigator: { serial: {} },
  Option: FakeOption,
  TextDecoder,
  TextEncoder,
  DataView,
  Uint8Array,
  setTimeout,
  clearTimeout,
  fetch: () => Promise.reject(new Error('manifest fetch disabled in unit test'))
});

vm.runInContext(match[1] + `
globalThis.serialTransportTest = (async () => {
  let readerCancelled = false;
  let writerAborted = false;
  let portClosed = false;
  reader = {
    read: () => new Promise(() => {}),
    cancel: async () => { readerCancelled = true; },
    releaseLock: () => {}
  };
  writer = {
    abort: async () => { writerAborted = true; },
    releaseLock: () => {}
  };
  port = { close: async () => { portClosed = true; } };
  setConnectedUi(true);
  let timeoutMessage = '';
  try { await readLine(15); } catch (e) { timeoutMessage = e.message; }
  const disconnected = !reader && !writer && !port &&
    !document.getElementById('connect').disabled &&
    document.getElementById('auto').disabled;

  reader = { cancel: async () => {}, releaseLock: () => {} };
  writer = { abort: async () => {}, releaseLock: () => {} };
  port = { close: async () => {} };
  setConnectedUi(true);
  const reconnected = document.getElementById('connect').disabled &&
    !document.getElementById('auto').disabled;

  let writeReaderCancelled = false;
  let writeAborted = false;
  let writePortClosed = false;
  reader = {
    cancel: async () => { writeReaderCancelled = true; },
    releaseLock: () => {}
  };
  writer = {
    write: () => new Promise(() => {}),
    abort: async () => { writeAborted = true; },
    releaseLock: () => {}
  };
  port = { close: async () => { writePortClosed = true; } };
  let writeTimeoutMessage = '';
  try { await writeSerial(new Uint8Array([1]), 15); }
  catch (e) { writeTimeoutMessage = e.message; }
  const writeDisconnected = !reader && !writer && !port &&
    !document.getElementById('connect').disabled;

  return { readerCancelled, writerAborted, portClosed, timeoutMessage,
           disconnected, reconnected, writeReaderCancelled, writeAborted,
           writePortClosed, writeTimeoutMessage, writeDisconnected };
})();
`, context);

const result = await context.serialTransportTest;
assert.equal(result.timeoutMessage, 'Board response timed out');
assert.equal(result.readerCancelled, true);
assert.equal(result.writerAborted, true);
assert.equal(result.portClosed, true);
assert.equal(result.disconnected, true);
assert.equal(result.reconnected, true);
assert.equal(result.writeTimeoutMessage, 'USB write timed out');
assert.equal(result.writeReaderCancelled, true);
assert.equal(result.writeAborted, true);
assert.equal(result.writePortClosed, true);
assert.equal(result.writeDisconnected, true);
console.log('Alle Web-Serial-Tests bestanden');

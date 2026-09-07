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

const releaseHtml = fs.readFileSync(new URL('../web/release-gen3.html', import.meta.url), 'utf8');
const releaseScript = fs.readFileSync(new URL('../web/installer-gen3.js', import.meta.url), 'utf8');
const publicHtml = fs.readFileSync(new URL('../web/index.html', import.meta.url), 'utf8');
assert(publicHtml.includes('id="backup"') && publicHtml.includes('id="restore"'),
       'public installer must expose complete save backup and restore controls');
assert(releaseScript.includes("SAVEGET\\n") && releaseScript.includes('SAVEPUT ${data.length}\\n'),
       'save backup must use explicit export and checked restore commands');
assert(releaseScript.includes('Safety backup downloaded') && releaseScript.includes('Restore this backup?'),
       'restore must create a safety backup and require confirmation');
assert(releaseHtml.includes('manifest-gen3.json?v=1.36.1'),
       'release preview must use the Gen-3 release manifest');
assert.equal((releaseHtml.match(/id="full"/g) || []).length, 1,
             'release preview must expose exactly one sprite install button');
assert(!releaseHtml.includes('data-test-command') && !releaseScript.match(/TESTMON|TESTEVO|CAUGHT|BATTLE/),
       'release preview must not expose local debug commands');
assert(releaseScript.includes("loadBundles(['sprites.pak', 'sprites-gen3-update.pak'])"),
       'release preview must install the base and Gen-3 bundles in sequence');
assert(releaseScript.includes("'sprites.pak': 503") &&
       releaseScript.includes("'sprites-gen3-update.pak': 271"),
       'release preview must reject bundles with unexpected entry counts');

const releaseElements = new Map();
const releaseDocument = {
  getElementById(id) {
    if (!releaseElements.has(id)) releaseElements.set(id, new FakeElement());
    return releaseElements.get(id);
  }
};
const releaseContext = vm.createContext({
  console,
  document: releaseDocument,
  navigator: { serial: {} },
  TextDecoder,
  TextEncoder,
  DataView,
  Uint8Array,
  setTimeout,
  clearTimeout,
  fetch: () => Promise.reject(new Error('network disabled in unit test'))
});
vm.runInContext(releaseScript + `
globalThis.releaseTransportTest = (async () => {
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
  try { await readLine(15); } catch (error) { timeoutMessage = error.message; }
  let malformedRejected = false;
  try { parsePak(new Uint8Array([84, 80, 65, 75, 1, 0]).buffer); }
  catch (_) { malformedRejected = true; }
  return { readerCancelled, writerAborted, portClosed, timeoutMessage,
           disconnected: !reader && !writer && !port,
           malformedRejected };
})();
`, releaseContext);
const releaseResult = await releaseContext.releaseTransportTest;
assert.equal(releaseResult.timeoutMessage, 'Board response timed out');
assert.equal(releaseResult.readerCancelled, true);
assert.equal(releaseResult.writerAborted, true);
assert.equal(releaseResult.portClosed, true);
assert.equal(releaseResult.disconnected, true);
assert.equal(releaseResult.malformedRejected, true);
console.log('Alle Web-Serial-Tests bestanden');

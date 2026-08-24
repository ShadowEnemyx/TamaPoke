# TamaPoke web installer

End users should open only this page:

## https://shadowenemyx.github.io/TamaPoke/web/

No ZIP download, Arduino setup, manual firmware flashing or manual sprite file
download is needed. The page flashes the firmware and loads the sprites from the
browser.

A one-click page that flashes the firmware and loads the sprites from the browser
(Chrome/Edge), with no Arduino or drivers. It uses
[ESP Web Tools](https://esphome.github.io/esp-web-tools/) to flash and **Web
Serial** to push the sprites to the SD with the firmware's `PUT` protocol (the
same one as `tools/send_sd.py`).

## Contents

- `index.html` — the page (flashing + sprite loader).
- `manifest.json` — ESP Web Tools config (points at the split firmware parts).
- `dev.html` — local-only test page with click-based Gen-2 serial controls; it is not the public installer.
- `manifest-local.json` — local-only `1.35.1-step-trail-local` manifest with debug
  firmware parts.
- `firmware/tamapoke-*-*.bin` — preserve-save firmware parts for ESP Web Tools.
- `sprites.pak` — all 251 species in one bundle (TPAK), so the page sends them in
  one click.
- `sprites-gen2-update.pak` — only #161–251 plus the rebuilt thumbnail index for
  quick local updates on a card that already has #1–160.

## Regenerate

After changing the firmware or the sprites:

```bash
bash tools/build_web.sh        # recompiles split firmware parts and rebuilds sprites.pak
```

## Test locally

Web Serial and ESP Web Tools need a **secure context**: `https://` or
`http://localhost`. To test:

```bash
cd web && python3 -m http.server 8000
# public-like installer: http://localhost:8000/
# local test installer:   http://localhost:8000/dev.html
```

The public page and `manifest.json` currently target `1.32.1-caught-mark`.
The local page is for hardware tests and targets
`1.35.1-step-trail-local`. It is compiled with `TAMAPOKE_LOCAL_TEST`, which adds the
click-driven commands `TESTMON`, `TESTEVO`, `CAUGHT`, `BATTLE`, `WALK`, `STEPS`,
`IMU` and `STATS` for testing the full #152–251 Gen-2 range and the persistent
step/trail system. `IMU` verifies the sensor and raw pedometer counter; `STATS`
also shows whether USB is still detected.
Do not replace the public manifest with the local one.

## End-user flow

1. **Install TamaPoke** → flashes the firmware (pick the USB port; tick "Erase
   device" only for a fresh board; leave it off when updating and keeping a save).
2. **Connect board** + **Load Gen-2 update** → downloads `sprites-gen2-update.pak`
   and copies it to the microSD over USB (about 25 MB). Use **Load full 251 package**
   for an empty card. Close the step-1 install tab
   first: only one program can use the port at a time.
3. Restart (PWR button) → choose your starter and play.

A hidden "pick them manually" option lets advanced users send their own `.bin`.

## Hosting the sprites

This fork serves `sprites.pak` directly from GitHub Pages so the one-click sprite
loader works without manual downloads. Release assets are provided only as a
backup for advanced users.

All sprites are from PMD SpriteCollab, CC BY-NC (non-commercial sharing with
attribution is allowed); see [`../CREDITS.md`](../CREDITS.md).

## Deploy (GitHub Pages)

1. Repo settings → Pages → serve from branch `tamapoke-expanded-update`, folder
   `/`. Pages gives HTTPS automatically.
2. The installer URL is `https://shadowenemyx.github.io/TamaPoke/web/`.

> **Pages on private repos** needs GitHub Pro/Team. If you make the repo
> **public** to use Pages for free, decide about the sprites first (see above and
> CREDITS).

## Limitations

- Desktop **Chrome/Edge** only (Web Serial isn't in Firefox/Safari).
- The local test page is intentionally not part of the GitHub Pages public flow.

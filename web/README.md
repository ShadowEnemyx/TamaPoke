# TamaPoke web installers

## Current public installer

End users currently use:

<https://shadowenemyx.github.io/TamaPoke/web/>

`index.html` and `manifest.json` serve the public Gen‑3 release `1.36.0` with
Pokémon #1–386. They expose no debug controls and require the complete two-step
firmware-plus-sprites installation.

## Gen‑3 pages

- `dev.html` + `manifest-local.json`: `1.36.0-gen3-local`, compiled with
  `TAMAPOKE_LOCAL_TEST`. It includes click-driven Pokémon, evolution, battle,
  IMU and step diagnostics.
- `release-gen3.html` + `manifest-gen3.json`: local reference copy of the same
  public-style `1.36.0` page, compiled with `TAMAPOKE_GEN3_RELEASE`.

The release preview deliberately exposes only one sprite action. It transfers
`sprites.pak` and then `sprites-gen3-update.pak`, giving every user the complete
#1–386 set. Firmware flashing without this second step is an incomplete Gen‑3
installation.

There is no `sprites-gen3-full.pak`. The former combined file exceeded 100 MB;
the two-package sequence keeps every GitHub-hosted file below the limit.

## Files

- `sprites.pak`: 502 normal/Shiny files for #1–251 plus 251-entry `thumbs.bin`
  (503 bundle entries).
- `sprites-gen3-update.pak`: 270 normal/Shiny files for #252–386 plus the full
  386-entry `thumbs.bin` (271 bundle entries).
- `firmware/tamapoke-<version>-*.bin`: bootloader, partitions, boot_app0 and app
  parts used by ESP Web Tools without overwriting the NVS save partition.

## Build and validate

```bash
bash tools/build_web.sh --check         # current public Gen 3
bash tools/build_web_local.sh --check   # Gen 3 debug
bash tools/build_web_gen2_legacy.sh --check # pinned historical Gen 2
```

Omit `--check` to refresh the current public Gen‑3 artifacts. The separate
legacy Gen‑2 command is read-only and never modifies installer files.

Each build validates its firmware version, Dex count, package entry counts and
thumbnail structure/count. The public Gen‑3 build also rejects binaries that
contain local `TESTMON` or `TESTEVO` command strings.

## Test locally

Web Serial and ESP Web Tools require HTTPS or localhost:

```bash
python3 -m http.server 8000 --directory web
```

- <http://127.0.0.1:8000/> — public Gen‑3 page
- <http://127.0.0.1:8000/dev.html> — Gen‑3 debug page
- <http://127.0.0.1:8000/release-gen3.html> — Gen‑3 public preview

Use desktop Chrome or Edge. Close the ESP Web Tools flash dialog before
reconnecting for sprite transfer because only one program can own the serial
port. Leave **Erase device** unchecked when preserving an existing save.

Both Gen‑3 pages use bounded serial reads/writes. A timeout or USB disconnect
cancels the transfer, closes the port and returns the interface to the connect
state so the user can reconnect.

## Release policy

The public flow must retain the mandatory two-step warning and the single,
complete sprite button. `dev.html` and `manifest-local.json` must never replace
the public page or manifest.

Sprites are from
[PMD SpriteCollab](https://github.com/PMDCollab/SpriteCollab) under CC BY-NC;
see [`../CREDITS.md`](../CREDITS.md).

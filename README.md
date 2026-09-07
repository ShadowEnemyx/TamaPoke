# TamaPoke

[![Flash in browser](https://img.shields.io/badge/flash-in%20browser-FF6B00?logo=googlechrome&logoColor=white)](https://shadowenemyx.github.io/TamaPoke/web/)
[![MakerWorld](https://img.shields.io/badge/MakerWorld-3D%20case-00AE42?logo=bambulab&logoColor=white)](https://makerworld.com/es/models/2937822-tamapoke-a-pokemon-pokeball-tamagotchi)
![Board](https://img.shields.io/badge/board-ESP32--S3%20round%20AMOLED-E7352C?logo=espressif&logoColor=white)
![Firmware](https://img.shields.io/badge/firmware-v1.36.0-4F93C4)
![Pokédex](https://img.shields.io/badge/Pok%C3%A9mon-386-E8503A)
![Languages](https://img.shields.io/badge/languages-6-FFCB05)

TamaPoke is a Pokémon-inspired virtual pet for the
**Waveshare ESP32-S3-Touch-AMOLED-1.75**. This is ShadowEnemyx's expanded fork.

> Use only the ShadowEnemyx installer linked here. The upstream project is
> credited as the original source, but its installer contains a different build.

## Install the current public version

### [Open the ShadowEnemyx web installer](https://shadowenemyx.github.io/TamaPoke/web/)

The hosted installer serves firmware `1.36.0` with all 386 Pokémon from
Generations 1–3. Use desktop **Chrome or Edge**:

1. Connect the Waveshare board by USB and install the firmware.
2. When updating, leave **Erase device unchecked** to preserve the save.
3. Reconnect the board in step 2 and load the sprites onto the microSD.

No ZIP, Arduino project or manual `.bin` download is required.

## Gen 3

Gen 3 is now public. The hosted installer uses the tested, debug-free `1.36.0`
firmware. The local `dev.html` page remains available only for development and
hardware diagnostics.

> [!WARNING]
> **A Gen‑3 installation always has two required steps.** Flashing firmware alone
> is incomplete. The sprite button must then copy both `sprites.pak` (#1–251)
> and `sprites-gen3-update.pak` (#252–386 plus the 386-entry thumbnail index) to
> the microSD. There is intentionally no single `sprites-gen3-full.pak` file.

## Highlights

- 386 Pokémon from Kanto, Johto and Hoenn, including Shiny variants
- region and starter selection on a new Gen‑3 save
- six UI languages: English, German, Spanish, French, Italian and Portuguese
- evolution with branching, day/night, bond and stat conditions
- evolution care gate: strictly three of four needs above 40
- persistent Pokédex/Box with raised and caught markers
- wild battles, catching, training, five minigames and daily goals
- expeditions with a small persistent item inventory
- profile, personality, medals, collector ranks and cosmetic frames
- RTC-based day/night and offline progression
- synthetic species chirps and sound effects; no game audio or ROM samples
- subtle moving `@SE` attribution watermark
- persistent step counter visible at top left and on the Steps/Trail card

### Walking rewards

Walking counts with the display on or off and also while USB is connected once
the cadence filter confirms real rhythmic steps. Single bumps are rejected.

- Daily rewards: **500 / 2,000 / 5,000** steps
- Lifetime trail ranks: **10,000 / 50,000 / 100,000 / 250,000** steps
- Walking slowly raises JOY and BOND within daily/hourly caps
- Daily and lifetime steps improve wild Shiny odds and catching slightly

## Basic controls

- Tap the Pokémon: pet it and play its synthetic chirp in the full sound mode.
- Swipe sideways: Pokédex/gallery.
- Swipe up: Profile, Personality, Daily, Box, Battle, Medals, Progress,
  Expedition and Steps/Trail cards.
- Swipe down: clock, language, sound, power saving and help.
- Hold the Pokémon for three seconds: release dialog.
- Short PWR press: display on/off. Long PWR press: full power-off.

Four needs decay over time: **FOOD, JOY, ENE and HYG**. Evolution requires the
species' level and at least three of those four values strictly above 40.
Evolution, farewell, release and runaway are always shown as decisions and do
not complete unseen in the background.

## Hardware

- Waveshare ESP32-S3-Touch-AMOLED-1.75 Standard or `-G`
- round 466×466 CO5300 AMOLED and CST9217 touch
- 16 MB flash with OPI PSRAM
- microSD, PCF85063 RTC, AXP2101 power management
- QMI8658 IMU and ES8311 audio codec

The `-B` model's supplied protective case does not fit the linked Pokéball case;
the separate `1.75C` is a different board.

## Developer builds

Board profile:

```bash
FQBN="esp32:esp32:esp32s3:CDCOnBoot=cdc,FlashSize=16M,PSRAM=opi,PartitionScheme=app3M_fat9M_16MB"
```

Validated toolchain: ESP32 Arduino core `3.3.10`, GFX Library for Arduino
`1.6.7`, SensorLib `0.4.1` and XPowersLib `0.3.3`.

Build and validate without replacing installer artifacts:

```bash
bash tools/build_web.sh --check         # current public Gen 3, 386 Pokémon
bash tools/build_web_local.sh --check   # Gen 3 debug build, 386 Pokémon
bash tools/build_web_gen2_legacy.sh --check # pinned historical Gen 2 check
```

Build the local artifacts, serve the folder and open the required page:

```bash
bash tools/build_web_local.sh           # or: bash tools/build_web_gen3.sh
python3 -m http.server 8000 --directory web
```

- `http://127.0.0.1:8000/` — current public Gen‑3 installer
- `http://127.0.0.1:8000/dev.html` — Gen‑3 hardware/debug installer
- `http://127.0.0.1:8000/release-gen3.html` — local release reference page

Never enable **Erase device** for an update whose save should be retained.

### Sprite pipeline

Sprites come from
[PMD SpriteCollab](https://github.com/PMDCollab/SpriteCollab) and are generated
and transferred with the repository tools:

```bash
python3 tools/pack_pmd.py
python3 tools/make_thumbs.py
python3 tools/pack_bundle.py
python3 tools/pack_bundle.py --gen3
python3 tools/send_sd.py
```

The safe complete Gen‑3 web flow sends the two sub-100-MB bundles sequentially.
The smaller Gen‑3-only button remains available only on the debug page for a
known-complete Gen‑2 card.

## Tests

```bash
cd tests && make clean && make test
cd ..
bash tools/build_web.sh --check
bash tools/build_web_local.sh --check
bash tools/build_web_gen2_legacy.sh --check
git diff --check
```

Hardware remains the final authority for display clipping, touch edges, IMU,
speaker volume, microSD transfer and save retention. Core Gen‑3 flashing,
sprites and step counting have already passed the owner's hardware smoke test;
the extended release checklist is tracked in `AI_HANDOFF.md`.

## Credits and license

This is a personal, non-commercial fan project and is not affiliated with or
endorsed by Nintendo, Game Freak or The Pokémon Company.

- Original project: [socquique/TamaPoke](https://github.com/socquique/TamaPoke)
- Expanded fork and installer: [ShadowEnemyx/TamaPoke](https://github.com/ShadowEnemyx/TamaPoke)
- Animated pixel art: [PMD SpriteCollab](https://github.com/PMDCollab/SpriteCollab), CC BY-NC 4.0
- 3D Pokéball case/remix: [MakerWorld](https://makerworld.com/es/models/2937822-tamapoke-a-pokemon-pokeball-tamagotchi), CC BY-NC-SA
- Source code: [MIT](LICENSE)

See [CREDITS.md](CREDITS.md) for complete attribution.

# TamaPoke development progress

Stand: 2026-09-07

## Current state

- Active branch: `local/full-gen3`; rollback tag: `local-before-gen3`.
- The tested Gen‑3 feature commit `da8bfa8` is already on `fork/main`.
- The hosted installer serves public Gen 3 `1.36.0` with #1–386.
- GitHub Pages is switched to the Gen‑3 installer and the matching GitHub release
  is published.
- Local debug build: `1.36.0-gen3-local` with `TAMAPOKE_LOCAL_TEST`.
- Public release: `1.36.0` with `TAMAPOKE_GEN3_RELEASE`, without local debug
  commands.

## Completed features

- Gen‑2 and Gen‑3 Dex data through #386, six languages, stats, types, rarity
  data, region/starter selection and evolution rules.
- Evolution requires strictly three of four care values above 40 and supports
  branch, bond, day/night and stat conditions.
- All normal and Shiny SpriteCollab files through #386 plus 386 thumbnails.
- Moving `@SE` attribution watermark.
- Persistent software step counter, top-left HUD and Steps/Trail card.
- Daily rewards at 500/2,000/5,000 steps, lifetime trail ranks, walking
  JOY/BOND rewards and capped Shiny/catch bonuses.
- Local browser controls for Pokémon, evolutions, battles and IMU/step
  diagnostics; no terminal is needed for the debug workflow.
- Gen‑3 build hardening: target-level evolution setup, Web Serial timeout and
  reconnect handling, Box list reuse and complete thumbnail validation.

## Sprite delivery

- `web/sprites.pak`: 503 entries for #1–251 including a 251-entry thumbnail file.
- `web/sprites-gen3-update.pak`: 271 entries for #252–386 including the complete
  386-entry thumbnail file.
- A complete Gen‑3 installation sends those two packages sequentially.
- `sprites-gen3-full.pak` was removed because it exceeded GitHub's 100-MB file
  limit and must not be referenced by current instructions.

## Installer paths

- `/web/index.html`: live/public Gen‑3 installer.
- `/web/dev.html`: local Gen‑3 debug installer with optional update/full choices.
- `/web/release-gen3.html`: local reference copy with one mandatory full sprite
  button and no debug controls.

## Historical milestones

- `local-before-full-gen2`: rollback before the full Gen‑2 work.
- `local-before-steps`: rollback before the walking system.
- `local-full-gen2-final`: completed Gen‑2 development snapshot.
- `local-full-gen2-final-1.35.3` / `v1.35.3`: stable public Gen‑2 installer.
- `local-before-gen3-bugfix-20260825`: snapshot before Gen‑3 hardening.

## Follow-up

- Monitor real installs and keep the two-step sprite warning prominent.
- Continue longer hardware soak tests for screen-off walking, rewards, six
  languages, touch edges and save retention.

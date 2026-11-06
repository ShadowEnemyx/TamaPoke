# TamaPoke – Projektregeln für KI-Sessions

ESP32-S3-Firmware (Arduino) für das Waveshare ESP32-S3-Touch-AMOLED-1.75 plus Browser-Installer in `web/`.
Arbeitsordner: `/Volumes/2TB SSD/Backup bot/Apps/tamapoke/TamaPoke` (Branch `local/full-gen3`).

## Lesereihenfolge

1. `PROJEKT_KONTEXT.md` – dauerhafte Technik, Dateien, Tests, Arbeitsregeln (kompakt).
2. `AI_HANDOFF.md` – ausführlicher Stand, Versionschronik, Verifikations-Checkliste.
3. `progress.md` – aktueller Fortschritt und Installer-Pfade.
4. `HOENN_WALK_LOCAL.md` – nur bei Arbeit am lokalen Kandidaten `1.36.2-hoenn-walk-local`.
5. `web/README.md`, `tools/assets/README.md` – nur bei Installer- bzw. Sprite-Arbeit.

Verbindliche Versionen stehen im Code: `FW_VERSION` in `TamaPoke.ino`, `tools/build_web_gen3.sh`,
`tools/build_web_local.sh` und den Manifesten in `web/`. Bei Abweichungen zählt der Code; die Doku danach angleichen.

## Harte Regeln

- **Nie ohne ausdrückliche Aufforderung pushen, releasen, Pages umstellen oder die PR ändern.**
  Lokales Bauen, Testen und der lokale Web-Installer sind jederzeit erlaubt.
- Bei Firmware-Updates **„Erase device“ ausgeschaltet lassen**, sonst geht der Spielstand (ESP32-NVS) verloren.
- Saves/NVS nicht durch unnötige Migrationen gefährden. Neue Logik zuerst in nativen Tests abdecken, dann UI/Hardware.
- Gen-3-Installation hat immer zwei Schritte: Firmware flashen **und** beide Sprite-Pakete (`sprites.pak`,
  `sprites-gen3-update.pak`) auf die microSD senden. `sprites-gen3-full.pak` existiert nicht und darf nirgends verlangt werden.
- `web/dev.html`, `web/manifest-local.json` und `TAMAPOKE_LOCAL_TEST` gehören nie in den öffentlichen Installer
  (`web/index.html`, `web/manifest.json`). Der öffentliche Build enthält keine Debug-Befehle (`TESTMON`, `TESTEVO`, …).
- Keine historischen Firmware-Binaries massenhaft in Git aufnehmen; nur die vier Parts einer freigegebenen Version.
- Keine originalen Pokémon-Cries, ROM-Samples oder urheberrechtlich geschützten Audio-Dateien; Audio bleibt synthetisch.
- UI-Texte im Firmware-Code bleiben aus Font-Gründen weitgehend ASCII (keine Umlaute/Akzente).

## Build und Tests

```bash
cd tests && make clean && make test
cd .. && bash tools/build_web.sh --check
bash tools/build_web_local.sh --check
bash tools/build_web_gen2_legacy.sh --check
git diff --check
```

Lokaler Installer: `python3 -m http.server 8000 --directory web` (Chrome/Edge, `/`, `/dev.html`, `/release-gen3.html`).
Hardware (Display-Clipping, Touch, IMU, Lautstärke, SD-Transfer, Save-Erhalt) bleibt die letzte Instanz; Native Tests ersetzen sie nicht.
Das Laufwerk ist ExFAT: vor `make test` im Ordner `tests` ggf. `dot_clean -m tests` ausführen (`._*`-Dateien).

## Dokumentation pflegen

- Gemeinsame Regeln stehen hier in `AGENTS.md`; `CLAUDE.md` bindet sie per `@AGENTS.md` ein.
- Beim Versionssprung `PROJEKT_KONTEXT.md`, `AI_HANDOFF.md`, `progress.md`, `web/README.md` und `README.md` gemeinsam angleichen.
- Sprache: Projektdoku für Entwickler auf Deutsch mit echten Umlauten und ß (`AI_HANDOFF.md`, `PROJEKT_KONTEXT.md`), öffentliche Dateien auf Englisch
  (`README.md`, `CREDITS.md`, `web/README.md`, `tools/assets/README.md`, `progress.md`, `HOENN_WALK_LOCAL.md`).

<!-- skill-routing:start v2 – von Hand für ESP32-Firmware angelegt; gemeinsame Regeln in AGENTS.md; CLAUDE.md bindet sie ein -->
## Skill-Zuordnung

Projektart: ESP32-Firmware (Arduino/C++) mit Browser-Installer.

| Wann | Skill |
| --- | --- |
| Browser-Installer (`web/*.html`, `installer-gen3.js`) im Browser prüfen: klicken, Konsolenfehler, Screenshots | `playwright` |
| Installer-Seiten bauen oder prüfen: Zustände, responsives Layout, Barrierefreiheit, Interface-Texte | `ui-ux-quality` |
| Vor Veröffentlichung eines neuen Installer-Stands | Abschnitt „Build und Tests“ oben; nur nach ausdrücklichem Auftrag veröffentlichen |
| Nur auf ausdrücklichen Wunsch: fremde App analysieren oder nachbauen | `replica-*` (Start: `replica-recon`) |

Nicht zuständig: `apple-app-release-check`, `swiftui-expert-skill`, `swift-concurrency`, `fullstack-architecture`
(keine App-Store-App, kein SwiftUI, kein Backend).
<!-- skill-routing:end -->

# TamaPoke Expanded - AI Handoff

Stand: 2026-11-05 (Versionsangaben abgeglichen; Chronik bis 1.36.1 und lokaler 1.36.2-Kandidat ergänzt)

## Projekt und Hardware

Dieses Repository ist eine stark erweiterte, community-orientierte Firmware für
das Waveshare ESP32-S3 Touch AMOLED 1.75. Es ist ein Fork von
`socquique/TamaPoke` und wird als "Expanded"-Variante gepflegt.

- Firmware-Entry-Point: `TamaPoke.ino`
- Ausgangs-Firmware-Stand: `1.32.1-caught-mark`
- Lokaler Testbuild: `1.36.2-hoenn-walk-local` (über `TAMAPOKE_LOCAL_TEST`;
  Hoenn-Expeditionen mit Schrittzielen, siehe `HOENN_WALK_LOCAL.md`)
- Öffentlicher Gen-3-Release: `1.36.1` (über
  `TAMAPOKE_GEN3_RELEASE`, ohne lokale Debugbefehle)
- Board: ESP32-S3, 16 MB Flash, OPI PSRAM, rundes 466x466 AMOLED, CST9217 Touch,
  PCF85063 RTC, AXP2101 PMU, ES8311 Audio
- Validierte Toolchain: ESP32-Core 3.3.10, Arduino_GFX 1.6.7,
  SensorLib 0.4.1 und XPowersLib 0.3.3.
- Sprache: DE, EN, ES, FR, IT, PT. Code und UI-Texte verwenden aus
  Font-Gründen weitgehend ASCII ohne Umlaute/Akzente.

Die Firmware speichert den Spielstand in ESP32-NVS. Bei einem Update darf der
Installer **nicht** mit `Erase device` ausgeführt werden, sonst wird der Save
gelöscht.

## Wichtige Arbeitsregel

**Niemals auf GitHub pushen, Releases erstellen oder die PR aktualisieren, ohne
die ausdrückliche Aufforderung des Nutzers.**

Der Nutzer möchte unfertige lokale Versionen erst auf seiner Hardware testen.
Lokales Bauen, Testen und ein lokaler Web-Installer sind immer erlaubt und
erwünscht.

## Aktueller Gen-3-Arbeitsstand

- Branch `local/full-gen3`; Tag `local-before-gen3` erlaubt die schnelle
  Rückkehr zum funktionierenden Gen-2-Stand. Der getestete Gen-3-Featurestand
  `da8bfa8` liegt bereits auf `fork/main`. Der gehostete Installer und der
  GitHub-Release verwenden den debugfreien Gen-3-Stand `1.36.1`.
- Lokaler Dex #1–386 mit sechs Sprachen, uint16-Dexpfaden, Gen-3-Stats/Typen,
  Evolutionsregeln und dem 3-von-4-Stats-Gate über 40 Prozent.
- Lokaler Erststart: Region Kanto/Johto/Hoenn wählen, danach einen von drei
  Regions-Startern. Vorhandene Saves werden nicht migriert oder gelöscht.
- Alle 270 Gen-3-SpriteCollab-Dateien (Normal + Shiny) sind in
  `tools/sdcard/mons/`; `thumbs.bin` hat 386 Einträge.
- `web/sprites-gen3-update.pak` umfasst #252–386 (ca. 38 MB). Das öffentliche
  `web/sprites.pak` bleibt #1–251. Der lokale Button für das volle 386er-Paket
  sendet beide Dateien nacheinander; dadurch bleibt jede GitHub-Datei unter
  dem 100-MB-Limit.
- Eine einzelne Datei `sprites-gen3-full.pak` existiert nicht mehr und darf in
  Anleitungen oder Release-Texten nicht verlangt werden.
- Lokaler Webtest: `cd web && python3 -m http.server 8000`, danach
  `http://localhost:8000/dev.html` in Chrome/Edge. Schritt-, IMU- und
  Evolutionsdiagnosen laufen dort über Klicks; kein `screen`-Terminal nötig.
- Build mit `bash tools/build_web_local.sh`; die vier lokalen Firmware-Parts
  liegen danach unter `web/firmware/tamapoke-1.36.2-hoenn-walk-local-*.bin`.
- Der öffentliche, debugfreie Release wird mit `bash tools/build_web.sh`
  gebaut. `bash tools/build_web_gen3.sh` ist der zugrunde liegende Gen-3-Build;
  `web/release-gen3.html` bleibt eine lokale Referenzseite.
- README, Installer und Release-Text sagen deutlich: Firmware-Flash allein
  reicht nicht; danach ist
  Schritt 2 für die microSD-Sprites Pflicht. Bei neuer/leerer/unklarer Karte
  immer das volle 386er-Paket statt nur des Gen-3-Updates verwenden.

## Aktueller Arbeitsbaum

Der öffentliche Installer zeigt auf den debugfreien Gen-3-Build `1.36.1`.
Für Hardwaretests existieren weiterhin `web/dev.html` und
`web/manifest-local.json`; diese Debug-Dateien sind bewusst nicht Teil des
öffentlichen Installationsflusses.

Aktuelle lokale Testguards in `TamaPoke.ino`:

- `TAMAPOKE_LOCAL_TEST` setzt die Anzeigeversion auf `1.36.2-hoenn-walk-local`.
- `TAMAPOKE_GEN3_RELEASE` setzt die Anzeigeversion auf `1.36.1` und erlaubt den
  386er-Dex, schaltet aber keine Debugbefehle frei.
- Die Serial-Befehle `TESTMON`, `TESTEVO`, `CAUGHT`, `CAUGHT <dex>`, `BATTLE`
  und `BATTLE <dex>` sind nur in diesem Testbuild aktiv.
- Diese Testversion darf nicht versehentlich in `web/index.html` oder
  `web/manifest.json` eingetragen oder als öffentlicher GitHub-Pages-Installer
  aktiviert werden; sie liegen für Hardwaretests in `web/dev.html` und
  `web/manifest-local.json`.
- `web/release-gen3.html` und `web/manifest-gen3.json` sind die lokale
  öffentliche Vorschau ohne Debugoberfläche. Der einzige Sprite-Knopf sendet
  `sprites.pak` und `sprites-gen3-update.pak` zwingend nacheinander.

Aktueller Git-Zustand bei Erstellung dieser Datei:

- Aktueller Branch: `local/full-gen3` (der Gen-2-Stand bleibt historisch auf
  `local/full-gen2` erhalten).
- `fork`: `https://github.com/ShadowEnemyx/TamaPoke.git`
- `origin`: `https://github.com/socquique/TamaPoke.git`
- Der Ausgangspunkt ist lokal als `3b24ea8` (`chore: save local baseline before gen2 watermark`)
  und zusätzlich mit dem Tag `local-baseline-before-gen2-watermark` gesichert.
- Der lokale Featurestand ist als `feat: add gen2 starters and local watermark` gesichert;
  der finale Stand wurde nach ausdrücklicher Nutzerfreigabe auf `fork/main`
  veröffentlicht.
- Der letzte getestete Gen-2-Stand ist historisch als Tag
  `local-full-gen2-final` markiert. Der aktuelle Arbeitsbranch ist
  `local/full-gen3`; vor den Bugfixes liegt zusätzlich der lokale Tag
  `local-before-gen3-bugfix-20260825`.
- Der Arbeitsbaum enthält den veröffentlichten Gen-2-, Wasserzeichen-,
  Lokalisierungs-, Sprite- und Schrittstand. `web/index.html` und
  `web/manifest.json` zeigen auf den öffentlichen Build; nur `web/dev.html`
  und `web/manifest-local.json` aktivieren die Debug-Befehle.
- Der Hauptautor hat die große Expanded-PR offen gelassen und verlinkt den Fork,
  möchte sie aber wegen Umfang, Branding und Binary-Historie nicht komplett in
  das Basisprojekt mergen. Kleine, spätere Einzel-PRs wären möglich, aber nur
  nach Nutzerentscheidung.

## Vorhandene Funktionen

### Kernspiel

- Ei, Starterwahl, Schlüpfen, Pflege, Schlaf, Hygiene, Hunger, Freude,
  Energie, Gewicht, Bindung, Spitznamen, Evolution, Farewell, Release und
  Runaway.
- Alter und Pflege laufen mit RTC auch bei ausgeschaltetem Display weiter;
  Offline-Fortschritt ist begrenzt.
- Pokedex/Gallery unterscheidet gezüchtete (`raised`) und gefangene (`caught`)
  Pokemon.
- Profil, Persönlichkeit, Tagesziele, Medaillen, Fortschritt und
  Sammler-Rang sind über acht Swipe-Karten erreichbar.

### Battle

- Manuelle Wild Battles über die Battle-Karte, zusätzlich seltene optionale
  Wild-Encounter-Prompts auf dem Hauptscreen.
- Gegner-Level liegen normalerweise nahe am Pet-Level, können aber auch einige
  Level darunter liegen. Wilde Legendäre sind in v1 nicht vorgesehen.
- Typen sind in den Kämpfen sichtbar und beeinflussen Schaden moderat.
- Aktionen: Quick, Heavy, Dodge/Counter, Rest und Run.
  - Quick: weniger Schaden, sicherer und reduziert eingehenden Schaden.
  - Heavy: mehr Schaden, aber der Gegner kann ausweichen/kontern.
  - Dodge: kann Counter für den nächsten Angriff vorbereiten.
  - Rest: maximal zweimal pro Kampf, heilt und gibt Guard.
- Kein Pokemon-Tod, kein Catching bei Niederlage. Siege/Niederlagen/Streaks
  sind persistent und geben moderate Trainingsbelohnungen.
- Nach einem Sieg gibt es genau einen optionalen Fangversuch. Bei knapper
  Niederlage kann es eine kleine "respect catch"-Chance geben.
- Im Kampf zeigt ein kleiner Pokeball rechts neben der Gegner-Namenszeile an,
  ob das gegnerische Pokemon bereits gefangen wurde. Das Symbol nutzt nur den
  bestehenden `dexCaught`-Bitmap und ändert keine Save-Struktur.

### Minigames und Events

- Play-Menü mit Ball, Catch, Memo, Clean und Type.
- Ball ist ein schweres Reaktionsspiel mit schneller/unvorhersehbarer Bewegung.
- Catch ist ein Reaktionsspiel mit zunehmend kurzen Zeitfenstern.
- Memo zeigt eine Farbsequenz, die nachgetippt werden muss; die Anleitung liegt
  optisch zwischen den Pad-Reihen und die Pads haben eigene Töne.
- Clean und Type ergänzen Hygiene- bzw. Typen-/Angriffs-Training.
- Seltene, freiwillige Pet-Events (Berry, Heart, Sparkle) und seltene optionale
  Wild-Encounter unterbrechen andere UI-Modalen nicht.

### Expedition und Inventar

- Achte Karte `EXPEDITION` mit 15/30/60-Minuten-Touren.
- Ein kleiner Hauptscreen-Chip erscheint nur bei aktiver Tour, abholbarem Fund
  oder vorhandenen Items; ein Tap öffnet direkt die Expeditions-Karte.
- Touren laufen per RTC weiter, auch wenn das Board ausgeschaltet ist.
- Belohnung wird beim Start festgelegt und persistiert.
- Inventar: Trail Snack, Energy Tonic, Care Kit und Train Token. Maximal drei
  jedes Items; Train Token öffnet die ATK/DEF/SPD-Auswahl.
- Der Hauptscreen-Chip öffnet direkt Karte 8 und zeigt Tour-Restzeit,
  abholbaren Fund oder Inventaranzahl.

### Einstellungen, Hilfe und Performance

- Settings: Sprache, Uhrzeit, vier Soundmodi und optionales Power Save.
- Power Save ist standardmäßig aus; es reduziert Idle-Rendering und nutzt
  Light Sleep nur bei Dimmung/Screen-Off. Pflege, RTC und Touch-Wakeup bleiben
  aktiv.
- Acht integrierte Hilfeseiten beschreiben Bedienung, Battle und Systeme.
- Statische Screens nutzen Dirty-Rendering; aktive Spiele/Battle bleiben
  regelmäßig gerendert.

### Bewegung, Tageszeit und Evolution

- `dayphase.h` liefert eine gemeinsame Morgen-/Tag-/Abend-/Nacht-Phase für
  Hintergrund, Wild-Pool und Pflegeverbrauch.
- Nachts sinkt FOOD im Wachzustand langsamer; Schlaf bleibt unverändert.
- QMI8658-Schütteln gibt begrenzt JOY. Der Pedometer zählt Schritte auch bei
  Screen-off; Tages-/Gesamtzähler, Trail-Belohnungen sowie Wild-Shiny-/Fangbonus
  bleiben in NVS. Der aktuelle Softwarezähler nutzt gefilterte positive
  Beschleunigungsimpulse und zählt auch bei USB, sobald zwei rhythmische
  Schritte bestätigt sind. Der rohe QMI-Pedometer bleibt als Diagnose sichtbar.
- Evolution wird nie automatisch ausgeführt: Der rote CTA bleibt bei erreichtem
  Level sichtbar und erinnert bei zu niedrigen Pflegewerten. Form behalten wird
  auf Level 100 nach einem Spieltag erneut angeboten.

## Audio

Audio ist vollständig synthetisch über ES8311/I2S. Es werden keine originalen
Pokemon-Audiodateien oder ROM-Sounds benutzt.

- `SOUND_FULL` / TON VIEL: UI, Minigames, Battle, Ambient und Pet-Rufe.
- `SOUND_MED`: wichtige Care-, Battle-, Event- und Ergebnis-Sounds.
- `SOUND_LOW`: große Ereignisse und Warnungen.
- `SOUND_OFF`: stumm.

Die Spezies-Rufe und alle UI-/Battle-/Minigame-Sounds sind synthetisch:

- vier statt drei Töne, länger und ohne Noise-Wave
- höhere Synthese-Lautstärke
- bei TON VIEL hat ein Pet-Tap Vorrang vor dem generischen Klick
- Pet-Tap, Galerie-Detail und Wildkampf haben eigene Ruf-/SFX-Pfade
- Soundmodi bleiben getrennt: VIEL, MITTEL, WENIG, AUS

Die Lautstärke und Wirkung müssen weiterhin auf echter Hardware beurteilt
werden; Desktop-Builds können den ES8311-/Lautsprecherweg nicht ersetzen.

## Versionschronik

Die folgenden Einträge dokumentieren den damaligen Entwicklungsstand. Nicht
jede Testversion wurde veröffentlicht; Angaben zu früheren Branches sind keine
Beschreibung des aktuellen Arbeitsbaums. `1.36.2-hoenn-walk-local` ist der
aktuelle lokale Debugstand; `1.36.1` ist der veröffentlichte debugfreie Gen-3-Release.

1. `1.29.3-reliability`
   - Reset von Interaktions-/Evolution-/Farewell-Sperren bei neuem Pet.
   - Farewell/Release/Runaway wird nach einem Reset sicher abgeschlossen.
   - Pet-Level ist auf 100 begrenzt.
   - `millis()`-Deadlines sind rollover-sicher.
   - Karten aktualisieren bei Pet-Ticks wieder.
   - verbleibende UI-Literale wurden i18n-Keys zugeordnet.
   - macOS `._*`-Sidecars innerhalb von `.git` wurden entfernt; `git fsck` ist
     danach bis auf einen normalen dangling Commit sauber.
2. `1.29.4-profile-tap`
   - Die grünen Kreise im Profil waren Sammlerrahmen. Sie werden nicht mehr
     über dem Portrait gezeichnet.
   - Ein Tap auf das Profil-Portrait spielt jetzt den Spezies-Ruf.
3. `1.29.5-pet-chirps`
   - Klarere und hörbarere, eigene synthetische Spezies-Rufe.
4. `1.30-expedition-hud`
   - Sichtbarer, runder-screen-tauglicher Einstieg zu Tour und Inventar auf
     dem Hauptscreen. Der Chip zeigt Tour-Restzeit, abholbaren Fund oder
     Inventaranzahl und bleibt in allen Modal-Ansichten verborgen.
5. `1.30.1-caught-frames`
   - Wildkämpfe zeigen links neben dem Gegner-HP-Balken einen kleinen
     Pokeball, wenn dieses Pokemon bereits gefangen wurde.
   - Profilrahmen sind wieder sichtbar: sechs Ecken-/Akzentvarianten liegen
     hinter dem Portrait und verdecken den Sprite nicht.
6. `1.31.0-day-imu`
   - Gemeinsame Tageszeit-API in `dayphase.h` (Morgen/Tag/Abend/Nacht).
   - Wach nachts: FOOD -1/Tick statt -2; Schlaf unverändert. Offline-Minuten
     nutzen die Uhrzeit jeder Minute.
   - Wild-Pool nach Phase: Morgen Grass/Flying/Normal/Bug, Abend Water/Flying/Fire,
     Nacht Ghost/Poison/Bug. Tag bleibt ungefiltert. Keine Legends.
   - Nacht-Idle läuft seltener. Ein Morgen-Overlay einmal pro Kalendertag,
     ohne Auto-Wecken.
   - QMI8658: Schütteln gibt JOY auf dem Hauptscreen (Cooldown 25 s, 8/Tag).
     Schritte auch bei Screen-off; der damalige Build verwarf USB-Steps.
     Der spätere Schritt-Testbuild zählte auch bei USB. Serial: `IMU`, `SHAKE`,
     `WALK n`, `STEPS`, `STATS`. Die lokale Testseite bietet zusätzlich klickbare
     `IMU`-/`STATS`-Diagnosebuttons; `STATS` zeigt auch `usb=0/1`.
7. `1.31.1-shake-fix`
   - Shake-Schwelle gesenkt (~1.45 g oder Gyro), Accel+Gyro, beide I2C-Adressen.
8. `1.32.0-evo-cta`
   - Roter Entwicklungs-Button bleibt, sobald das Level reicht, auch wenn ein
     Balken unter 40 liegt. Tippen erinnert dann an die Balken.
   - "Form behalten" auf Level 100 kommt nach einem Spieltag wieder.
9. `1.32.1-caught-mark`
   - Öffentlicher Installerstand mit Fangmarker im Wildkampf.
   - Der Marker sitzt neben der Gegner-Namenszeile und zeigt nur bereits
     gefangene wilde Pokemon.
10. `1.32.1-local-test`
   - Lokale Testvariante mit zusätzlichen Serial-Befehlen für Fangmarker und
     erzwungene Battle-Gegner. Nicht öffentlich veröffentlichen.
11. `1.34.0-gen2-full-local`
   - Vollständiger Dex #1-251 mit Gen-2-Namen, Werten, Typen, sechs Sprachen
     und 122 Evolutionsregeln inklusive Eevee-, Baby- und Tyrogue-Verzweigungen.
   - Eine Entwicklung benötigt strikt drei von vier Pflegewerten über 40;
     Bond, Tag/Nacht und Stat-Verhältnisse werden für passende Regeln geprüft.
   - SpriteCollab-Normal-/Shiny-Dateien und Thumbnails für #161-251 sind lokal
     gepackt; `sprites-gen2-update.pak` ist ein inkrementelles Update.
   - `web/dev.html` bietet Auswahl und Testbuttons für alle 251 Arten ohne
     Terminal; die Firmware-Befehle sind nur im lokalen Testbuild aktiv.
12. `1.35.3-soft-step-local`
   - Persistenter Tages-/Gesamt-Schrittzähler mit 500/2.000/5.000-Trailbelohnungen
     und Trail-Rang-Meilensteinen.
   - Tagesschritte verbessern Wild-Shiny-Chance und Fangchance; Shiny-Wildkämpfe
     werden angezeigt und in der Shiny-Dexregistrierung gespeichert.
   - Der QMI-Hardwarezähler bleibt zur Diagnose sichtbar; Schritte werden aus
     gefilterten Beschleunigungsimpulsen erkannt. USB blockiert das Zählen nicht
     mehr; Roh-, Software- und USB-Status sind über `STATS`/`IMU` prüfbar.
13. `1.36.0-gen3-local`
   - Lokaler Dex und Spritebestand #1-386 mit Hoenn-Startern, allen Gen-3-Arten,
     sechs Sprachen und Gen-3-Evolutionsregeln.
   - Nur `tools/build_web_local.sh` erzeugt diesen Kandidaten. Der öffentliche
     Gen-2-Build bleibt unverändert und wird aus einem gepinnten Commit gebaut.
14. `1.36.0` Release
   - Öffentliches Gen-3-Buildprofil mit 386 Arten, aber ohne lokale Testbefehle.
   - Der Sprite-Schritt überträgt das Gen-1/2- und das Gen-3-Paket nacheinander.
   - Auf GitHub Pages aktiviert und als GitHub-Release veröffentlicht.
15. `1.36.1` (öffentlich)
   - Vollständiges Save-Backup/Restore per USB im Browser mit automatischem
     Sicherheits-Backup (Commit `release: publish save backup update v1.36.1`).
   - Aktueller Stand des öffentlichen Installers (`web/index.html`).
16. `1.36.2-hoenn-walk-local` (nur lokal)
   - Hoenn-Expeditionsorte und Schrittziele 250/500/1.000 für 15/30/60 Minuten
     mit optionalem Zusatz-Item; Save-Backup Version 2 enthält den Lauffortschritt.
   - Nicht veröffentlicht; laut Besitzer (Stand 2026-11-06) seit Wochen im Hardware-Dauerbetrieb
     ohne Auffälligkeiten (`HOENN_WALK_LOCAL.md`).

## Architektur und wichtige Dateien

- `TamaPoke.ino`: UI, Touch-Routing, Rendern, Karten, Minigames, Battle-Screen,
  Settings, Hilfe, lokaler Laufzeit-Zustand, IMU-Poll und Morgen-Overlay.
- `dayphase.h`: Stunde, Phase und visuelle Nacht aus RTC-Epoch.
- `imu.h` / `imu.cpp`: QMI8658 Poll, Shake-Kante, Pedometer-Delta.
- `pet.h` / `pet.cpp`: persistentes Pet-Modell, NVS Save/Load, Pflege,
  Progression, Pokedex, Catching, Events, Expedition und Items.
- `battle.h` / `battle.cpp`: testbare Battle-Logik und Typ-Multiplikatoren.
- `audio.h` / `audio.cpp`: Sound-Queue, ES8311, SFX und Spezies-Rufe.
- `species_chirp.h` / `species_chirp.cpp`: pro Dexnummer generierte,
  rechtlich unbedenkliche Syntheseprofile.
- `i18n.h` / `i18n.cpp`: alle sichtbaren UI-Texte und Dex-Namen.
- `time_utils.h`: rollover-sichere `deadlineActive`, `deadlineReached` und
  `deadlineRemaining` für `millis()`-Timer.
- `tests/pet_tests.cpp` und `tests/battle_tests.cpp`: native Regressionstests.
- `tools/build_web.sh`: erzeugt die vier separaten öffentlichen Gen-3-
  Installer-Binaries.
- `tools/build_web_gen3.sh`: erzeugt und validiert den debugfreien
  `1.36.1`-Release ohne den lokalen Debugbuild zu verwenden.
- `web/manifest.json` und `web/index.html`: Web-Installer. Die Parts werden
  getrennt geflasht, damit NVS/Save bei Updates erhalten bleibt.
- `web/dev.html` und `web/manifest-local.json`: lokaler Testinstaller, nicht für
  den öffentlichen GitHub-Pages-Flow.
- `web/release-gen3.html` und `web/manifest-gen3.json`: lokale Vorschau des
  öffentlichen Gen-3-Installers ohne Testknöpfe.

## Testen und lokales Flashen

Im Repository-Ordner (`TamaPoke`) ausführen:

```bash
cd tests && make clean && make test
cd .. && bash tools/build_web.sh
python3 -m http.server 8000 --directory web
```

Danach auf dem Mac Chrome oder Edge öffnen:

```text
http://127.0.0.1:8000/?v=1.36.1
```

Waveshare per USB verbinden und im Installer **Erase device deaktiviert lassen**.
Der lokale Server muss während des Flashens weiterlaufen. Der aktuelle
Web-Installer erwartet diese vier Dateien:

```text
web/firmware/tamapoke-1.36.1-bootloader.bin
web/firmware/tamapoke-1.36.1-partitions.bin
web/firmware/tamapoke-1.36.1-boot_app0.bin
web/firmware/tamapoke-1.36.1-app.bin
```

### Lokaler Testinstaller

Für Hardwaretests wird der abgesicherte lokale Buildweg verwendet:

```bash
bash tools/build_web_local.sh
# oder ohne Aenderung bestehender Installerdateien:
bash tools/build_web_local.sh --check
```

Die vier erzeugten Parts müssen unter den in `web/manifest-local.json`
genannten `1.36.2-hoenn-walk-local`-Namen liegen. Die Browserinstaller-Parts
werden für reproduzierbare lokale und öffentliche Tests versioniert. Danach:

```bash
python3 -m http.server 8000 --directory web
```

Im Browser `http://127.0.0.1:8000/dev.html` öffnen. Auch beim lokalen
Testupdate `Erase device` deaktiviert lassen.

### Öffentliche Gen-3-Release-Referenz

```bash
bash tools/build_web_gen3.sh
python3 -m http.server 8000 --directory web
```

Im Browser `http://127.0.0.1:8000/release-gen3.html` öffnen. Diese Seite hat
keine Debugbefehle und bietet genau einen verpflichtenden Komplett-Spriteknopf.
Die öffentliche Seite `web/index.html` hat denselben normalen Ablauf.

## Verifikation vor einer eventuellen Veröffentlichung

1. `cd tests && make clean && make test`
2. `bash tools/build_web.sh --check`, `bash tools/build_web_local.sh --check`
   und `bash tools/build_web_gen3.sh --check`
3. `git diff --check`
4. Hardware-Smoke-Test ohne Erase:
   - Save/Pet bleibt erhalten.
   - Hauptscreen-Pet mehrfach antippen: Ruf muss klar hörbar sein.
   - Profil öffnen: sechs sichtbare Ecken-/Akzentrahmen durchschalten; Portrait
     antippen prüfen.
   - Battle, Play-Menü, Memo, Expedition, Schlaf, PWR-Wakeup und Settings
     kurz prüfen.
   - Im lokalen Testbuild `TESTMON`, `TESTEVO`, `CAUGHT <dex>` und `BATTLE <dex>` prüfen; im
     öffentlichen Build sind diese Debug-Befehle absichtlich nicht vorhanden.
5. Erst nach ausdrücklicher Nutzerfreigabe committen/pushen/veröffentlichen.

## Offene Themen und sichere nächste Schritte

- Der Besitzer hat lokales Flashen, Gen-3-Sprites und reales Schrittzählen
  grundsätzlich auf Hardware bestätigt. Für die Release-Freigabe verbleibt
  der erweiterte Test: Serial `IMU`, `STEPS`,
  `WALK n`, Software-Schritte bei Screen-off und USB, Trail-Belohnungen,
  Wild-Shiny-Fang, Nacht-FOOD, Morgen-Overlay,
  Schlaf bleibt beim Schütteln. Schwellen nach der Session nachziehen.
- Die synthetischen Pet-Rufe und die sechs Profilrahmen auf dem echten Waveshare
  visuell/akustisch prüfen.
- Nach neuem Nutzerfeedback erneut gezielte Bug-Hunts machen. Bei Reviews immer
  zuerst echte Fehler, Save-Risiken und Touch-Hitboxen prüfen.
- Alle UI-Änderungen auf dem runden Screen auf abgeschnittenen Text und
  Fehleingaben prüfen.
- Keine neue große Battle-Funktion ohne Nutzerentscheidung; zuerst Marker,
  Rahmen, Touch-Hitboxen und Save-Sicherheit auf Hardware bestätigen.
- Historische Firmware-Binaries nicht erneut massenhaft in Git aufnehmen. Nur
  die vier aktuellen Installer-Parts einer freigegebenen Version gezielt
  veröffentlichen.

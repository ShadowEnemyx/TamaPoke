# TamaPoke Expanded - AI Handoff

Stand: 2026-08-23

## Projekt und Hardware

Dieses Repository ist eine stark erweiterte, community-orientierte Firmware fuer
das Waveshare ESP32-S3 Touch AMOLED 1.75. Es ist ein Fork von
`socquique/TamaPoke` und wird als "Expanded"-Variante gepflegt.

- Firmware-Entry-Point: `TamaPoke.ino`
- Ausgangs-Firmware-Stand: `1.32.1-caught-mark`
- Aktueller lokaler Gen-2/Wasserzeichen-/Schritt-Test: `1.35.1-step-trail-local` (nur ueber `TAMAPOKE_LOCAL_TEST`)
- Board: ESP32-S3, 16 MB Flash, OPI PSRAM, rundes 466x466 AMOLED, CST9217 Touch,
  PCF85063 RTC, AXP2101 PMU, ES8311 Audio
- Sprache: DE, EN, ES, FR, IT, PT. Code und UI-Texte verwenden aus
  Font-Gruenden weitgehend ASCII ohne Umlaute/Akzente.

Die Firmware speichert den Spielstand in ESP32-NVS. Bei einem Update darf der
Installer **nicht** mit `Erase device` ausgefuehrt werden, sonst wird der Save
geloescht.

## Wichtige Arbeitsregel

**Niemals auf GitHub pushen, Releases erstellen oder die PR aktualisieren, ohne
die ausdrueckliche Aufforderung des Nutzers.**

Der Nutzer moechte unfertige lokale Versionen erst auf seiner Hardware testen.
Lokales Bauen, Testen und ein lokaler Web-Installer sind immer erlaubt und
erwuenscht.

## Aktueller Arbeitsbaum

Der oeffentliche Installer bleibt auf dem Ausgangsstand. Fuer Hardwaretests
existieren lokal zusaetzlich `web/dev.html` und `web/manifest-local.json`; diese
Dateien sind bewusst nicht Teil des oeffentlichen Installationsflusses.

Aktuelle lokale Testguards in `TamaPoke.ino`:

- `TAMAPOKE_LOCAL_TEST` setzt die Anzeigeversion auf `1.35.1-step-trail-local`.
- Die Serial-Befehle `TESTMON`, `TESTEVO`, `CAUGHT`, `CAUGHT <dex>`, `BATTLE`
  und `BATTLE <dex>` sind nur in diesem Testbuild aktiv.
- Diese Testversion darf nicht versehentlich in `web/index.html` oder
  `web/manifest.json` eingetragen oder auf GitHub gepusht werden.

Aktueller Git-Zustand bei Erstellung dieser Datei:

- Branch: `local/full-gen2`
- `fork`: `https://github.com/ShadowEnemyx/TamaPoke.git`
- `origin`: `https://github.com/socquique/TamaPoke.git`
- Der Ausgangspunkt ist lokal als `3b24ea8` (`chore: save local baseline before gen2 watermark`)
  und zusaetzlich mit dem Tag `local-baseline-before-gen2-watermark` gesichert.
- Der lokale Featurestand ist als `feat: add gen2 starters and local watermark` gesichert;
  es wurde nichts gepusht.
- Der aktuell getestete, funktionierende lokale Stand ist als Tag
  `local-full-gen2-final` markiert; der Branch bleibt `local/full-gen2`.
- Der Arbeitsbaum enthaelt lokale, noch nicht veroeffentlichte Gen-2-,
  Wasserzeichen-, Lokalisierungs- und Sprite-Aenderungen. `web/index.html` und
  `web/manifest.json` bleiben auf dem oeffentlichen Ausgangsstand; nur
  `web/dev.html` und `web/manifest-local.json` zeigen auf den lokalen Build.
- Der Hauptautor hat die grosse Expanded-PR offen gelassen und verlinkt den Fork,
  moechte sie aber wegen Umfang, Branding und Binary-Historie nicht komplett in
  das Basisprojekt mergen. Kleine, spaetere Einzel-PRs waeren moeglich, aber nur
  nach Nutzerentscheidung.

## Vorhandene Funktionen

### Kernspiel

- Ei, Starterwahl, Schluetzen, Pflege, Schlaf, Hygiene, Hunger, Freude,
  Energie, Gewicht, Bindung, Spitznamen, Evolution, Farewell, Release und
  Runaway.
- Alter und Pflege laufen mit RTC auch bei ausgeschaltetem Display weiter;
  Offline-Fortschritt ist begrenzt.
- Pokedex/Gallery unterscheidet gezuechtete (`raised`) und gefangene (`caught`)
  Pokemon.
- Profil, Persoenlichkeit, Tagesziele, Medaillen, Fortschritt und
  Sammler-Rang sind ueber acht Swipe-Karten erreichbar.

### Battle

- Manuelle Wild Battles ueber die Battle-Karte, zusaetzlich seltene optionale
  Wild-Encounter-Prompts auf dem Hauptscreen.
- Gegner-Level liegen normalerweise nahe am Pet-Level, koennen aber auch einige
  Level darunter liegen. Wilde Legendaere sind in v1 nicht vorgesehen.
- Typen sind in den Kaempfen sichtbar und beeinflussen Schaden moderat.
- Aktionen: Quick, Heavy, Dodge/Counter, Rest und Run.
  - Quick: weniger Schaden, sicherer und reduziert eingehenden Schaden.
  - Heavy: mehr Schaden, aber der Gegner kann ausweichen/kontern.
  - Dodge: kann Counter fuer den naechsten Angriff vorbereiten.
  - Rest: maximal zweimal pro Kampf, heilt und gibt Guard.
- Kein Pokemon-Tod, kein Catching bei Niederlage. Siege/Niederlagen/Streaks
  sind persistent und geben moderate Trainingsbelohnungen.
- Nach einem Sieg gibt es genau einen optionalen Fangversuch. Bei knapper
  Niederlage kann es eine kleine "respect catch"-Chance geben.
- Im Kampf zeigt ein kleiner Pokeball rechts neben der Gegner-Namenszeile an,
  ob das gegnerische Pokemon bereits gefangen wurde. Das Symbol nutzt nur den
  bestehenden `dexCaught`-Bitmap und aendert keine Save-Struktur.

### Minigames und Events

- Play-Menue mit Ball, Catch, Memo, Clean und Type.
- Ball ist ein schweres Reaktionsspiel mit schneller/unvorhersehbarer Bewegung.
- Catch ist ein Reaktionsspiel mit zunehmend kurzen Zeitfenstern.
- Memo zeigt eine Farbsequenz, die nachgetippt werden muss; die Anleitung liegt
  optisch zwischen den Pad-Reihen und die Pads haben eigene Toene.
- Clean und Type ergaenzen Hygiene- bzw. Typen-/Angriffs-Training.
- Seltene, freiwillige Pet-Events (Berry, Heart, Sparkle) und seltene optionale
  Wild-Encounter unterbrechen andere UI-Modalen nicht.

### Expedition und Inventar

- Achte Karte `EXPEDITION` mit 15/30/60-Minuten-Touren.
- Ein kleiner Hauptscreen-Chip erscheint nur bei aktiver Tour, abholbarem Fund
  oder vorhandenen Items; ein Tap oeffnet direkt die Expeditions-Karte.
- Touren laufen per RTC weiter, auch wenn das Board ausgeschaltet ist.
- Belohnung wird beim Start festgelegt und persistiert.
- Inventar: Trail Snack, Energy Tonic, Care Kit und Train Token. Maximal drei
  jedes Items; Train Token oeffnet die ATK/DEF/SPD-Auswahl.
- Der Hauptscreen-Chip oeffnet direkt Karte 8 und zeigt Tour-Restzeit,
  abholbaren Fund oder Inventaranzahl.

### Einstellungen, Hilfe und Performance

- Settings: Sprache, Uhrzeit, vier Soundmodi und optionales Power Save.
- Power Save ist standardmaessig aus; es reduziert Idle-Rendering und nutzt
  Light Sleep nur bei Dimmung/Screen-Off. Pflege, RTC und Touch-Wakeup bleiben
  aktiv.
- Acht integrierte Hilfeseiten beschreiben Bedienung, Battle und Systeme.
- Statische Screens nutzen Dirty-Rendering; aktive Spiele/Battle bleiben
  regelmaessig gerendert.

### Bewegung, Tageszeit und Evolution

- `dayphase.h` liefert eine gemeinsame Morgen-/Tag-/Abend-/Nacht-Phase fuer
  Hintergrund, Wild-Pool und Pflegeverbrauch.
- Nachts sinkt FOOD im Wachzustand langsamer; Schlaf bleibt unveraendert.
- QMI8658-Schuetteln gibt begrenzt JOY. Der Pedometer zaehlt Schritte auch bei
  Screen-off; Tages-/Gesamtzaehler, Trail-Belohnungen sowie Wild-Shiny-/Fangbonus
  bleiben in NVS. USB-Laden verwirft Schritte, damit Bewegung nicht farmbar ist.
  Die Shake-Entprellung blockiert die Pedometer-Abfrage nicht; vier zusammen-
  haengende Schritte starten die Erkennung, danach wird jeder Schritt gemeldet.
- Evolution wird nie automatisch ausgefuehrt: Der rote CTA bleibt bei erreichtem
  Level sichtbar und erinnert bei zu niedrigen Pflegewerten. Form behalten wird
  auf Level 100 nach einem Spieltag erneut angeboten.

## Audio

Audio ist vollstaendig synthetisch ueber ES8311/I2S. Es werden keine originalen
Pokemon-Audiodateien oder ROM-Sounds benutzt.

- `SOUND_FULL` / TON VIEL: UI, Minigames, Battle, Ambient und Pet-Rufe.
- `SOUND_MED`: wichtige Care-, Battle-, Event- und Ergebnis-Sounds.
- `SOUND_LOW`: grosse Ereignisse und Warnungen.
- `SOUND_OFF`: stumm.

Die Spezies-Rufe und alle UI-/Battle-/Minigame-Sounds sind synthetisch:

- vier statt drei Toene, laenger und ohne Noise-Wave
- hoehere Synthese-Lautstaerke
- bei TON VIEL hat ein Pet-Tap Vorrang vor dem generischen Klick
- Pet-Tap, Galerie-Detail und Wildkampf haben eigene Ruf-/SFX-Pfade
- Soundmodi bleiben getrennt: VIEL, MITTEL, WENIG, AUS

Die Lautstaerke und Wirkung muessen weiterhin auf echter Hardware beurteilt
werden; Desktop-Builds koennen den ES8311-/Lautsprecherweg nicht ersetzen.

## Aktuelle lokale Aenderungen seit der letzten Veroeffentlichung

Die folgenden Aenderungen sind lokal implementiert, getestet und gebaut, aber
nicht gepusht:

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
   - Die gruennen Kreise im Profil waren Sammlerrahmen. Sie werden nicht mehr
     ueber dem Portrait gezeichnet.
   - Ein Tap auf das Profil-Portrait spielt jetzt den Spezies-Ruf.
3. `1.29.5-pet-chirps`
   - Klarere und hoerbarere, eigene synthetische Spezies-Rufe.
4. `1.30-expedition-hud`
   - Sichtbarer, runder-screen-tauglicher Einstieg zu Tour und Inventar auf
     dem Hauptscreen. Der Chip zeigt Tour-Restzeit, abholbaren Fund oder
     Inventaranzahl und bleibt in allen Modal-Ansichten verborgen.
5. `1.30.1-caught-frames`
   - Wildkaempfe zeigen links neben dem Gegner-HP-Balken einen kleinen
     Pokeball, wenn dieses Pokemon bereits gefangen wurde.
   - Profilrahmen sind wieder sichtbar: sechs Ecken-/Akzentvarianten liegen
     hinter dem Portrait und verdecken den Sprite nicht.
6. `1.31.0-day-imu`
   - Gemeinsame Tageszeit-API in `dayphase.h` (Morgen/Tag/Abend/Nacht).
   - Wach nachts: FOOD -1/Tick statt -2; Schlaf unveraendert. Offline-Minuten
     nutzen die Uhrzeit jeder Minute.
   - Wild-Pool nach Phase: Morgen Grass/Flying/Normal/Bug, Abend Water/Flying/Fire,
     Nacht Ghost/Poison/Bug. Tag bleibt ungefiltert. Keine Legends.
   - Nacht-Idle laeuft seltener. Ein Morgen-Overlay einmal pro Kalendertag,
     ohne Auto-Wecken.
   - QMI8658: Schuetteln gibt JOY auf dem Hauptscreen (Cooldown 25 s, 8/Tag).
     Schritte auch bei Screen-off; USB verwirft Steps. Serial: `IMU`, `SHAKE`,
     `WALK n`, `STEPS`, `STATS`. Die lokale Testseite bietet zusaetzlich klickbare
     `IMU`-/`STATS`-Diagnosebuttons; `STATS` zeigt auch `usb=0/1`.
7. `1.31.1-shake-fix`
   - Shake-Schwelle gesenkt (~1.45 g oder Gyro), Accel+Gyro, beide I2C-Adressen.
8. `1.32.0-evo-cta`
   - Roter Entwicklungs-Button bleibt, sobald das Level reicht, auch wenn ein
     Balken unter 40 liegt. Tippen erinnert dann an die Balken.
   - "Form behalten" auf Level 100 kommt nach einem Spieltag wieder.
9. `1.32.1-caught-mark`
   - Oeffentlicher Installerstand mit Fangmarker im Wildkampf.
   - Der Marker sitzt neben der Gegner-Namenszeile und zeigt nur bereits
     gefangene wilde Pokemon.
10. `1.32.1-local-test`
   - Lokale Testvariante mit zusaetzlichen Serial-Befehlen fuer Fangmarker und
     erzwungene Battle-Gegner. Nicht oeffentlich veroeffentlichen.
11. `1.34.0-gen2-full-local`
   - Vollstaendiger Dex #1-251 mit Gen-2-Namen, Werten, Typen, sechs Sprachen
     und 122 Evolutionsregeln inklusive Eevee-, Baby- und Tyrogue-Verzweigungen.
   - Eine Entwicklung benoetigt strikt drei von vier Pflegewerten ueber 40;
     Bond, Tag/Nacht und Stat-Verhaeltnisse werden fuer passende Regeln geprueft.
   - SpriteCollab-Normal-/Shiny-Dateien und Thumbnails fuer #161-251 sind lokal
     gepackt; `sprites-gen2-update.pak` ist ein inkrementelles Update.
   - `web/dev.html` bietet Auswahl und Testbuttons fuer alle 251 Arten ohne
     Terminal; die Firmware-Befehle sind nur im lokalen Testbuild aktiv.
12. `1.35.1-step-trail-local`
   - Persistenter Tages-/Gesamt-Schrittzaehler mit 500/2.000/5.000-Trailbelohnungen
     und Trail-Rang-Meilensteinen.
   - Tagesschritte verbessern Wild-Shiny-Chance und Fangchance; Shiny-Wildkaempfe
     werden angezeigt und in der Shiny-Dexregistrierung gespeichert.
   - IMU-Pedometer fuer kurze Gehstrecken responsiver gemacht; USB-/Sensorstatus
     ist ueber `STATS`/`IMU` pruefbar.

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
  `deadlineRemaining` fuer `millis()`-Timer.
- `tests/pet_tests.cpp` und `tests/battle_tests.cpp`: native Regressionstests.
- `tools/build_web.sh`: erzeugt die vier separaten Installer-Binaries.
- `web/manifest.json` und `web/index.html`: Web-Installer. Die Parts werden
  getrennt geflasht, damit NVS/Save bei Updates erhalten bleibt.
- `web/dev.html` und `web/manifest-local.json`: lokaler Testinstaller, nicht fuer
  den oeffentlichen GitHub-Pages-Flow.

## Testen und lokales Flashen

Im Repository-Ordner (`TamaPoke`) ausfuehren:

```bash
cd tests && make clean && make test
cd .. && bash tools/build_web.sh
python3 -m http.server 8000 --directory web
```

Danach auf dem Mac Chrome oder Edge oeffnen:

```text
http://127.0.0.1:8000/?v=1.32.1-caught-mark
```

Waveshare per USB verbinden und im Installer **Erase device deaktiviert lassen**.
Der lokale Server muss waehrend des Flashens weiterlaufen. Der aktuelle
Web-Installer erwartet diese vier Dateien:

```text
web/firmware/tamapoke-1.32.1-caught-mark-bootloader.bin
web/firmware/tamapoke-1.32.1-caught-mark-partitions.bin
web/firmware/tamapoke-1.32.1-caught-mark-boot_app0.bin
web/firmware/tamapoke-1.32.1-caught-mark-app.bin
```

### Lokaler Testinstaller

Fuer uncommittete Hardwaretests kann ein separates Testbuild erzeugt werden:

```bash
FQBN="esp32:esp32:esp32s3:CDCOnBoot=cdc,FlashSize=16M,PSRAM=opi,PartitionScheme=app3M_fat9M_16MB"
arduino-cli compile --fqbn "$FQBN" \
  --build-property compiler.cpp.extra_flags=-DTAMAPOKE_LOCAL_TEST \
  --build-path /tmp/tamapoke-gen2-local-build --export-binaries .
```

Die vier erzeugten Parts muessen unter den in `web/manifest-local.json`
genannten `1.35.1-step-trail-local`-Namen liegen. Die lokalen Parts sind
Build-Artefakte und bleiben bewusst von Git ignoriert. Danach:

```bash
python3 -m http.server 8000 --directory web
```

Im Browser `http://127.0.0.1:8000/dev.html` oeffnen. Auch beim lokalen
Testupdate `Erase device` deaktiviert lassen.

## Verifikation vor einer eventuellen Veroeffentlichung

1. `cd tests && make clean && make test`
2. `bash tools/build_web.sh`
3. `git diff --check`
4. Hardware-Smoke-Test ohne Erase:
   - Save/Pet bleibt erhalten.
   - Hauptscreen-Pet mehrfach antippen: Ruf muss klar hoerbar sein.
   - Profil oeffnen: sechs sichtbare Ecken-/Akzentrahmen durchschalten; Portrait
     antippen pruefen.
   - Battle, Play-Menue, Memo, Expedition, Schlaf, PWR-Wakeup und Settings
     kurz pruefen.
   - Im lokalen Testbuild `TESTMON`, `TESTEVO`, `CAUGHT <dex>` und `BATTLE <dex>` pruefen; im
     oeffentlichen Build sind diese Debug-Befehle absichtlich nicht vorhanden.
5. Erst nach ausdruecklicher Nutzerfreigabe committen/pushen/veroeffentlichen.

## Offene Themen und sichere naechste Schritte

- `1.35.1-step-trail-local` auf Hardware pruefen: Serial `IMU`, `STEPS`,
  `WALK n`, Schritte ohne USB, USB darf keine Schritte farmen, Trail-Belohnungen,
  Wild-Shiny-Fang, Nacht-FOOD, Morgen-Overlay,
  Schlaf bleibt beim Schuetteln. Schwellen nach der Session nachziehen.
- Die synthetischen Pet-Rufe und die sechs Profilrahmen auf dem echten Waveshare
  visuell/akustisch pruefen.
- Nach neuem Nutzerfeedback erneut gezielte Bug-Hunts machen. Bei Reviews immer
  zuerst echte Fehler, Save-Risiken und Touch-Hitboxen pruefen.
- Alle UI-Aenderungen auf dem runden Screen auf abgeschnittenen Text und
  Fehleingaben pruefen.
- Keine neue grosse Battle-Funktion ohne Nutzerentscheidung; zuerst Marker,
  Rahmen, Touch-Hitboxen und Save-Sicherheit auf Hardware bestaetigen.
- Historische Firmware-Binaries nicht erneut massenhaft in Git aufnehmen. Nur
  die vier aktuellen Installer-Parts einer freigegebenen Version gezielt
  veroeffentlichen.

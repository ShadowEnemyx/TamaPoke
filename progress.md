Original prompt: Vollständigen Gen-2-Plan lokal umsetzen und die Evolutionsvoraussetzung auf 3 von 4 Stats über 40% ändern.

## Aktueller lokaler Gen-3-Kandidat (2026-08-25)

- Branch: `local/full-gen3`; Rücksprung-Tag: `local-before-gen3`.
- Öffentlicher Installer und öffentliche Firmware bleiben unverändert bei
  `1.35.3-soft-step` und #1–251.
- Lokaler Build: `1.36.0-gen3-local` mit `TAMAPOKE_LOCAL_TEST`, sechs Sprachen
  und Dex #1–386.
- Gen-3 #252–386 enthält lokalisierte Namen, Typen, Basiswerte, seltene/
  legendäre Kennzeichnung und Spezialentwicklungen (Bond, Stat-Gate,
  Tageszeit sowie TamaPoke-freundliche Levelpfade).
- Starterwahl im lokalen Build: zuerst Kanto, Johto oder Hoenn, danach einer
  der drei Regions-Starter. Bestehende Spielstände bleiben unangetastet.
- 270 neue SpriteCollab-Dateien (Normal + Shiny) und 386 Miniaturen sind als
  `web/sprites-gen3-update.pak` (ca. 38 MB) sowie im lokalen vollständigen
  `web/sprites-gen3-full.pak` (ca. 105 MB) gepackt. Das öffentliche
  `web/sprites.pak` bleibt das stabile #1–251-Paket.
- Lokale Browserseite: `web/dev.html` + `web/manifest-local.json`; kein Push,
  Release oder GitHub-Pages-Update erfolgt.

## Fortschritt

- Gen-2-Dex #161–251, lokalisierte Namen, Werte und Evolutionsregeln integriert.
- Eevee-, Baby-, Tyrogue- und Gen-2-Branch-Regeln inklusive 3/4-Stats-Gate
  (strictly >40) ergänzt; insgesamt 122 Regeln.
- SpriteCollab-Normal-/Shiny-Pakete und Miniaturen für #161–251 erzeugt.
- Lokale Firmware mit `TAMAPOKE_LOCAL_TEST` kompiliert; natives Testprogramm besteht.
- Lokale Testseite enthält Auswahl für alle 251 Pokémon, Evolutionsziel-Auswahl und Paket-Buttons.
- Lokaler Build meldet `1.35.3-soft-step-local`; der öffentliche Installer wird als
  `1.35.3-soft-step` ohne Debug-Befehle gebaut.
- Persistenter Schrittzähler mit Tages-/Gesamtwert, 500/2.000/5.000-Trailbelohnungen,
  Trail-Rängen sowie verbessertem Wild-Shiny- und Fangbonus ergänzt.
- IMU-Polling korrigiert: Die Software-Schritterkennung filtert Beschleunigungs-
  impulse und zählt nach zwei rhythmischen Schritten; USB blockiert das Zählen
  nicht mehr. Die lokale Seite bietet dafür `IMU`- und `STATS`-Diagnosebuttons.

## Abschluss

- Browser-Testseite per Syntax-/Playwright-Check ohne Console-Fehler geprüft.
- Datenpakete, Firmware-Artefakte und Git-Diff geprüft; lokaler Commit erstellt.
- Rücksprung: Tag `local-before-full-gen2`; Schritt-Rücksprung: `local-before-steps`.
- Fertiger Schrittstand: `1.35.3-soft-step-local`; der öffentliche Build
  `1.35.3-soft-step` und die aktualisierte README sind auf `fork/main`.
- Final markiert auf Branch `local/full-gen2`: Tag `local-full-gen2-final`.

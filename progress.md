Original prompt: Vollständigen Gen-2-Plan lokal umsetzen und die Evolutionsvoraussetzung auf 3 von 4 Stats über 40% ändern.

## Fortschritt

- Gen-2-Dex #161–251, lokalisierte Namen, Werte und Evolutionsregeln integriert.
- Eevee-, Baby-, Tyrogue- und Gen-2-Branch-Regeln inklusive 3/4-Stats-Gate
  (strictly >40) ergänzt; insgesamt 122 Regeln.
- SpriteCollab-Normal-/Shiny-Pakete und Miniaturen für #161–251 erzeugt.
- Lokale Firmware mit `TAMAPOKE_LOCAL_TEST` kompiliert; natives Testprogramm besteht.
- Lokale Testseite enthält Auswahl für alle 251 Pokémon, Evolutionsziel-Auswahl und Paket-Buttons.
- Lokaler Build meldet `1.34.0-gen2-full-local`; öffentliche Manifest-/Installer-Dateien
  bleiben auf dem bisherigen Stand.

## Abschluss

- Browser-Testseite per Syntax-/Playwright-Check ohne Console-Fehler geprüft.
- Datenpakete, Firmware-Artefakte und Git-Diff geprüft; lokaler Commit erstellt.
- Rücksprung: Tag `local-before-full-gen2`; fertiger Stand: `local-full-gen2-ready`.

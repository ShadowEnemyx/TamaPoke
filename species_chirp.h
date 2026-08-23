#pragma once

#include <stdint.h>

// Eigene, synthetisierte Spezies-Chirps. Diese Profile enthalten keine
// aufgenommenen oder ROM-abgeleiteten Pokemon-Audiodaten.
enum ChirpWave : uint8_t {
  CHIRP_SQUARE = 0,
  CHIRP_TRI,
  CHIRP_SOFT,
  CHIRP_NOISE,
};

struct SpeciesChirpNote {
  uint16_t frequency;
  uint16_t durationMs;
  int16_t slide;
  uint8_t volume;
  uint8_t wave;
};

struct SpeciesChirpProfile {
  SpeciesChirpNote notes[4];
  uint8_t count;
};

// Liefert fuer jede enthaltene Dexnummer einen eigenen, melodischen Synthese-Ruf.
// Ungueltige Dexnummern liefern false und erzeugen nie Audio.
bool speciesChirpProfile(int16_t dex, SpeciesChirpProfile *out);

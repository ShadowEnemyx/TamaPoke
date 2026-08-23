#include "species_chirp.h"

#include "dex.h"

static uint16_t clampPitch(int value) {
  if (value < 140) return 140;
  if (value > 2600) return 2600;
  return (uint16_t)value;
}

static int typePitchOffset(uint8_t type) {
  switch (type) {
    case TYPE_ELECTRIC: return 210;
    case TYPE_FIRE: return 105;
    case TYPE_FLYING: return 150;
    case TYPE_ICE: return 170;
    case TYPE_PSYCHIC: return 125;
    case TYPE_WATER: return -35;
    case TYPE_GRASS: return -65;
    case TYPE_BUG: return -85;
    case TYPE_ROCK: return -200;
    case TYPE_GROUND: return -170;
    case TYPE_STEEL: return -130;
    case TYPE_GHOST: return -110;
    default: return 0;
  }
}

bool speciesChirpProfile(int16_t dex, SpeciesChirpProfile *out) {
  if (!out || dex < 1 || dex > DEX_COUNT) return false;

  const DexEntry &entry = DEX_TBL[dex];
  const uint8_t seed = (uint8_t)(dex * 53 + entry.bAtk * 3 + entry.bSpe);
  const int base = 430 + entry.bSpe * 5 + typePitchOffset(entry.type1);
  const int direction = (seed & 0x80) ? 1 : -1;
  const int span = 70 + (seed & 0x5F);

  out->count = 4;
  out->notes[0] = {
    clampPitch(base + (int)(seed & 0x1F) * 5),
    (uint16_t)(68 + (seed & 0x1F)),
    (int16_t)(direction * span),
    (uint8_t)(78 + ((seed >> 2) & 0x0F)),
    (uint8_t)(seed % 3),
  };
  out->notes[1] = {
    clampPitch(base + direction * (35 + ((seed >> 3) & 0x7F))),
    (uint16_t)(54 + ((seed >> 5) & 0x1F)),
    (int16_t)(-direction * (span / 2)),
    (uint8_t)(74 + ((seed >> 1) & 0x0F)),
    (uint8_t)((seed >> 3) % 3),
  };
  // Die dritte Frequenz enthaelt bewusst die Dexnummer direkt. Dadurch hat
  // jede enthaltene Spezies ein eindeutig anderes, eigenes Klangprofil.
  out->notes[2] = {
    (uint16_t)(220 + dex * 9),
    (uint16_t)(64 + ((seed >> 4) & 0x1F)),
    (int16_t)(direction * (30 + entry.bSpe)),
    (uint8_t)(80 + ((seed >> 4) & 0x0F)),
    (uint8_t)((seed + entry.type2) % 3),
  };
  out->notes[3] = {
    clampPitch(base + direction * (80 + (seed & 0x3F))),
    (uint16_t)(82 + ((seed >> 2) & 0x0F)),
    (int16_t)(-direction * (span + 35)),
    (uint8_t)(86 + ((seed >> 3) & 0x0B)),
    CHIRP_SOFT,
  };
  return true;
}

#pragma once

#include <stdint.h>

// Tageszeit aus der RTC-Epoch (UTC, wie rtcEpoch()/mktime).
// Stunde 13 ist der Fallback, wenn noch keine gültige Uhrzeit existiert.
inline int sceneHourFromEpoch(uint32_t epoch) {
  return epoch ? (int)((epoch / 3600UL) % 24UL) : 13;
}

inline uint32_t unixDayFromEpoch(uint32_t epoch) {
  return epoch ? epoch / 86400UL : 0;
}

inline uint32_t unixHourFromEpoch(uint32_t epoch) {
  return epoch ? epoch / 3600UL : 0;
}

// 0 Morgen 6-12, 1 Tag 12-18, 2 Abend 18-22, 3 Nacht 22-6
inline uint8_t dayPhaseFromHour(int hour) {
  if (hour >= 6 && hour < 12) return 0;
  if (hour >= 12 && hour < 18) return 1;
  if (hour >= 18 && hour < 22) return 2;
  return 3;
}

inline uint8_t dayPhaseFromEpoch(uint32_t epoch) {
  return dayPhaseFromHour(sceneHourFromEpoch(epoch));
}

inline bool isNightPhase(uint8_t phase) {
  return phase == 3;
}

// Visuelle Nacht: schlafend oder Himmel nach 20:00 / vor 6:00.
// Die Spielphase "Nacht" beginnt erst um 22:00.
inline bool isVisualNight(int hour, bool sleeping) {
  return sleeping || hour < 6 || hour >= 20;
}

inline uint8_t nightFoodDrop(uint32_t epoch) {
  return isNightPhase(dayPhaseFromEpoch(epoch)) ? 1 : 2;
}

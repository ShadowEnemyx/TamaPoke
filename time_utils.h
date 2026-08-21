#pragma once

#include <stdint.h>

// Sichere Vergleiche fuer millis()-Deadlines. Durch die signed Differenz
// funktionieren sie auch, wenn der 32-Bit-Zaehler nach rund 49 Tagen umspringt.
inline bool deadlineActive(uint32_t now, uint32_t deadline) {
  return deadline != 0 && (int32_t)(now - deadline) < 0;
}

inline bool deadlineReached(uint32_t now, uint32_t deadline) {
  return deadline != 0 && (int32_t)(now - deadline) >= 0;
}

inline uint32_t deadlineRemaining(uint32_t now, uint32_t deadline) {
  return deadlineActive(now, deadline) ? deadline - now : 0;
}

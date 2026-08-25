#pragma once
#include <stdint.h>

// Validates the complete TPTH thumbnail index and every variable-size entry.
bool validateThumbBlob(const uint8_t *data, uint32_t size, uint16_t maxCount,
                       uint16_t *countOut = nullptr);

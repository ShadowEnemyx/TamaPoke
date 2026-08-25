#include "thumb_format.h"
#include <string.h>

bool validateThumbBlob(const uint8_t *blob, uint32_t size, uint16_t maxCount,
                       uint16_t *countOut) {
  if (!blob || size < 6 || memcmp(blob, "TPTH", 4) != 0) return false;
  uint16_t parsedCount;
  memcpy(&parsedCount, blob + 4, sizeof(parsedCount));
  if (parsedCount == 0 || parsedCount > maxCount) return false;
  uint32_t tableEnd = 6UL + (uint32_t)parsedCount * 4UL;
  if (tableEnd > size) return false;

  for (uint16_t i = 0; i < parsedCount; i++) {
    uint32_t off;
    memcpy(&off, blob + 6 + (uint32_t)i * 4, sizeof(off));
    if (off < tableEnd || off > size - 3) return false;
    uint8_t w = blob[off];
    uint8_t h = blob[off + 1];
    uint8_t palCount = blob[off + 2];
    if (w == 0 || h == 0 || palCount == 0) return false;
    uint32_t pixelCount = (uint32_t)w * h;
    uint32_t entrySize = 3UL + (uint32_t)palCount * 2UL + pixelCount;
    if (entrySize > size - off) return false;
    const uint8_t *pixels = blob + off + 3 + (uint32_t)palCount * 2UL;
    for (uint32_t px = 0; px < pixelCount; px++)
      if (pixels[px] != 0xFF && pixels[px] >= palCount) return false;
  }
  if (countOut) *countOut = parsedCount;
  return true;
}

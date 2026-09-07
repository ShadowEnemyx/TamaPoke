#!/usr/bin/env python3
"""Fail-closed validation for TamaPoke installer firmware and TPAK bundles."""

import argparse
import json
from pathlib import Path
import re
import struct


def validate_thumbs(blob: bytes, expected_count: int, source: str) -> None:
    if len(blob) < 6 or blob[:4] != b"TPTH":
        raise SystemExit(f"{source}: invalid TPTH header")
    count = struct.unpack_from("<H", blob, 4)[0]
    if count != expected_count:
        raise SystemExit(f"{source}: {count} thumbnails, expected {expected_count}")
    table_end = 6 + count * 4
    if table_end > len(blob):
        raise SystemExit(f"{source}: truncated thumbnail offset table")
    offsets = struct.unpack_from(f"<{count}I", blob, 6)
    previous = table_end
    for index, offset in enumerate(offsets, 1):
        if offset < table_end or offset < previous or offset + 3 > len(blob):
            raise SystemExit(f"{source}: invalid thumbnail offset for entry {index}")
        width, height, palette_count = struct.unpack_from("<BBB", blob, offset)
        if not width or not height or not palette_count:
            raise SystemExit(f"{source}: invalid thumbnail dimensions/palette for entry {index}")
        entry_end = offset + 3 + palette_count * 2 + width * height
        next_offset = offsets[index] if index < count else len(blob)
        if entry_end != next_offset:
            raise SystemExit(f"{source}: invalid thumbnail payload for entry {index}")
        pixels = blob[offset + 3 + palette_count * 2:entry_end]
        if any(pixel != 0xFF and pixel >= palette_count for pixel in pixels):
            raise SystemExit(f"{source}: invalid palette index for entry {index}")
        previous = offset


def validate_pak(path: Path, expected_files: int, expected_thumbs: int | None = None) -> None:
    blob = path.read_bytes()
    if len(blob) < 6 or blob[:4] != b"TPAK":
        raise SystemExit(f"{path}: invalid TPAK header")
    count = struct.unpack_from("<H", blob, 4)[0]
    if count != expected_files:
        raise SystemExit(f"{path}: {count} entries, expected {expected_files}")
    pos = 6
    entries = []
    for _ in range(count):
        if pos >= len(blob):
            raise SystemExit(f"{path}: truncated index")
        name_len = blob[pos]
        pos += 1
        if pos + name_len + 4 > len(blob):
            raise SystemExit(f"{path}: truncated index entry")
        name = blob[pos:pos + name_len].decode("utf-8")
        pos += name_len
        size = struct.unpack_from("<I", blob, pos)[0]
        pos += 4
        entries.append((name, size))
    names = [name for name, _ in entries]
    if len(names) != len(set(names)):
        raise SystemExit(f"{path}: duplicate bundle names")
    if pos + sum(size for _, size in entries) != len(blob):
        raise SystemExit(f"{path}: indexed data size does not match file size")
    if expected_thumbs is not None:
        data_pos = pos
        thumb_blob = None
        for name, size in entries:
            if name == "mons/thumbs.bin":
                thumb_blob = blob[data_pos:data_pos + size]
            data_pos += size
        if thumb_blob is None:
            raise SystemExit(f"{path}: mons/thumbs.bin is missing")
        validate_thumbs(thumb_blob, expected_thumbs, f"{path}:mons/thumbs.bin")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--dex-header", type=Path)
    parser.add_argument("--app", type=Path)
    parser.add_argument("--pak", type=Path, required=True)
    parser.add_argument("--manifest", type=Path)
    parser.add_argument("--expected-version")
    parser.add_argument("--expected-dex", type=int)
    parser.add_argument("--expected-files", type=int, required=True)
    parser.add_argument("--expected-thumbs", type=int)
    args = parser.parse_args()

    if args.dex_header:
        match = re.search(r"^#define DEX_COUNT (\d+)$", args.dex_header.read_text(), re.MULTILINE)
        if not match or int(match.group(1)) != args.expected_dex:
            raise SystemExit(f"{args.dex_header}: DEX_COUNT is not {args.expected_dex}")
    if args.app:
        if not args.expected_version:
            raise SystemExit("--app requires --expected-version")
        if args.expected_version.encode() not in args.app.read_bytes():
            raise SystemExit(f"{args.app}: firmware version {args.expected_version!r} not embedded")
    if args.manifest:
        manifest = json.loads(args.manifest.read_text())
        if manifest.get("version") != args.expected_version:
            raise SystemExit(f"{args.manifest}: manifest version mismatch")
        expected_names = {
            f"firmware/tamapoke-{args.expected_version}-{suffix}.bin"
            for suffix in ("bootloader", "partitions", "boot_app0", "app")
        }
        actual_names = {
            part.get("path")
            for build in manifest.get("builds", [])
            for part in build.get("parts", [])
        }
        if actual_names != expected_names:
            raise SystemExit(f"{args.manifest}: firmware paths do not match version")
    validate_pak(args.pak, args.expected_files, args.expected_thumbs)
    print(f"OK: {args.pak} ({args.expected_files} entries)")


if __name__ == "__main__":
    main()

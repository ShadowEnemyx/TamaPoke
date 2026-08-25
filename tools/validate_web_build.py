#!/usr/bin/env python3
"""Fail-closed validation for TamaPoke installer firmware and TPAK bundles."""

import argparse
import json
from pathlib import Path
import re
import struct


def validate_pak(path: Path, expected_files: int) -> None:
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


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--dex-header", type=Path)
    parser.add_argument("--app", type=Path)
    parser.add_argument("--pak", type=Path, required=True)
    parser.add_argument("--manifest", type=Path)
    parser.add_argument("--expected-version")
    parser.add_argument("--expected-dex", type=int)
    parser.add_argument("--expected-files", type=int, required=True)
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
    validate_pak(args.pak, args.expected_files)
    print(f"OK: {args.pak} ({args.expected_files} entries)")


if __name__ == "__main__":
    main()

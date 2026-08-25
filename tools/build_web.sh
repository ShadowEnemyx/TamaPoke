#!/bin/bash
# Builds the stable public Gen-2 installer from its immutable source snapshot.
# The current branch may contain a larger local Dex and is never compiled here.
set -euo pipefail

cd "$(dirname "$0")/.."
ROOT="$PWD"
PUBLIC_COMMIT="c5d3ca6959f3c80519cccc70990ded05ca38c28b"
VERSION="1.35.3-soft-step"
CHECK_ONLY=0

if [[ ${1:-} == "--check" ]]; then
  CHECK_ONLY=1
  shift
fi
if [[ $# -ne 0 ]]; then
  echo "Usage: bash tools/build_web.sh [--check]" >&2
  exit 2
fi

git cat-file -e "$PUBLIC_COMMIT^{commit}"
STAGE="$(mktemp -d "${TMPDIR:-/tmp}/tamapoke-public.XXXXXX")"
trap 'rm -rf "$STAGE"' EXIT
mkdir -p "$STAGE/TamaPoke"
git archive "$PUBLIC_COMMIT" | tar -x -C "$STAGE/TamaPoke"

echo "Building pinned public Gen-2 source $PUBLIC_COMMIT..."
(cd "$STAGE/TamaPoke" && bash tools/build_web.sh)

python3 "$ROOT/tools/validate_web_build.py" \
  --dex-header "$STAGE/TamaPoke/dex.h" \
  --app "$STAGE/TamaPoke/web/firmware/tamapoke-$VERSION-app.bin" \
  --pak "$STAGE/TamaPoke/web/sprites.pak" \
  --manifest "$ROOT/web/manifest.json" \
  --expected-version "$VERSION" --expected-dex 251 --expected-files 503

if [[ $CHECK_ONLY -eq 1 ]]; then
  echo "CHECK OK: public installer files were not changed."
  exit 0
fi

for suffix in bootloader partitions boot_app0 app; do
  src="$STAGE/TamaPoke/web/firmware/tamapoke-$VERSION-$suffix.bin"
  dst="$ROOT/web/firmware/tamapoke-$VERSION-$suffix.bin"
  cp "$src" "$dst.new"
  mv "$dst.new" "$dst"
done
cp "$STAGE/TamaPoke/web/sprites.pak" "$ROOT/web/sprites.pak.new"
mv "$ROOT/web/sprites.pak.new" "$ROOT/web/sprites.pak"
echo "OK: stable public Gen-2 installer refreshed from pinned source."

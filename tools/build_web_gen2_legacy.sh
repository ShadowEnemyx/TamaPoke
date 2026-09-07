#!/bin/bash
# Read-only reproducibility check for the former public Gen-2 installer.
set -euo pipefail

if [[ ${1:-} != "--check" || $# -ne 1 ]]; then
  echo "Usage: bash tools/build_web_gen2_legacy.sh --check" >&2
  exit 2
fi

cd "$(dirname "$0")/.."
ROOT="$PWD"
PUBLIC_COMMIT="c5d3ca6959f3c80519cccc70990ded05ca38c28b"
VERSION="1.35.3-soft-step"
STAGE="$(mktemp -d "${TMPDIR:-/tmp}/tamapoke-gen2-legacy.XXXXXX")"
trap 'rm -rf "$STAGE"' EXIT
mkdir -p "$STAGE/TamaPoke"
git archive "$PUBLIC_COMMIT" | tar -x -C "$STAGE/TamaPoke"

echo "Building pinned legacy Gen-2 source $PUBLIC_COMMIT..."
(cd "$STAGE/TamaPoke" && bash tools/build_web.sh)
python3 "$ROOT/tools/validate_web_build.py" \
  --dex-header "$STAGE/TamaPoke/dex.h" \
  --app "$STAGE/TamaPoke/web/firmware/tamapoke-$VERSION-app.bin" \
  --pak "$STAGE/TamaPoke/web/sprites.pak" \
  --manifest "$STAGE/TamaPoke/web/manifest.json" \
  --expected-version "$VERSION" --expected-dex 251 --expected-files 503 --expected-thumbs 251
echo "CHECK OK: legacy Gen-2 artifacts were built only in a temporary directory."

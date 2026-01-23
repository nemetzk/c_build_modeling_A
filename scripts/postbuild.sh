#!/usr/bin/env bash
set -euo pipefail

BIN_PATH="${1:-}"
if [[ -z "$BIN_PATH" ]]; then
  echo "[postbuild] usage: postbuild.sh <path-to-binary>" >&2
  exit 2
fi

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
OUT_DIR="$ROOT_DIR/build"

mkdir -p "$OUT_DIR"

if command -v strip >/dev/null 2>&1; then
  STRIPPED="$OUT_DIR/$(basename "$BIN_PATH").stripped"
  cp -f "$BIN_PATH" "$STRIPPED"
  strip "$STRIPPED" || true
  echo "[postbuild] stripped -> $STRIPPED"
fi

if command -v sha256sum >/dev/null 2>&1; then
  sha256sum "$BIN_PATH" > "$OUT_DIR/$(basename "$BIN_PATH").sha256"
  echo "[postbuild] sha256 -> $OUT_DIR/$(basename "$BIN_PATH").sha256"
fi

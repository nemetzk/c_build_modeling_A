#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
OUT="$ROOT_DIR/include/version.h"

TS="$(date -u +"%Y-%m-%dT%H:%M:%SZ")"
GIT_HASH="nogit"
if command -v git >/dev/null 2>&1 && git -C "$ROOT_DIR" rev-parse --is-inside-work-tree >/dev/null 2>&1; then
  GIT_HASH="$(git -C "$ROOT_DIR" rev-parse --short HEAD)"
fi

cat > "$OUT" <<EOF
#pragma once
#define APP_NAME "pilot-c-tui"
#define BUILD_TIMESTAMP_UTC "${TS}"
#define GIT_HASH "${GIT_HASH}"
EOF

echo "[prebuild] generated: $OUT"

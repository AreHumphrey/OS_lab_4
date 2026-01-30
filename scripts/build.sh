#!/bin/bash
set -e

BUILD_TYPE="${1:-Debug}"
SCRIPT_DIR="$(cd -- "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"
LAB4_ROOT="$(cd -- "${SCRIPT_DIR}/.." && pwd -P)"

echo "========================================"
echo " Building lab4 (Linux) "
echo "========================================"
echo "Build type: ${BUILD_TYPE}"
echo "Project dir: ${LAB4_ROOT}"
echo ""

mkdir -p "${LAB4_ROOT}/build"
cd "${LAB4_ROOT}/build"

cmake -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" ..
make -j4

echo ""
echo "========================================"
echo " Build completed successfully "
echo " Executable: ${LAB4_ROOT}/build/lab4_main"
echo "========================================"

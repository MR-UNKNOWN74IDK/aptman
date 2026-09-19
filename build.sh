#!/bin/bash
set -euo pipefail

RED='\033[0;31m'; GREEN='\033[0;32m'; YELLOW='\033[1;33m'; BLUE='\033[0;34m'; NC='\033[0m'

BUILD_TYPE="Release"
CLEAN=0
INSTALL=0

while [[ $# -gt 0 ]]; do
    case "$1" in
        --debug|-d) BUILD_TYPE="Debug"; shift ;;
        --clean|-c) CLEAN=1; shift ;;
        --install|-i) INSTALL=1; shift ;;
        --help|-h)
            echo "Usage: $0 [--debug] [--clean] [--install]"
            echo "  --debug   Debug mode (-O0 -g)"
            echo "  --clean   force reconfiguration"
            echo "  --install install to /usr/local/bin"
            exit 0
            ;;
        *) echo -e "${RED}Unknown argument: $1${NC}"; exit 1 ;;
    esac
done

# 1. Check and install base dependencies
echo -e "${BLUE}Checking build dependencies...${NC}"
check_dep() {
    if ! command -v "$1" &>/dev/null; then
        echo "Installing $1..."
        sudo pacman -S --needed --noconfirm "$2"
    fi
}
check_dep cmake cmake
check_dep g++ gcc
check_dep ninja ninja

# 2. Verify CMake version >= 4.3
REQ_VER="4.3"
CUR_VER=$(cmake --version | head -n1 | grep -oP '[0-9]+\.[0-9]+\.[0-9]+')
if [ "$(printf '%s\n' "$REQ_VER" "$CUR_VER" | sort -V | head -n1)" != "$REQ_VER" ]; then
    echo -e "${RED}Error: CMake requires >= $REQ_VER, current version is $CUR_VER${NC}"
    echo "Please update: sudo pacman -S cmake"
    exit 1
fi
echo -e "${GREEN}CMake version: $CUR_VER ✓${NC}"

# 3. Choose a generator (prefer Ninja)
if command -v ninja &>/dev/null; then
    GENERATOR="Ninja"
    echo -e "${GREEN}Generator: Ninja${NC}"
else
    GENERATOR="Unix Makefiles"
    echo -e "${YELLOW}Generator: Make (installing ninja is recommended)${NC}"
fi

# 4. Clean/create the build directory
if [ "$CLEAN" -eq 1 ] && [ -d "build" ]; then
    echo "Cleaning build directory..."
    rm -rf build
fi
mkdir -p build

# 5. Configure
echo -e "${BLUE}Configuring project ($BUILD_TYPE)...${NC}"
cmake -B build -S . \
    -G "$GENERATOR" \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DCMAKE_COLOR_DIAGNOSTICS=ON

# 6. Build
JOBS=$(nproc)
echo -e "${BLUE}Building (parallel jobs: $JOBS)...${NC}"
cmake --build build --parallel "$JOBS"

# 7. Install or show a hint
if [ "$INSTALL" -eq 1 ]; then
    echo -e "${GREEN}Installing to /usr/local/bin/aptman${NC}"
    sudo install -Dm755 build/aptman /usr/local/bin/aptman
    echo -e "${GREEN}Done! Run: aptman${NC}"
else
    echo -e "${GREEN}Build complete! Run: ./build/aptman${NC}"
fi
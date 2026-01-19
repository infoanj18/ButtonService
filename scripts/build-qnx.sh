#!/bin/bash

set -e

cd $(dirname $0)/..

PROJECT_DIR="$(pwd)"
BUILD_DIR="${PROJECT_DIR}/build-qnx"
TOOLCHAIN_FILE="$PROJECT_DIR/scripts/qnx-toolchainfile.cmake"

QNX="${QNX:-$HOME/qnx710}"
source "$QNX/qnxsdp-env.sh"

rm -rf $BUILD_DIR
mkdir -p $BUILD_DIR
cmake -B$BUILD_DIR \
    -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_FILE \
    $PROJECT_DIR
cmake --build $BUILD_DIR

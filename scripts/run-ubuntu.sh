#!/bin/bash

set -e

cd $(dirname $0)/..

PROJECT_DIR="$(pwd)"
BUILD_DIR="${PROJECT_DIR}/build-ubuntu"

cmake --build $BUILD_DIR
$BUILD_DIR/impl/Button-Service
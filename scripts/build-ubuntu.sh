#!/bin/bash

set -e

cd $(dirname $0)/..

PROJECT_DIR="$(pwd)"
BUILD_DIR="${PROJECT_DIR}/build-ubuntu"

rm -rf $BUILD_DIR
mkdir -p $BUILD_DIR
cmake -B$BUILD_DIR\
     -DCMAKE_BUILD_TYPE="Debug"\
      $PROJECT_DIR

cmake --build $BUILD_DIR --parallel=$(nproc)

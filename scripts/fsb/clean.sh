#!/bin/bash

set -e
cd $(dirname $0)
PROJECT_HOME="$(pwd)/../../"

source setup_env.sh

cd $FSB_DIR

fsb clean button-service

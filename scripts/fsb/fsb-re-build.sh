#!/bin/bash

# This script is just the fsb commands
# Use the re-build.sh script for builds

cd $(dirname $0)

source ./setup_env.sh
BUTTON_SERVICE_HOME=$(pwd)/../../

cd $FSB_DIR

time (
    fsb make --no-depends --force button-service
);

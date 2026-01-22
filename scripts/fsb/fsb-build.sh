#!/bin/bash

# This script is just the fsb commands
# Use the build.sh script for builds

cd $(dirname $0)

source ./setup_env.sh
BUTTON_SERVICE_HOME=$(pwd)/../../

cd $FSB_DIR

# runs builds in parallel and only builds dependencies once
# button-service-source is not required as it is a dependency of the builds
fsb make --force button-service

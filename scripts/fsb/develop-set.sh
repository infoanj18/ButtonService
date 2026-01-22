#!/bin/bash

set -e
cd $(dirname $0)
PROJECT_HOME="$(pwd)/../../"

source setup_env.sh

# only enable if it's needed
if [ "$(grep -c button-service $FSB_DIR/.fsb.yaml)" -lt 4 ]; then
    cd $FSB_DIR

    fsb develop --source-path $PROJECT_HOME button-service-source
    fsb develop --source-path $PROJECT_HOME button-service 
fi

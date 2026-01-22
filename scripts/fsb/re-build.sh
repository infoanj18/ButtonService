#!/bin/bash

# This script builds button-service in fsb
# It will work for both native fsb intalls and docker installs
#
# This variant skips dependencies
# If your dependencies are not built, use build.sh
# Your dependencies are built if your have successfully built button-service
# You will need to use the build script again if you make changes in phx-fsb

set -e
cd $(dirname $0)

source setup_env.sh

# The current run-fsb-docker command will not accept arguments
# so we have to give it its own script file to execute
FSB_SCRIPT="$(pwd)/fsb-re-build.sh"
BUTTON_SERVICE_HOME=$(realpath "$(pwd)/../../")

bash "${BUTTON_SERVICE_HOME}/scripts/fsb/develop-set.sh"

cd $FSB_DIR
if ! command -v run-fsb-docker >/dev/null 2>&1
then # no run-fsb-docker, so the install is native
    $FSB_SCRIPT
else # yes run-fsb-docker, run the commands in the container
    run-fsb-docker -v $BUTTON_SERVICE_HOME -w $FSB_DIR -c "$FSB_SCRIPT"
fi

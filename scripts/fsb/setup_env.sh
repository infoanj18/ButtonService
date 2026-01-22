#!/bin/bash

set -e

if [ -e local_env.sh ]
then
    source local_env.sh

    if [ -z "$PHX_FSB" ]
    then
        echo >&2 "==local_env.sh=="
        echo >&2 "$(< local_env.sh)"
        echo >&2 "==ERROR: FSB directory is missing=="
        exit 1
    else
        FSB_DIR="$PHX_FSB"
    fi

    COVERAGE_DIR_NAME="coverage"
    TARGET_COVERAGE_DIR="${TARGET_DEST_DIR}/${COVERAGE_DIR_NAME}"

else
    echo
    echo >&2 "ERROR: scripts/fsb/local_env.sh is missing"
    echo
    echo "Sample local_env.sh:"
    echo
    echo "#!/bin/bash"
    echo "PHX_FSB=\"$HOME/workspace/phx-fsb\""
    echo "TARGET_ADDRESS=\"root@10.1.0.3\""
    echo "SSH_KEY_PATH=\"$HOME/.ssh/PDC-dev\""
    echo "TARGET_DEST_DIR=\"/data/button-service\""
    echo

    exit 1
fi

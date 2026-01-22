#!/bin/bash

set -e

cd $(dirname $0)
source setup_env.sh

ssh -i "${SSH_KEY_PATH}" "${TARGET_ADDRESS}" sh -l -c 'mount -uw /fs/os' || true

echo $(pwd)
bash stop_service.sh

# Create target directory (remove if it's a file first)
ssh -i $SSH_KEY_PATH $TARGET_ADDRESS "[ -f ${TARGET_DEST_DIR} ] && rm ${TARGET_DEST_DIR}; mkdir -p ${TARGET_DEST_DIR}" || true

# giving the service a delay to terminate is a good idea
sleep 2

# copy the binary over
scp -C -i $SSH_KEY_PATH\
    $PHX_FSB/output/phoenix_hi/package/button-service/stage/aarch64le/bin/Button-Service \
    $TARGET_ADDRESS:"${TARGET_DEST_DIR}/Button-Service"

bash start_service.sh

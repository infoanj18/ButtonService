#!/bin/bash

set -e

cd $(dirname $0)
source setup_env.sh

echo "Starting Service"
ssh -i $SSH_KEY_PATH $TARGET_ADDRESS "cd ${TARGET_DEST_DIR} && (./Button-Service >button-service.log 2>&1 </dev/null &)"
sleep 1
echo "Service Started"

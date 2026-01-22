#!/bin/bash

set -e
cd $(dirname $0)

source setup_env.sh

echo "Stopping Service"
ssh -i $SSH_KEY_PATH $TARGET_ADDRESS sh -l -c 'slay Button-Service'
echo "Service Stopped"

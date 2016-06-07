#!/bin/bash
export DEST="./.exvim.network"
export TOOLS="/root/exvim//vimfiles/tools/"
export TMP="${DEST}/_ID"
export TARGET="${DEST}/ID"
sh ${TOOLS}/shell/bash/update-idutils.sh

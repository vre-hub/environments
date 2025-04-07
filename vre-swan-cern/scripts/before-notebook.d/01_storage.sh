#!/bin/bash

# Author: Danilo Piparo, Enric Tejedor, Pedro Maximino, Diogo Castro 2023
# Copyright CERN
# Here the storage environment is prepared, to ensure the user is able to access
# their home directory (EOS for CERN users).

# The $HOME directory is specified upstream in the Spawner
if [[ $HOME == /eos/* ]]; then export CERNBOX_HOME=$HOME; fi

# Remove the last slash from HOME
export HOME="${HOME%/}"

# Store the oAuth token given by the spawner inside a file
# so that EOS can use it
if [[ ! -z "$ACCESS_TOKEN" ]];
then
    _log "Storing oAuth token for EOS"
    export OAUTH2_FILE=/tmp/eos_oauth.token
    export OAUTH2_TOKEN="FILE:$OAUTH2_FILE"
    echo -n oauth2:$ACCESS_TOKEN:$OAUTH_INSPECTION_ENDPOINT >& $OAUTH2_FILE
    chown -R $NB_USER:$NB_GID $OAUTH2_FILE
    chmod 600 $OAUTH2_FILE
fi

set +e
run_as_user 'if [[ ! -d "$HOME" || ! -x "$HOME" ]]; then exit 1; fi'
if [ $? -ne 0 ]
then
    _log "Error setting notebook working directory, $HOME not accessible by user $NB_USER."
    exit 1
fi
set -e

# Change the user home to point to EOS.
if [[ ! -z "$CERNBOX_HOME" && ! $(usermod --home $HOME $NB_USER 2>&1 | grep "no changes" > /dev/null) ]]; 
then
    _log "Updated the user home to $HOME."
fi

# Make sure the user has the SWAN_projects folder
run_as_user mkdir -p $HOME/SWAN_projects

_log "Finished setting up user session storage"

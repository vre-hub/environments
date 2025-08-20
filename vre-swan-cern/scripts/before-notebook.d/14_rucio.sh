#!/bin/bash

# Author: Giovanni Guerrieri, Enrique Garcia Garcia 2025
# Copyright CERN
# This script configures the environment for the usage 
# of the Rucio JupyterLab extension.

# RUCIO_JUPYTERLAB_VERSION is set in the Dockerfile
if [[ -z "$RUCIO_JUPYTERLAB_VERSION" ]]; then
    echo "RUCIO_JUPYTERLAB_VERSION is not set. Please set it to the desired version."
    exit 1
fi

# Check if the Rucio JupyterLab version is available
if [[ ! -d "/cvmfs/sw.escape.eu/rucio-jupyterlab/${RUCIO_JUPYTERLAB_VERSION}" ]]; then
    echo "Rucio JupyterLab version ${RUCIO_JUPYTERLAB_VERSION} is not available."
    exit 1
fi

# Set up the environment for Rucio JupyterLab
_log "Setting up Rucio JupyterLab environment for version ${RUCIO_JUPYTERLAB_VERSION}..."

RUCIO_CVMFS_PATH="/cvmfs/sw.escape.eu/rucio-jupyterlab/${RUCIO_JUPYTERLAB_VERSION}"

export RUCIO_HOME="${RUCIO_CVMFS_PATH}"
export PATH="$RUCIO_HOME/bin:$PATH"
export PYTHONPATH="$PYTHONPATH:${RUCIO_CVMFS_PATH}/lib/python3.11/site-packages"
export RUCIO_CA_CERT=$RUCIO_HOME/etc/rucio_ca.pem
export RUCIO_PYTHONBIN=python

echo $PYTHONPATH | grep -q "${RUCIO_CVMFS_PATH}/lib/python3.11/site-packages"
echo $PATH | grep -q "${RUCIO_HOME}/bin"

_log "Rucio JupyterLab environment set up successfully."


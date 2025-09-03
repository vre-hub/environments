#!/bin/bash

# Author: Giovanni Guerrieri, Enrique Garcia Garcia 2025
# Copyright CERN
# This script configures the environment for the usage 
# of the Rucio JupyterLab extension.

# RUCIO_JUPYTERLAB_VERSION is set in the Dockerfile
if [[ -z "$RUCIO_JUPYTERLAB_VERSION" ]]; then
    _log "RUCIO_JUPYTERLAB_VERSION is not set. Please set it to the desired version."
    exit 1
fi

# Check if the Rucio JupyterLab version is available
if [[ ! -d "/cvmfs/sw.escape.eu/rucio-jupyterlab/${RUCIO_JUPYTERLAB_VERSION}" ]]; then
    _log "Rucio JupyterLab version ${RUCIO_JUPYTERLAB_VERSION} is not available."
    exit 1
fi

# Set up the environment for Rucio JupyterLab
_log "Setting up Rucio JupyterLab environment for version ${RUCIO_JUPYTERLAB_VERSION}..."

ESCAPE_CVMFS_PATH="/cvmfs/sw.escape.eu"
RUCIO_CVMFS_PATH="${ESCAPE_CVMFS_PATH}/rucio-jupyterlab/${RUCIO_JUPYTERLAB_VERSION}"

export RUCIO_HOME="${RUCIO_CVMFS_PATH}"
export USER_PATH="${RUCIO_CVMFS_PATH}/bin"
export PATH="${USER_PATH}:${PATH}"
export USER_PYTHONPATH="${RUCIO_CVMFS_PATH}/lib/python3.11/site-packages"
export PYTHONPATH="${USER_PYTHONPATH}:${PYTHONPATH}"
export RUCIO_CA_CERT="${ESCAPE_CVMFS_PATH}/etc/ssl/certs/rucio_ca.pem"
export RUCIO_PYTHONBIN=python

_log "Rucio JupyterLab environment set up successfully."


#!/bin/bash

# Author: Danilo Piparo, Enric Tejedor, Pedro Maximino, Diogo Castro 2023
# Copyright CERN
# The environment for Spark is configured here. It allows CERN users to
# connect to spark clusters and use their computational resources
# through SWAN.

_log "$PYTHONPATH"
_log "Enabling Rucio JupyterLab extension"
_log "/cvmfs/sw.escape.eu/rucio-jupyterlab/1.3.1/bin/jupyter serverextension enable --py rucio_jupyterlab --sys-prefix"
/cvmfs/sw.escape.eu/rucio-jupyterlab/1.3.1/bin/jupyter serverextension enable --py rucio_jupyterlab --sys-prefix 2>&1 | while IFS= read -r line; do
    _log "$line"
done
_log "============================================================"
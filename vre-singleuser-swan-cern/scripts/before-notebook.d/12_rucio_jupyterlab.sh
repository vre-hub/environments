#!/bin/bash
set -e 
python /srv/singleuser/configure_rucio_jupyterlab.py
exec "$@"
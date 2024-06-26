#!/bin/bash
set -e 
python /srv/singleuser/configure_rucio.py
exec "$@"
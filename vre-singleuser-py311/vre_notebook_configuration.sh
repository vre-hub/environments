#!/bin/bash
set -e
python /usr/local/bin/vre_notebook_configuration.py
exec "$@"
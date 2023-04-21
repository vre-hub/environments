#!/bin/bash
set -e
python /opt/setup/configure.py
exec "$@"

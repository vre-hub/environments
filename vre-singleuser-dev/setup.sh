#!/bin/bash
set -e
python /opt/setup-rucio-jupyterlab/configure.py
echo -e "c.ServerApp.max_body_size = 2000000000" >> /etc/jupyter/jupyter_server_config.py
exec "$@"
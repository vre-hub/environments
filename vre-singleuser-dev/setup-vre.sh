#!/bin/bash
set -e
python /usr/local/bin/configure-vre.py
# echo -e "c.ServerApp.max_body_size = 2100100100" >> /etc/jupyter/jupyter_server_config.py
# echo -e "c.ServerApp.max_buffer_size = 2100100100" >> /etc/jupyter/jupyter_server_config.py
exec "$@"
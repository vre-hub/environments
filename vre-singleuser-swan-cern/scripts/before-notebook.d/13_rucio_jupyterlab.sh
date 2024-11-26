#!/bin/bash
set -e 
mkdir -p $HOME/.jupyter/
# If file exists, erase it and create an empty one
config_file="$HOME/.jupyter/jupyter_server_config.json"
if [ -f "$config_file"] ; then rm -f $config_file ; fi
sleep 1
touch "$config_file"
python /srv/singleuser/configure_rucio_jupyterlab.py
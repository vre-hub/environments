#!/bin/bash
set -e 
mkdir -p $HOME/.jupyter/
# If file exists, erase it and create an empty one
config_file="$HOME/.jupyter/jupyter_server_config.json"
if [ -f "$file"] ; then rm -f $file ; fi
touch ${file}
python /srv/singleuser/configure_rucio_jupyterlab.py
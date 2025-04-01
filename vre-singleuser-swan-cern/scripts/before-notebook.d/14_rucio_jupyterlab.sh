#!/bin/bash
set -e 
echo "Whoami: "
whoami
echo "id USER:"
id $USER
echo "pwd: "
echo $PWD
python /srv/singleuser/configure_rucio_jupyterlab.py
#run_as_user python /srv/singleuser/configure_rucio_jupyterlab.py
#sudo -u $NB_USER python /srv/singleuser/configure_rucio_jupyterlab.py
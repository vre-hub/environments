#!/bin/bash
set -e 
echo "Whoami: "
whoami
echo "id USER:"
id $USER
echo "pwd: "
echo $PWD
run_as_user python /srv/singleuser/configure_rucio_jupyterlab.py
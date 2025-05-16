#!/bin/bash

# Author: Danilo Piparo, Enric Tejedor, Pedro Maximino, Diogo Castro 2023
# Copyright CERN
# Here the software environment for notebooks and terminals is configured, 
# using the LCG release as basis and (possibly) a user environment script.

_log () {
    if [[ "$*" == "ERROR:"* ]] || [[ "$*" == "WARNING:"* ]] || [[ "${JUPYTER_DOCKER_STACKS_QUIET}" == "" ]]; then
        echo "$@"
    fi
}

START_TIME_SETUP_SWAN_HOME=$( date +%s.%N )
SETUP_SWAN_HOME_TIME_SEC=$(echo $(date +%s.%N --date="$START_TIME_SETUP_SWAN_HOME seconds ago") | bc)
_log "user: $USER, host: ${SERVER_HOSTNAME%%.*}, metric: configure_user_env_swan_home.duration_sec, value: $SETUP_SWAN_HOME_TIME_SEC"

# Persist enabled notebook nbextensions
SWAN_PROJECTS=$HOME/SWAN_projects
NBCONFIG=$JPY_DIR/nbconfig
mkdir -p $NBCONFIG
LOCAL_NB_NBEXTENSIONS=$SWAN_PROJECTS/.notebook_nbextensions
if [ ! -f $LOCAL_NB_NBEXTENSIONS ]; then 
  echo "{
    \"load_extensions\": {
    }
  }" > $LOCAL_NB_NBEXTENSIONS
fi
rm -f $NBCONFIG/notebook.json
ln -s $LOCAL_NB_NBEXTENSIONS $NBCONFIG/notebook.json

START_TIME_SETUP_LCG=$( date +%s.%N )
export JUPYTER_DATA_DIR=$LCG_VIEW/share/jupyter 

# Setup LCG
source $LCG_VIEW/setup.sh

SETUP_LCG_TIME_SEC=$(echo $(date +%s.%N --date="$START_TIME_SETUP_LCG seconds ago") | bc)
_log "user: $USER, host: ${SERVER_HOSTNAME%%.*}, metric: configure_user_env_cvmfs.${ROOT_LCG_VIEW_NAME:-none}.duration_sec, value: $SETUP_LCG_TIME_SEC"

# Prepend SWAN extensions path to PYTHONPATH to expose them
# to the notebook processes
export PYTHONPATH=$SWAN_LIB_DIR/extensions/:$PYTHONPATH

# Append to PYTHONPATH a directory where to install libraries
# to be exposed to the user environment (notebooks, terminals)
export PYTHONPATH=$PYTHONPATH:$SWAN_LIB_DIR/nb_term_lib/

# Prepend the user site packages directory to PYTHONPATH, if they request it.
# This allows to use Python packages installed on CERNBox
if [ "$SWAN_USE_LOCAL_PACKAGES" == "true" ]; then
  USER_SITE=$(python -m site --user-site)
  export PYTHONPATH=$USER_SITE:$PYTHONPATH
fi

# Run user startup script
TMP_SCRIPT=`mktemp`
if [[ ! -n $USER_ENV_SCRIPT ]];
then
  _log "User did not set a script";
elif [[ $USER_ENV_SCRIPT && -f `eval echo $USER_ENV_SCRIPT` ]];
then
  START_TIME_SETUP_SCRIPT=$( date +%s.%N )

  _log "Found user script: $USER_ENV_SCRIPT"
  TMP_SCRIPT=`mktemp`
  cat `eval echo $USER_ENV_SCRIPT` > $TMP_SCRIPT
  source $TMP_SCRIPT

  SETUP_SCRIPT_TIME_SEC=$(echo $(date +%s.%N --date="$START_TIME_SETUP_SCRIPT seconds ago") | bc)
  _log "user: $USER, host: ${SERVER_HOSTNAME%%.*}, metric: configure_user_env_script.duration_sec, value: $SETUP_SCRIPT_TIME_SEC"
else
 _log "Cannot find user script: $USER_ENV_SCRIPT";
 exit 127
fi

# In k8s, $KRB5CCNAME_NB_TERM points to the location of the EOS kerberos ticket that notebook and terminal
# processes use. The Jupyter server uses the same ticket stored in another location ($KRB5CCNAME). With the
# code below, we force that $KRB5CCNAME becomes $KRB5CCNAME_NB_TERM only for notebook and terminal processes.
# This duality exists to prevent the user from overwriting the EOS kerberos ticket that the Jupyter server
# uses, e.g. by doing `kinit` from a notebook or a terminal.
# In puppet, $KRB5CCNAME_NB_TERM does not exist. Thus we give it a value and make $KRB5CCNAME point to that
# value.
# Both in k8s and puppet, renewals of the EOS kerberos tickets are automatically done to prevent expiration,
# both for the Jupyter server and the notebooks and terminals. However, if the user runs an explicit kinit
# and generates new kerberos credentials for notebooks and terminals, they are responsible for renewing those
# credentials from that point on.
if [[ -z $KRB5CCNAME_NB_TERM ]]
then
  KRB5CCNAME_NB_TERM="/tmp/krb5cc_${USER_ID}_${RANDOM}"
fi
export KRB5CCNAME=$KRB5CCNAME_NB_TERM

# As the LCG setup might set PYTHONHOME, run python with -I (Isolated Mode) to prevent
# the lookup for modules in a Python 3 path and user site
python -I /srv/singleuser/configure_kernels_and_terminal.py

# Remove our extra paths (where we install our extensions) in the kernel (via SwanKernelEnv kernel extension), 
# leaving the user env cleaned. It should be the last one called to allow the kernel to load our extensions correctly.
export KERNEL_PROFILEPATH=$PROFILEPATH/ipython_kernel_config.py
echo "c.InteractiveShellApp.extensions.append('swankernelenv')" >>  $KERNEL_PROFILEPATH

#!/bin/bash

# Author: Danilo Piparo, Enric Tejedor, Pedro Maximino, Diogo Castro 2023
# Copyright CERN
# Here the environment for the notebook server is prepared. Many of the commands are 
# launched as regular user as it's this entity which is able to access 
# eos and not the super user.

# Set environment for the Jupyter process
LOCAL_HOME=/home/$NB_USER
export IPYTHONDIR=$LOCAL_HOME/.ipython
export JPY_DIR=$LOCAL_HOME/.jupyter

# The Jupyter environment variables below are set to point to the local user
# home (/home/$USER), instead of the EOS path
export JUPYTER_CONFIG_DIR=$JPY_DIR
export JUPYTER_PATH=$LOCAL_HOME/.local/share/jupyter
export JUPYTER_RUNTIME_DIR=$JUPYTER_PATH/runtime
export JUPYTER_DATA_DIR=$JUPYTER_PATH

# Set npm cache on the local user home, instead of the EOS path
export NPM_CONFIG_CACHE=$LOCAL_HOME/.npm

# Set jupyterlab config directory
export JUPYTERLAB_SETTINGS_DIR=$HOME/.local/lab/user-settings/

# Set other environment variables
export KERNEL_DIR=$JUPYTER_PATH/kernels
export SWAN_ENV_FILE=$LOCAL_HOME/.bash_profile
export PROFILEPATH=$IPYTHONDIR/profile_default

# Create missing directories
mkdir -p $IPYTHONDIR $PROFILEPATH

# Create a gitignore file for ignoring all .sys. files and set it as global
# This will hide the checkpoint files created by EOS.
GLOBAL_GITIGNORE="$LOCAL_HOME/.gitignore_global"
echo ".sys.*" > "$GLOBAL_GITIGNORE"
run_as_user git config --global core.excludesfile "$GLOBAL_GITIGNORE"

# Make the user the owner of the local home and subdirectories
chown -R $NB_USER:$NB_GID $LOCAL_HOME

if [ "$SOFTWARE_SOURCE" == "lcg" ]; then

  # Setup the LCG View on CVMFS
  _log "Setting up environment from CVMFS"
  export LCG_VIEW=$ROOT_LCG_VIEW_PATH/$ROOT_LCG_VIEW_NAME/$ROOT_LCG_VIEW_PLATFORM

  # Configure nb and lab extensions from the LCG release
  ln -s $LCG_VIEW/share/jupyter/nbextensions $JUPYTER_PATH
  ln -s $LCG_VIEW/share/jupyter/labextensions $JUPYTER_PATH

  # Create directory for nb configuration
  NBCONFIG=/etc/jupyter/nbconfig/notebook.d
  mkdir -p $NBCONFIG

  # Enable jupyter-matplotlib extension for classic UI
  jq -n --argjson jupyter-matplotlib/extension true \
        '{load_extensions: $ARGS.named}' > $NBCONFIG/jupyter-matplotlib.json

  # Enable widgets extension for classic UI
  jq -n --argjson jupyter-js-widgets/extension true \
        '{load_extensions: $ARGS.named}' > $NBCONFIG/widgetsnbextension.json

  # Configure kernels and terminal
  # The environment of the kernels and the terminal will combine the view and the user script (if any)
  _log "Configuring kernels and terminal"

  # ROOT
  ROOT_KERNEL_PATH=$LCG_VIEW/etc/notebook/kernels/root
  if [ -d $ROOT_KERNEL_PATH ];
  then
    cp -rL $ROOT_KERNEL_PATH $KERNEL_DIR
  fi

  # R
  R_KERNEL_PATH=$LCG_VIEW/share/jupyter/kernels/ir
  if [ -d $R_KERNEL_PATH ];
  then
    cp -rL $R_KERNEL_PATH $KERNEL_DIR
    sed -i "s/IRkernel::main()/options(bitmapType='cairo');IRkernel::main()/g" $KERNEL_DIR/ir/kernel.json # Force cairo for graphics
  fi

  # Octave
  OCTAVE_KERNEL_PATH=$LCG_VIEW/share/jupyter/kernels/octave
  if [[ -d $OCTAVE_KERNEL_PATH ]];
  then
    cp -rL $OCTAVE_KERNEL_PATH $KERNEL_DIR
    export OCTAVE_KERNEL_JSON=$KERNEL_DIR/octave/kernel.json
  fi

  # Julia
  JULIA_KERNEL_PATH=$LCG_VIEW/share/jupyter/kernels/julia-*
  if [ -d $JULIA_KERNEL_PATH ];
  then
    cp -rL $JULIA_KERNEL_PATH $KERNEL_DIR
  fi

  # Make the user the owner of kernel files
  chown -R $NB_USER:$NB_GID $KERNEL_DIR

  _log "Running user configuration script for user $NB_USER."

  set +e
  run_as_user bash /srv/singleuser/scripts/userconfig.sh

  # Since the jupyter server is started with --preserve-env (in start.sh)
  # other variables exported from this point on are also visible in the
  # notebook/terminal environment unless overwritten by what appears in
  # the kernel.json or .bash_profile.

  USERCONFIG_EXIT=$?

  if [ $USERCONFIG_EXIT -ne 0 ]
  then
    _log "Error configuring user environment. Exit code: $USERCONFIG_EXIT"
    exit $USERCONFIG_EXIT  
  fi
  set -e

  START_TIME_CONFIGURE_KERNEL_ENV=$( date +%s.%N )

  # If there, source users' .bashrc after the SWAN environment
  BASHRC_LOCATION=$HOME/.bashrc
  printf "if [[ -f $BASHRC_LOCATION ]];
  then
    source $BASHRC_LOCATION
  fi\n" >> $SWAN_ENV_FILE

  if [ $? -ne 0 ]
  then
    _log "Error setting the environment for kernels"
    exit 1
  else
    CONFIGURE_KERNEL_ENV_TIME_SEC=$(echo $(date +%s.%N --date="$START_TIME_CONFIGURE_KERNEL_ENV seconds ago") | bc)
    _log "user: $NB_USER, host: ${SERVER_HOSTNAME%%.*}, metric: configure_kernel_env.${ROOT_LCG_VIEW_NAME:-none}.${SPARK_CLUSTER_NAME:-none}.duration_sec, value: $CONFIGURE_KERNEL_ENV_TIME_SEC"
  fi

  _log "Finished setting up CVMFS and user environment"
else
  export KRB5CCNAME=$KRB5CCNAME_NB_TERM
fi

# Set the terminal environment
#in jupyter 6.0.0 login shell (jupyter/notebook#4112) is set by default and /etc/profile.d is respected
echo "source $LOCAL_HOME/.bash_profile" > /etc/profile.d/swan.sh
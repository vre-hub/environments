#!/bin/bash

# Author: Giovanni Guerrieri, Enrique Garcia Garcia (2025)
# Copyright CERN
# This script configures the environment for the usage 
# of the Rucio JupyterLab extension.

if [[ "$SWAN_USE_RUCIO" = "true" ]]
then
    # Check if the RUCIO_JUPYTERLAB_VERSION environment variable is set.
    if [[ -z "$RUCIO_JUPYTERLAB_VERSION" ]]; then
        _log "RUCIO_JUPYTERLAB_VERSION is not set. Please set it to the desired version."
        exit 1
    fi

    # Verify if the specified Rucio JupyterLab version exists in the CVMFS directory.
    if [[ ! -d "/cvmfs/sw.escape.eu/rucio-jupyterlab/${RUCIO_JUPYTERLAB_VERSION}" ]]; then
        _log "Rucio JupyterLab version ${RUCIO_JUPYTERLAB_VERSION} is not available."
        exit 1
    fi

    _log "Setting up Rucio JupyterLab environment for version ${RUCIO_JUPYTERLAB_VERSION}..."

    # Define the base path for the ESCAPE CVMFS repository.
    ESCAPE_CVMFS_PATH="/cvmfs/sw.escape.eu"

    # Define the path to the specific Rucio JupyterLab version within the CVMFS repository.
    RUCIO_CVMFS_PATH="${ESCAPE_CVMFS_PATH}/rucio-jupyterlab/${RUCIO_JUPYTERLAB_VERSION}"

    # Set the RUCIO_HOME environment variable to point to the Rucio JupyterLab installation directory.
    export RUCIO_HOME="${RUCIO_CVMFS_PATH}"

    # Symlink all the Rucio binaries to the SWAN nb_term_bin directory.
    ln -s ${RUCIO_CVMFS_PATH}/bin/* $SWAN_BIN_DIR/nb_term_bin
    export PATH="${RUCIO_CVMFS_PATH}/bin:${PATH}"

    # Pick up the jupyter server side python version from /opt/conda/bin/jupyter
    # Only the major.minor version is needed to select the correct site-packages path
    SERVER_PYTHON_VERSION=$(/opt/conda/bin/python -c "import sys; print('.'.join(map(str, sys.version_info[:2])))")
    echo "Using server python version: $SERVER_PYTHON_VERSION"
    ls -l ${RUCIO_CVMFS_PATH}/lib/python${SERVER_PYTHON_VERSION}/

    # Select the correct python version subdirectory, regardless of the patch version
    ln -s ${RUCIO_CVMFS_PATH}/lib/python${SERVER_PYTHON_VERSION}/site-packages/* $SWAN_LIB_DIR/nb_term_lib

    # Add the Rucio JupyterLab Python packages directory to the PYTHONPATH environment variable.
    # export USER_PYTHONPATH="${RUCIO_CVMFS_PATH}/lib/python${SERVER_PYTHON_VERSION}/site-packages"
    export PYTHONPATH="${RUCIO_CVMFS_PATH}/lib/python${SERVER_PYTHON_VERSION}/site-packages:${PYTHONPATH}"

    # Set the path to the Rucio CA certificate used for secure communication.
    export RUCIO_CA_CERT="${ESCAPE_CVMFS_PATH}/etc/ssl/certs/rucio_ca.pem"

    # Define the Python binary to be used by Rucio JupyterLab.
    export RUCIO_PYTHONBIN=python

    _log "Rucio JupyterLab environment set up successfully."

    _log "Setting up iPython kernel for Rucio JupyterLab..."

    # Create the default iPython profile directory for the Jupyter Notebook user.
    mkdir -p /home/${NB_USER}/.ipython/profile_default
    _log "Created directory /home/${NB_USER}/.ipython/profile_default"

    # Configure the iPython kernel to load the Rucio JupyterLab extension.
    IPYTHON_KERNEL_CONFIG=$IPYTHONDIR/profile_default/ipython_kernel_config.py
    echo -e "c.InteractiveShellApp.extensions.append('rucio_jupyterlab.kernels.ipython')\n$( [ -f ${IPYTHON_KERNEL_CONFIG} ] && cat ${IPYTHON_KERNEL_CONFIG})" > ${IPYTHON_KERNEL_CONFIG}

    _log "iPython kernel for Rucio JupyterLab set up successfully."

    _log "Writing the extension configuration file..."

    # Add the Rucio JupyterLab server configuration to the Jupyter server configuration file.
    # The Rusio specific file is provided by CVMFS, and the original is copied from the Dockerfile.
    cat "${ESCAPE_CVMFS_PATH}/etc/jupyter/jupyter_server_config.py" >> /home/${NB_USER}/.jupyter/jupyter_server_config.py

    _log "Extension configuration file written successfully."
    _log "Rucio JupyterLab setup completed."
else
    _log "Skipping Rucio JupyterLab configuration as it's not enabled.";
fi

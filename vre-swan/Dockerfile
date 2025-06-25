# Author: Danilo Piparo, Enric Tejedor, Pedro Maximino, Diogo Castro 2023
# Copyright CERN
# This installs the SWAN packages to enable 
# using Jupyter with EOS and CVMFS

ARG VERSION_PARENT=v0.0.5

FROM gitlab-registry.cern.ch/swan/docker-images/jupyter/base:${VERSION_PARENT}

LABEL maintainer="swan-admins@cern.ch"

ARG NB_USER="jovyan"
ARG NB_UID="1000"
ARG BUILD_TAG=daily
ENV VERSION_DOCKER_IMAGE=$BUILD_TAG

RUN echo "Building swan image with tag ${VERSION_DOCKER_IMAGE} from parent tag ${VERSION_PARENT}."

# Directory to expose SWAN extensions and libraries
ENV SWAN_LIB_DIR=/usr/local/lib/swan

# Switch to superuser to install packages
USER root

# Install required dnf packages
RUN dnf install -y \
    # Required by before-notebook scripts
    bc \
    # Required for key4hep
    environment-modules \
    # The R configuration of the LCG release requires
    # the en_US.UTF-8 encoding
    glibc-langpack-en \
    # General utilities
    file \
    git \
    htop \
    nano \
    patch \
    unzip \
    which \
    # Texlive and fontconfig packages are used to convert 
    # notebooks into different formats
    texlive \
    # Texlive packages necessary to convert notebooks
    # into different formats that are not installed
    # automatically as dependencies of texlive
    texlive-adjustbox \
    texlive-tcolorbox \
    texlive-titling \
    texlive-type1cm \
    texlive-upquote \
    texlive-ulem \
    # Added to allow tex outputs to be converted to png
    texlive-dvipng \
    fontconfig && \
    # Clear the dnf cache as we no longer need to install packages
    dnf clean all && \
    rm -rf /var/cache/dnf

# Install HEP_OSlibs
# This installs system packages for LCGs to work
RUN dnf --repofrompath=wlcg,'https://linuxsoft.cern.ch/wlcg/el9/$basearch/' install -y --nogpgcheck wlcg-repo
RUN dnf -y install HEP_OSlibs-9.2.3-1.el9

# Switch back to jovyan to avoid accidental container runs as root
USER ${NB_UID}

# Pip is used to install this package because conda forge
# does not contain the latest version (v0.6.3)
RUN pip install --no-deps --no-cache-dir \
    jupyter_nbextensions_configurator==0.6.3

# Install python pip packages
RUN mamba install --yes \
    'voila==0.5.5' \
    'ipyparallel==8.6.1' \
    'jupyter-server-proxy==4.1.0' \
    'jupyter-resource-usage==1.1.0' \
    'jupyterlab-git==0.51.1' \
    # Extensions required by jupyter server
    'webio-jupyter-extension==0.1.0'

# Install all of our extensions
# Ignore (almost all) dependencies because they have already been installed or come from CVMFS
RUN pip install --no-deps --no-cache-dir \
    swancontents==2.1.14 \
    swanhelp==3.0.3 \
    swankernelenv==1.0.0 \
    swanoauthrenew==1.0.2  \
    swanshare==2.0.3 \
    swancustomenvironments==0.0.28

RUN pip install \ 
    # Required dependency for swanoauthrenew
    PyJWT

# Add Python 3 kernel configuration
RUN mkdir -p /home/${NB_USER}/.local/share/jupyter/kernels/python3
ADD config/kernel.json  /home/${NB_USER}/.local/share/jupyter/kernels/python3/kernel.json
RUN cp /opt/conda/share/jupyter/kernels/python3/logo* /home/${NB_USER}/.local/share/jupyter/kernels/python3/

# Python configuration
# Add jupyter notebook configuration
ADD python/jupyter_server_config.py /home/${NB_USER}/.jupyter/jupyter_server_config.py

USER root

# Create directories where we will store:
# - SWAN extensions and their dependencies (this path gets removed from
# notebooks by swankernelenv)
# - Libraries to be exposed to notebooks and terminals and their
# dependencies
RUN mkdir -p $SWAN_LIB_DIR/extensions && \
    mkdir -p $SWAN_LIB_DIR/nb_term_lib && \
    fix-permissions $SWAN_LIB_DIR && \
    chown ${NB_USER}:${NB_GID} $SWAN_LIB_DIR/nb_term_lib

# Expose swankernelenv to the user environment in notebooks.
# swankernelenv removes the $SWAN_LIB_DIR/extensions directory from the PYTHONPATH
# when the notebook starts. Check EOF of userconfig.sh
RUN ln -s $(pip show swankernelenv | grep 'Location:' | awk '{print $2}')/swankernelenv $SWAN_LIB_DIR/extensions/

# Expose ipykernel and some of its dependencies to the user environment in
# notebooks, to enforce an ipykernel version that comes from the image,
# instead of from the LCG release. This ensures we run the Python kernels
# with the same package versions as the Jupyter server.
RUN ln -s $(pip show ipykernel | grep -oP 'Location: \K.*')/ipykernel ${SWAN_LIB_DIR}/extensions/
RUN ln -s $(pip show jupyter_core | grep -oP 'Location: \K.*')/jupyter_core ${SWAN_LIB_DIR}/extensions/
RUN ln -s $(pip show comm | grep -oP 'Location: \K.*')/comm ${SWAN_LIB_DIR}/extensions/
RUN ln -s $(pip show debugpy | grep -oP 'Location: \K.*')/debugpy ${SWAN_LIB_DIR}/extensions/

# Enable extensions for classic UI
RUN jupyter nbclassic-extension install --py --system swanhelp && \
    jupyter nbclassic-extension enable --py --system swanhelp
RUN jupyter nbclassic-extension install --py --system swanshare && \
    jupyter nbclassic-extension enable --py --system swanshare
RUN jupyter nbclassic-extension install --py --system jupyter_nbextensions_configurator && \
    jupyter nbclassic-extension enable --py --system jupyter_nbextensions_configurator

# User session configuration scripts
# Add scripts
COPY scripts/before-notebook.d/* /usr/local/bin/before-notebook.d/

# Grant scripts execution permissions
RUN chmod +x /usr/local/bin/before-notebook.d/*

# Add python scripts
ADD python/configure_kernels_and_terminal.py /srv/singleuser/configure_kernels_and_terminal.py

# Add scripts that are not executed automatically but are
# instead called by our scripts internally
RUN mkdir /srv/singleuser/scripts
COPY scripts/others/* /srv/singleuser/scripts

# TEMPORARY: apply a patch to the jupyter server proxy handlers,
# while we wait for the release of a new version with it
ADD patches/jupyter_server_proxy.diff /tmp/jupyter_server_proxy.diff
RUN patch $(pip show jupyter-server-proxy | grep -oP 'Location: \K.*')/jupyter_server_proxy/handlers.py /tmp/jupyter_server_proxy.diff && \
    rm -f /tmp/jupyter_server_proxy.diff

# Switch back to jovyan to avoid accidental container runs as root
USER ${NB_UID}
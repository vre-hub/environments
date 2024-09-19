# Image fully derived from 
# https://github.com/jupyter/docker-stacks/tree/9e230b3b7d2418bd79c94d03bf5f45d2a601865f/images/minimal-notebook
# but with different base layer

FROM ghcr.io/vre-hub/itwinai-base-notebook:0.2.2-torch2.1-py3.10 

LABEL org.opencontainers.image.source=https://github.com/vre-hub/environments/
LABEL org.opencontainers.image.description="Base itwinai image (torch2.1) and Jupyter Minimal Notebook layer (python 3.10)"
LABEL org.opencontainers.image.licenses=MIT
LABEL maintainer="Enrique Garcia & Matteo Bunino - CERN"

# Fix: https://github.com/hadolint/hadolint/wiki/DL4006
# Fix: https://github.com/koalaman/shellcheck/wiki/SC3014
SHELL ["/bin/bash", "-o", "pipefail", "-c"]

USER root

# Install all OS dependencies for a fully functional Server
RUN apt-get update --yes && \
    apt-get install --yes --no-install-recommends \
    # Common useful utilities
    curl \
    git \
    nano-tiny \
    tzdata \
    unzip \
    vim-tiny \
    # git-over-ssh
    openssh-client \
    # `less` is needed to run help in R
    # see: https://github.com/jupyter/docker-stacks/issues/1588
    less \
    # `nbconvert` dependencies
    # https://nbconvert.readthedocs.io/en/latest/install.html#installing-tex
    texlive-xetex \
    texlive-fonts-recommended \
    texlive-plain-generic \
    # Enable clipboard on Linux host systems
    xclip && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Create alternative for nano -> nano-tiny
RUN update-alternatives --install /usr/bin/nano nano /bin/nano-tiny 10

# Switch back to jovyan to avoid accidental container runs as root
USER ${NB_UID}

# Add an R mimetype option to specify how the plot returns from R to the browser
COPY --chown=${NB_UID}:${NB_GID} Rprofile.site /opt/conda/lib/R/etc/

# Add setup scripts that may be used by downstream images or inherited images
COPY setup-scripts/ /opt/setup-scripts/

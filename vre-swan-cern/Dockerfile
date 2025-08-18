#ARG VERSION_PARENT=v0.0.32
#FROM gitlab-registry.cern.ch/swan/docker-images/jupyter/swan:${VERSION_PARENT}
# Same image as swan-cern/v0.0.48 - VRE-ied

ARG VERSION_PARENT=sha-a09e0ad
FROM ghcr.io/vre-hub/vre-swan:${VERSION_PARENT}

LABEL maintainer="swan-admins@cern.ch"
ARG NB_UID="1000"
ARG BUILD_TAG=daily
ENV VERSION_DOCKER_IMAGE=$BUILD_TAG

RUN echo "Building swan-cern image with tag ${VERSION_DOCKER_IMAGE} from parent tag ${VERSION_PARENT}."

# User session configuration scripts
# Add scripts to be run before the jupyter server starts
COPY scripts/before-notebook.d/* /usr/local/bin/before-notebook.d/

# dask-labextension needs to be installed first so its lab extension
# gets disabled automatically when installing swandask
RUN pip install --no-deps --no-cache-dir dask-labextension==7.0.0

# Install all of our extensions required to access Spark, HDFS and Dask.
# Ignore dependencies because they have already been installed or come from CVMFS
RUN pip install --no-deps --no-cache-dir \
    sparkconnector==3.0.9 \
    sparkmonitor==3.1.0 \
    swanportallocator==2.0.0 \
    swandask==0.0.5

# CERN-VRE
RUN pip install --no-deps --no-cache-dir rucio-jupyterlab==1.3.1 

# Install swandaskcluster in the lib directory that is exposed to notebooks and
# terminals, which need it to do automatic TLS configuration for Dask clients
RUN pip install --no-deps --no-cache-dir --target ${SWAN_LIB_DIR}/nb_term_lib \
    swandaskcluster==3.1.0

# Add helper scripts
COPY scripts/others/* /srv/singleuser/

# Add dask configuration file
# Dask config: lab extension must use SwanHTCondorCluster
ADD config/dask-labextension.yaml /etc/dask/labextension.yaml

USER root

# Install Spark extensions for classic UI
RUN jupyter nbclassic-extension install --py --system sparkconnector && \
    jupyter nbclassic-extension install --py --system sparkmonitor

# HTCondor requirements
RUN dnf install -y \
    # required by condor_submit
    perl-Archive-Tar \
    perl-Authen-Krb5 \
    perl-Sys-Hostname \
    perl-Sys-Syslog && \
    dnf clean all && \
    rm -rf /var/cache/dnf
# Required for kerberos authentication to work
ADD config/krb5.conf.no_rdns /etc/krb5.conf.no_rdns

# Import dependency of swandaskcluster, which is required by Dask clients
# created from a notebook/terminal to create a Security object
RUN ln -s $(pip show swanportallocator | grep -oP 'Location: \K.*')/swanportallocator ${SWAN_LIB_DIR}/nb_term_lib

# Create symlinks for the remaining swan extensions, because
# they need to be accessible in the user environment
RUN ln -s $(pip show sparkconnector | grep -oP 'Location: \K.*')/sparkconnector ${SWAN_LIB_DIR}/extensions/ && \
    ln -s $(pip show sparkmonitor | grep -oP 'Location: \K.*')/sparkmonitor ${SWAN_LIB_DIR}/extensions/ && \
    ln -s $(pip show swandask | grep -oP 'Location: \K.*')/swandask ${SWAN_LIB_DIR}/extensions/ && \
    ln -s $(pip show dask-labextension | grep -oP 'Location: \K.*')/dask_labextension ${SWAN_LIB_DIR}/extensions/ && \
    # dependency of dask-labextension
    ln -s $(pip show jupyter-server-proxy | grep -oP 'Location: \K.*')/jupyter_server_proxy ${SWAN_LIB_DIR}/extensions/ && \
    # dependency of jupyter-server-proxy
    ln -s $(pip show simpervisor | grep -oP 'Location: \K.*')/simpervisor ${SWAN_LIB_DIR}/extensions/

# CERN-VRE
# The fact that the rucio_jupyterlab does not correspond with rucio-jupyterlab is how the package was dev
RUN ln -s $(pip show rucio-jupyterlab | grep -oP 'Location: \K.*')/rucio_jupyterlab ${SWAN_LIB_DIR}/extensions/
# RUN jupyter serverextension enable --py rucio_jupyterlab --sys-prefix

# Grant scripts execution permissions
RUN chmod +x /usr/local/bin/before-notebook.d/*

# Switch back to jovyan to avoid accidental container runs as root
USER ${NB_UID}

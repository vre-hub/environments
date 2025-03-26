ARG VERSION_PARENT=v0.0.34

FROM gitlab-registry.cern.ch/swan/docker-images/jupyter/swan-cern:${VERSION_PARENT}
LABEL author="E. Garcia - 2024"
LABEL maintainer="VRE Team @ CERN 23/24 - E. Garcia, G. Guerrieri. escape-cern@cern.ch"

USER root 

RUN curl -Lo /etc/yum.repos.d/lcg-trustanchors.repo https://lcg-ca.web.cern.ch/distribution/current/repo-files/lcg-trustanchors.repo \
    && dnf update -y \
    && dnf install -y epel-release gfal2* ca-policy-lcg\
    && dnf clean all \
    && rm -rf /var/cache/dnf

USER ${NB_UID}

# RUN python -m pip install rucio-clients
# RUN python -m pip install --upgrade typing_extensions

RUN python -m pip install rucio-jupyterlab==1.2.0 \
    && jupyter serverextension enable --py rucio_jupyterlab --sys-prefix 

RUN python -m pip install rucio-clients==34.6.0

# Add pre-hooks to be run before the jupyter server starts
COPY scripts/before-notebook.d/* /usr/local/bin/before-notebook.d/
COPY scripts/others/* /srv/singleuser

USER root

RUN mkdir -p /opt/rucio/etc \
    && touch /opt/rucio/etc/rucio.cfg \
    && fix-permissions /opt/rucio/etc/rucio.cfg \
    && chown -R ${NB_UID}:${NB_GID} /opt/rucio/etc     

# # Grant script execution permissions
# RUN chmod +x /usr/local/bin/before-notebook.d/*
# RUN fix-permissions /srv/singleuser/configure_rucio_jupyterlab.py \
#     && chown -R ${NB_UID} /srv/singleuser/configure_rucio_jupyterlab.py \
#     && chmod +x /srv/singleuser/configure_rucio_jupyterlab.py

# This should not be used as we are gonna be writing on $JUPYTER_CONFIG_DIR = '/home/$USER/.jupyter'
# RUN mkdir -p $HOME/.jupyter \
#     && fix-permissions $HOME/.jupyter \
#     && chown -R ${NB_UID} $HOME/.jupyter

RUN mkdir /certs \
    && touch /certs/rucio_ca.pem \
    && curl -fsSL 'https://cafiles.cern.ch/cafiles/certificates/CERN%20Root%20Certification%20Authority%202.crt' | openssl x509 -inform DER -out /tmp/cernrootca2.crt \
    && curl -fsSL 'https://cafiles.cern.ch/cafiles/certificates/CERN%20Grid%20Certification%20Authority(1).crt' -o /tmp/cerngridca.crt \
    && curl -fsSL 'https://cafiles.cern.ch/cafiles/certificates/CERN%20Certification%20Authority.crt' -o /tmp/cernca.crt \
    && cat /tmp/cernrootca2.crt >> /certs/rucio_ca.pem \
    && cat /tmp/cerngridca.crt >> /certs/rucio_ca.pem \
    && cat /tmp/cernca.crt >> /certs/rucio_ca.pem \
    && rm /tmp/*.crt \
    && update-ca-trust

USER ${NB_UID}
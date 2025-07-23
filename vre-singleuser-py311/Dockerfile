FROM quay.io/jupyter/scipy-notebook:python-3.12.11
LABEL author="Image based on the work by Muhammad Aditya Hilmy - ESCAPE WP2 2020"
LABEL maintainer="VRE Team @ CERN 23/24 - E. Garcia, G. Guerrieri"
LABEL org.opencontainers.image.source https://github.com/vre-hub/environments
ARG BUILD_DATE
LABEL org.label-schema.build-date=$BUILD_DATE

RUN python -m pip install --upgrade pip

USER $NB_UID

RUN conda install -y -n base mamba \
    && mamba install -y -c conda-forge python-gfal2 \
        nodejs \
        jupyterlab">4,<5" \
        notebook"<7" \
        jupyterhub \
        jsonschema \ 
        jupyterlab_server \
        jupyter_server \
        traitlets \
        nbformat \
        ipykernel \
        PyJWT \
        ipywidgets \
        rucio-clients==35.6.0 \
    && conda clean --all -f -y

#RUN python -m pip install rucio-clients==34.6.0

# Install jupyterlab extensions
# RUN python -m pip install rucio-jupyterlab==1.3.0 
# #    && jupyter server extension enable --py rucio_jupyterlab --sys-prefix 

# RUN python -m pip install swanoauthrenew==1.0.1 
# #    && jupyter server extension enable --py swanoauthrenew --sys-prefix 

# RUN python -m pip install reana-jupyterlab 
# #    && jupyter server extension enable --py reana_jupyterlab --sys-prefix

# RUN git clone https://github.com/vre-hub/zenodo-jupyterlab-extension.git \
#     && cd zenodo-jupyterlab-extension \
#     && python -m pip install . \
# #    && jupyter server extension enable --py zenodo_jupyterlab.server --sys-prefix \
#     && cd .. \
#     && rm -rf zenodo-jupyterlab-extension
    
# # Custom version of reana-client due to the jsonschema problem
# RUN python -m pip install git+https://github.com/mdonadoni/reana-client.git@vre-summer-24

USER root

RUN apt-get update && \
    apt-get install -y wget gnupg ca-certificates build-essential curl voms-clients-java software-properties-common && \
    rm -rf /var/lib/apt/lists/* && \
    apt-get clean && \
    rm /opt/conda/bin/voms-proxy-init && \
    ln -s /usr/bin/voms-proxy-init /opt/conda/bin/voms-proxy-init

# ESCAPE grid-security
# Docs: https://docs.egi.eu/providers/operations-manuals/howto01_using_igtf_ca_distribution/#using-the-distribution-on-a-debian-or-debian-derived-platform
# Not working
# RUN wget -q -O - https://dist.eugridpma.info/distribution/igtf/current/GPG-KEY-EUGridPMA-RPM-3 | apt-key add -

# RUN echo "deb [signed-by=/usr/share/keyrings/egi-igtf-archive-keyring.gpg] https://repository.egi.eu/sw/production/cas/1/current egi-igtf core" \
#     > /etc/apt/sources.list.d/egi-igtf.list

# RUN apt-get update && \
#     apt-get install -y ca-policy-egi-core && \
#     rm -rf /var/lib/apt/lists/*

# VOMS setup
# wget https://indigo-iam.github.io/escape-docs/voms-config/voms-escape.cloud.cnaf.infn.it.vomses -O /etc/vomses/voms-escape.cloud.cnaf.infn.it.vomses 
# wget https://indigo-iam.github.io/escape-docs/voms-config/voms-escape.cloud.cnaf.infn.it.lsc -O /etc/grid-security/vomsdir/escape/voms-escape.cloud.cnaf.infn.it.lsc
RUN mkdir -p /etc/vomses \
    && mkdir -p /etc/grid-security/vomsdir/escape \ 
    && mkdir -p /etc/grid-security/vomsdir/atlas \ 
    && mkdir -p /etc/grid-security/vomsdir/cms
COPY voms/vomsdir/escape/* /etc/grid-security/vomsdir/escape/
COPY voms/vomsdir/atlas/* /etc/grid-security/vomsdir/atlas/
COPY voms/vomsdir/cms/* /etc/grid-security/vomsdir/cms/
COPY voms/vomses/* /etc/vomses/

# Setup merged CERN CA file on Ubuntu based images.
# This file is contained in the `CERN-bundle.pem` file downloaded using 
RUN mkdir /certs \
    && touch /certs/rucio_ca.pem \
    && curl -fsSL 'https://cafiles.cern.ch/cafiles/certificates/CERN%20Root%20Certification%20Authority%202.crt' | openssl x509 -inform DER -out /tmp/cernrootca2.crt \
    && curl -fsSL 'https://cafiles.cern.ch/cafiles/certificates/CERN%20Grid%20Certification%20Authority(1).crt' -o /tmp/cerngridca.crt \
    && curl -fsSL 'https://cafiles.cern.ch/cafiles/certificates/CERN%20Certification%20Authority.crt' -o /tmp/cernca.crt \
    && cat /tmp/cernrootca2.crt >> /certs/rucio_ca.pem \
    && cat /tmp/cerngridca.crt >> /certs/rucio_ca.pem \
    && cat /tmp/cernca.crt >> /certs/rucio_ca.pem \
    && rm /tmp/*.crt \
    && update-ca-certificates

# Setup extension Rucio instance config
COPY configure-vre.py /usr/local/bin/
RUN chmod +x /usr/local/bin/configure-vre.py
COPY configure-vre.sh /usr/local/bin/before-notebook.d/

RUN mkdir -p /opt/rucio/etc \
    && chown -R $NB_UID /opt/rucio/etc 

ENV JUPYTER_ENABLE_LAB=yes
ENV JUPYTERHUB_SINGLEUSER_APP=jupyter-server

WORKDIR $HOME
USER $NB_UID

CMD ["start-notebook.py"]



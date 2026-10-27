FROM quay.io/jupyter/scipy-notebook:python-3.11.8
LABEL author="Image based on the work by Muhammad Aditya Hilmy - ESCAPE WP2 2020"
LABEL maintainer="VRE Team @ CERN 23/24 - E. Garcia, G. Guerrieri"
LABEL org.opencontainers.image.source https://github.com/vre-hub/environments
ARG BUILD_DATE
LABEL org.label-schema.build-date=$BUILD_DATE

USER $NB_UID

RUN conda install -y -n base mamba \
    && mamba install -y -c conda-forge python-gfal2 \
        gfal2 \
        gfal2-util \
        nodejs \
        jupyterlab">4,<5" \
        notebook"<7" \
        jupyterhub \
        jsonschema"<4.18" \
        jupyterlab_server \
        jupyter_server \
        traitlets \
        nbformat \
        ipykernel \
        PyJWT \
        ipywidgets \
    && conda clean --all -f -y

# eMudhra/emSign CA incident (October 2026): the emSign root was removed from
# the OS and Python trust stores. Refresh conda's copies (ca-certificates,
# certifi) and conda itself. Separate solve: conda>=26.9.4 may move mamba.
RUN mamba install -y -n base -c conda-forge \
        "conda>=26.9.4" \
        "certifi>=2026.10.19" \
        "ca-certificates>=2026.10.19" \
    && mamba clean -afy

# Install jupyterlab extensions
RUN python -m pip install rucio-clients==39.2.0 \
    rucio-jupyterlab==1.4.0 \
    && jupyter server extension enable --py rucio_jupyterlab --sys-prefix 

RUN python -m pip install swanoauthrenew==1.0.1 \ 
    && jupyter server extension enable --py swanoauthrenew --sys-prefix 

RUN python -m pip install reana-jupyterlab==1.0.2 \
    && jupyter server extension enable --py reana_jupyterlab --sys-prefix

RUN git clone https://github.com/vre-hub/inveniordm-jupyterlab-extension.git \
    && cd inveniordm-jupyterlab-extension \
    && git checkout --detach fc21415b9ee1abae327ffdcf9258455f913fe8b8 \
    && python -m pip install . \
    && cd .. \
    && rm -rf inveniordm-jupyterlab-extension
    
# Custom version of reana-client due to the jsonschema problem
# RUN python -m pip install git+https://github.com/mdonadoni/reana-client.git@vre-summer-24
# vre-summer-24 was breaking compatibility with Yadage. 
# vre-summer-25 might break OpenAPI spec. But there is no other way of building REANA due to
#  lower jsonchema<4 pin
RUN python -m pip install git+https://github.com/garciagenrique/reana-client.git@vre-summer-25

# Last Python step, so no later install can move these back: pip's vendored
# certifi, and fail the build if the certifi in use still has the emSign root.
RUN python -m pip install --upgrade "pip>=26.2.2" "certifi>=2026.10.19" \
    && python -c "import certifi; assert tuple(map(int, certifi.__version__.split('.'))) >= (2026, 10, 19), certifi.__version__"

USER root

# ca-certificates (apt) is installed unpinned, so a rebuild gets the Ubuntu
# bundle without the emSign root.
RUN apt-get update && \
    apt-get install -y wget gnupg ca-certificates build-essential curl voms-clients-java software-properties-common && \
    rm -rf /var/lib/apt/lists/* && \
    apt-get clean && \
    rm /opt/conda/bin/voms-proxy-init && \
    ln -s /usr/bin/voms-proxy-init /opt/conda/bin/voms-proxy-init

# ESCAPE grid-security
# Docs (not updated): https://docs.egi.eu/providers/operations-manuals/howto01_using_igtf_ca_distribution/#using-the-distribution-on-a-debian-or-debian-derived-platform
RUN wget -qO - https://dist.eugridpma.info/distribution/igtf/current/GPG-KEY-EUGridPMA-RPM-4 | gpg --dearmor -o /etc/apt/trusted.gpg.d/EGI-Key.gpg
RUN echo "deb http://repository.egi.eu/sw/production/cas/1/current egi-igtf core" > /etc/apt/sources.list.d/egi-igtf.list

RUN apt-get update && \
    apt-get install -y ca-policy-egi-core && \
    rm -rf /var/lib/apt/lists/*

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

# Setup jupyter server config for extensions
COPY configure-vre.py /usr/local/bin/
COPY configure_inveniordm_extension.py /usr/local/bin/
RUN chmod +x /usr/local/bin/configure-vre.py
COPY configure-vre.sh /usr/local/bin/before-notebook.d/

RUN mkdir -p /opt/rucio/etc \
    && chown -R $NB_UID /opt/rucio/etc 

ENV JUPYTER_ENABLE_LAB=yes
ENV JUPYTERHUB_SINGLEUSER_APP=jupyter-server

WORKDIR $HOME
USER $NB_UID

CMD ["start-notebook.py"]

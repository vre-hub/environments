FROM jupyter/scipy-notebook:python-3.9.13
LABEL author="VRE CERN team - testing !"
LABEL org.opencontainers.image.source https://github.com/goseind/jupyterlab-extension-setup

USER root
RUN pip install --upgrade pip

USER $NB_UID

# # rucio-jupyterlab>=0.9.8 
RUN pip install git+https://github.com/garciagenrique/jupyterlab-extension.git@upgrade_rucio-client_v1.30
RUN pip install swanoauthrenew==1.0.1 PyJWT\ 
    && jupyter serverextension enable --py rucio_jupyterlab --sys-prefix \
    && jupyter serverextension enable --py swanoauthrenew --sys-prefix \
    && pip install reana-client>=0.9.0 \
    && pip install ipykernel

RUN conda install -y -c conda-forge python-gfal2 \
    && conda clean --all -f -y

USER root

RUN apt update -y \
    && apt install -y build-essential curl voms-clients-java software-properties-common \
    && apt clean -y \
    && rm /opt/conda/bin/voms-proxy-init \
    && ln -s /usr/bin/voms-proxy-init /opt/conda/bin/voms-proxy-init

# ESCAPE grid-security and VOMS setup
RUN wget -q -O - https://dist.eugridpma.info/distribution/igtf/current/GPG-KEY-EUGridPMA-RPM-3 | apt-key add -

RUN apt update \
    && add-apt-repository 'deb http://repository.egi.eu/sw/production/cas/1/current egi-igtf core' \
    && apt -y install ca-certificates ca-policy-egi-core

RUN mkdir -p /etc/vomses \
    && wget https://indigo-iam.github.io/escape-docs/voms-config/voms-escape.cloud.cnaf.infn.it.vomses -O /etc/vomses/voms-escape.cloud.cnaf.infn.it.vomses \
    && mkdir -p /etc/grid-security/vomsdir/escape \
    && wget https://indigo-iam.github.io/escape-docs/voms-config/voms-escape.cloud.cnaf.infn.it.lsc -O /etc/grid-security/vomsdir/escape/voms-escape.cloud.cnaf.infn.it.lsc

# Setup merged CERN CA file --> get them from here: https://linuxsoft.cern.ch/mirror/repository.egi.eu/sw/production/cas/1/current/
# CERN specific configuration: Trusting the CERN CA (remove if not needed)
RUN mkdir /certs \
    && touch /certs/rucio_ca.pem \
    && curl -fsSL 'https://cafiles.cern.ch/cafiles/certificates/CERN%20Root%20Certification%20Authority%202.crt' | openssl x509 -inform DER -out /tmp/cernrootca2.crt \
    && curl -fsSL 'https://cafiles.cern.ch/cafiles/certificates/CERN%20Grid%20Certification%20Authority(1).crt' -o /tmp/cerngridca.crt \
    && curl -fsSL 'https://cafiles.cern.ch/cafiles/certificates/CERN%20Certification%20Authority.crt' -o /tmp/cernca.crt \
    && cat /tmp/cernrootca2.crt >> /certs/rucio_ca.pem \
    && cat /tmp/cerngridca.crt >> /certs/rucio_ca.pem \
    && cat /tmp/cernca.crt >> /certs/rucio_ca.pem

# Setup extension Rucio instance config
ADD configure.py /opt/setup/configure.py
ADD setup.sh /usr/local/bin/setup.sh
RUN fix-permissions /opt/setup \
    && fix-permissions /usr/local/bin/setup.sh \
    && sed -i -e 's/\r$/\n/' /usr/local/bin/setup.sh \
    && chmod +x /usr/local/bin/setup.sh

# CERN specific configuration: VRE Data Lake (remove if not needed)
ENV RUCIO_MODE=replica
ENV RUCIO_WILDCARD_ENABLED=1
ENV RUCIO_BASE_URL=https://vre-rucio.cern.ch
ENV RUCIO_AUTH_URL=https://vre-rucio-auth.cern.ch
ENV RUCIO_WEBUI_URL=https://vre-rucio-ui.cern.ch
ENV RUCIO_DISPLAY_NAME="VRE Data Lake"
ENV RUCIO_NAME=escape
ENV RUCIO_VOMS_ENABLED=1
ENV RUCIO_VOMS_VOMSES_PATH=/etc/vomses
ENV RUCIO_VOMS_CERTDIR_PATH=/etc/grid-security/certificates
ENV RUCIO_VOMS_VOMSDIR_PATH=/etc/grid-security/vomsdir
ENV RUCIO_CA_CERT=/certs/rucio_ca.pem
ENV RUCIO_DEFAULT_INSTANCE="vre"

RUN mkdir -p /opt/rucio \
    && chown -R $NB_UID /opt/rucio \
    && /usr/local/bin/setup.sh \
    && chown -R $NB_UID /etc/jupyter/jupyter_notebook_config.json \
    && chown -R $NB_UID /etc/jupyter/jupyter_notebook_config.py

ENV IPYTHONDIR=/etc/ipython
ADD ipython_kernel_config.json /etc/ipython/profile_default/ipython_kernel_config.json
RUN chown -R $NB_UID /etc/ipython
ENV JUPYTER_ENABLE_LAB=yes

WORKDIR $HOME
USER $NB_UID

CMD ["configure.sh", "start-notebook.sh"]

FROM nvcr.io/nvidia/pytorch:23.09-py3 
LABEL author="E. Garcia, M. Bunino"
LABEL maintainer="VRE Team @ CERN 23/24 - E. Garcia, G. Guerrieri"

USER root

RUN apt-get update -y
RUN apt-get install -y libglib2.0-dev libgfal2-dev python3-dev libboost-all-dev

RUN python -m pip install --upgrade pip
RUN python -m pip install 'jupyterhub==1.5.0'
RUN npm install -g configurable-http-proxy
RUN python -m pip install \
    'jupyterlab' \
    'notebook<7' \
    'nbclassic' \
    jupyter server --generate-config \
    asyncssh

RUN python -m pip install rucio-jupyterlab==0.10.0 \
    && jupyter serverextension enable --py rucio_jupyterlab --sys-prefix 

RUN apt update -y \
    && apt install -y build-essential curl voms-clients-java software-properties-common \
    && apt clean -y \
    && rm /opt/conda/bin/voms-proxy-init \
    && ln -s /usr/bin/voms-proxy-init /opt/conda/bin/voms-proxy-init

RUN wget -q -O - https://dist.eugridpma.info/distribution/igtf/current/GPG-KEY-EUGridPMA-RPM-3 | apt-key add -

RUN apt update \
    && add-apt-repository 'deb http://repository.egi.eu/sw/production/cas/1/current egi-igtf core' \
    && apt -y install ca-policy-egi-core

RUN mkdir -p /etc/vomses \
    && wget https://indigo-iam.github.io/escape-docs/voms-config/voms-escape.cloud.cnaf.infn.it.vomses -O /etc/vomses/voms-escape.cloud.cnaf.infn.it.vomses \
    && mkdir -p /etc/grid-security/vomsdir/escape \
    && wget https://indigo-iam.github.io/escape-docs/voms-config/voms-escape.cloud.cnaf.infn.it.lsc -O /etc/grid-security/vomsdir/escape/voms-escape.cloud.cnaf.infn.it.lsc

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

ADD asyncssh_config.py /opt/ssh/jupyterhub-singleuser
RUN fix-permissions /opt/ssh/jupyterhub-singleuser \
    && chown -R $NB_UID /opt/ssh/jupyterhub-singleuser \
    && chmod +x /opt/ssh/jupyterhub-singleuser

# Setup extension Rucio instance config
ADD configure.py /opt/setup-rucio-jupyterlab/configure.py
RUN fix-permissions /opt/setup-rucio-jupyterlab/configure.py \
    && chown -R $NB_UID /opt/setup-rucio-jupyterlab/configure.py \
    && chmod +x /opt/setup-rucio-jupyterlab/configure.py

ADD setup.sh /usr/local/bin/setup.sh
RUN fix-permissions /usr/local/bin/setup.sh \
    && sed -i -e 's/\r$/\n/' /usr/local/bin/setup.sh \
    && chmod +x /usr/local/bin/setup.sh

RUN mkdir -p /opt/rucio/etc \
#    && touch /opt/rucio/etc/rucio.cfg \
    && fix-permissions /opt/rucio/etc \
    && chown -R ${NB_UID}:${NB_GID} /opt/rucio/etc 

#    && /usr/local/bin/setup.sh 
#RUN chown -R $NB_UID $HOME/.jupyter/jupyter_notebook_config.json 
#    && chown -R $NB_UID /etc/jupyter/jupyter_notebook_config.py


#ENV IPYTHONDIR=/etc/ipython
#ADD ipython_kernel_config.json /etc/ipython/profile_default/ipython_kernel_config.json
#RUN chown -R $NB_UID /etc/ipython
ENV JUPYTER_ENABLE_LAB=yes

WORKDIR $HOME
USER $NB_UID

CMD ["setup.sh", "start-notebook.sh"]

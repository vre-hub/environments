FROM quay.io/jupyter/scipy-notebook:python-3.11.8
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
        #jupyterhub \
        jsonschema \
        jupyterlab_server \
        jupyter_server \
        traitlets \
        nbformat \
    && conda clean --all -f -y

# Install rucio-jupyterlab version with jlab v=4
RUN pip install rucio-jupyterlab==1.0.0 \
    && jupyter server extension enable --py rucio_jupyterlab --sys-prefix 
#    && jupyter labextension link . --dev-build=False 
#    && jupyter lab clean -y

RUN pip install swanoauthrenew==1.0.1 \ 
    && jupyter server extension enable --py swanoauthrenew --sys-prefix 

# RUN pip install reana-client>=0.9.0  #jsonschema version compatibility issue. 
# Not even working with RUN pip install git+https://github.com/mdonadoni/reana-client.git@vre-summer-24
RUN pip install ipykernel ipywidgets PyJWT 
#dogpile.cache

RUN pip install reana-jupyterlab \
    && jupyter server extension enable --py reana_jupyterlab --sys-prefix 

# RUN pip install --upgrade jupyterlab-git
# RUN pip install --upgrade jupyterlab_pygments 
# RUN pip install --upgrade jupyterlab_widgets
# RUN pip install --upgrade jupyterlab jupyterlab_server jupyter_server traitlets nbformat 

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

# Setup extension Rucio instance config
ADD vre_notebook_configuration.py /usr/local/bin/vre_notebook_configuration.py
ADD vre_notebook_configuration.sh /usr/local/bin/vre_notebook_configuration.sh
RUN fix-permissions /usr/local/bin/vre_notebook_configuration.sh \
    && sed -i -e 's/\r$/\n/' /usr/local/bin/vre_notebook_configuration.sh \
    && chmod +x /usr/local/bin/vre_notebook_configuration.sh

RUN mkdir -p /opt/rucio/etc \
    && chown -R $NB_UID /opt/rucio/etc \
    && /usr/local/bin/vre_notebook_configuration.sh \
    && chown -R $NB_UID $HOME/.jupyter/jupyter_server_config.json
    #&& chown -R $NB_UID /etc/jupyter/jupyter_notebook_config.py

# ADD ipython_kernel_config.json $HOME/.ipython/profile_default/ipython_kernel_config.json    
RUN fix-permissions $HOME/.jupyter    
#RUN fix-permissions $HOME/.ipython/profile_default
#RUN chmod -R $NB_UID $HOME/.ipython/profile_default 
#    && fix-permissions $HOME/.ipython/profile_default

ENV JUPYTER_ENABLE_LAB=yes
#ENV IPYTHONDIR=/etc/ipython
ENV JUPYTERHUB_SINGLEUSER_APP=jupyter-server

WORKDIR $HOME
USER $NB_UID

CMD ["vre_notebook_configuration.sh", "start-notebook.sh"]

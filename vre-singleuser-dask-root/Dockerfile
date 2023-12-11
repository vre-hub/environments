FROM ghcr.io/vre-hub/vre-singleuser-root:sha-c94d95a
LABEL author="Elena Gazzarrini for Analysis Grand Challenge on the VRE"
LABEL maintainer="Elena Gazzarrini"
ARG BUILD_DATE
LABEL org.label-schema.build-date=$BUILD_DATE

WORKDIR $HOME
USER root
# USER $NB_UID

RUN pip install dask==2022.6.0 \
    && pip install distributed==2022.6.0 \ 
    && pip install dask-gateway\ 
    && pip install jupyter-server-proxy \
    && jupyter serverextension enable --sys-prefix jupyter_server_proxy \
    && pip install dask-labextension==6.2.0 
 
WORKDIR $HOME
USER $NB_UID 

CMD ["setup.sh", "start-notebook.sh"] 

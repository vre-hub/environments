#FROM ghcr.io/vre-hub/vre-singleuser-py38:sha-8cddc67
FROM ghcr.io/vre-hub/vre-singleuser:sha-7210810
LABEL author="VRE Team @ CERN 22/23 - E. Garcia, E. Gazzarrini, D. Gosein"
LABEL maintainer="VRE Team @ CERN 22/23 - E. Garcia, E. Gazzarrini, D. Gosein"
LABEL org.opencontainers.image.source https://github.com/vre-hub/environments
ARG BUILD_DATE
LABEL org.label-schema.build-date=$BUILD_DATE

USER root

# Install ROOT
ENV LANG=C.UTF-8
ARG ROOT_BIN=root_v6.26.10.Linux-ubuntu20-x86_64-gcc9.4.tar.gz	

WORKDIR /opt

COPY packages packages

RUN apt-get -y update

RUN apt-get update -qq \
    && ln -sf /usr/share/zoneinfo/UTC /etc/localtime \
    && apt-get -y install $(cat packages) wget\
    && rm -rf /var/lib/apt/lists/*\
    && wget https://root.cern/download/${ROOT_BIN} \
    && tar -xzvf ${ROOT_BIN} \
    && rm -f ${ROOT_BIN} \
    && echo /opt/root/lib >> /etc/ld.so.conf \
    && ldconfig

ENV ROOTSYS /opt/root
ENV PATH $ROOTSYS/bin:$PATH
ENV PYTHONPATH $ROOTSYS/lib:$PYTHONPATH
ENV CLING_STANDARD_PCH none

RUN mkdir -p /opt/conda/share/jupyter/kernels/root \
    && cp -r /opt/root/etc/notebook/kernels/root/kernel.json /opt/conda/share/jupyter/kernels/root/kernel.json

RUN pip install metakernel

WORKDIR $HOME
USER $NB_UID

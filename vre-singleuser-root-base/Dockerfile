# FROM rootproject/root:6.26.02-ubuntu20.04 as root-base

FROM jupyter/scipy-notebook:python-3.11

USER root

# Install system dependencies
RUN apt-get update -y && apt-get install -y rsync wget build-essential curl && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

RUN pip install --upgrade pip jupyter_server notebook traitlets

# Copy ROOT installation
# COPY --from=root-base /opt/root /opt/root

# Install ROOT
ENV LANG=C.UTF-8
ARG ROOT_BIN=root_v6.26.14.Linux-ubuntu20-x86_64-gcc9.4.tar.gz

WORKDIR /opt

COPY packages packages

RUN apt-get update -qq \
    && ln -sf /usr/share/zoneinfo/UTC /etc/localtime \
    && apt-get -y install $(cat packages) wget\
    && rm -rf /var/lib/apt/lists/*
    
RUN wget https://root.cern/download/${ROOT_BIN} \
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

 #RUN conda install -c conda-forge metakernel # conda complains, installing though pip
RUN pip install metakernel


WORKDIR $HOME
USER $NB_UID

RUN mkdir HiggsTutorial && \
    wget https://launchpad.net/mg5amcnlo/3.0/3.6.x/+download/MG5_aMC_v3.6.1.beta.tar.gz && \
    tar -xvzf MG5_aMC_v3.6.1.beta.tar.gz && rm MG5_aMC_v3.6.1.beta.tar.gz

CMD ["start-notebook.sh"]
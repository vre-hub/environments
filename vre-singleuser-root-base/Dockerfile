# FROM rootproject/root:6.26.02-ubuntu20.04 as root-base

FROM quay.io/jupyter/scipy-notebook:python-3.12

USER root

ENV LANG=C.UTF-8

ARG ROOT_BIN=root_v6.32.04.Linux-ubuntu24.04-x86_64-gcc13.2.tar.gz

WORKDIR /opt

COPY packages packages

RUN apt-get update -qq \
 && ln -sf /usr/share/zoneinfo/UTC /etc/localtime \
 && apt-get -y install $(cat packages) wget\
 && rm -rf /var/lib/apt/lists/*\
 && wget https://root.cern/download/${ROOT_BIN} \
 && tar -xzvf ${ROOT_BIN} \
 && rm -f ${ROOT_BIN} \
 && echo /opt/root/lib >> /etc/ld.so.conf \
 && ldconfig

#RUN yes | unminimize

ENV ROOTSYS /opt/root
ENV PATH $ROOTSYS/bin:$PATH
ENV PYTHONPATH $ROOTSYS/lib:$PYTHONPATH
ENV CLING_STANDARD_PCH none


WORKDIR $HOME
USER $NB_UID

RUN mkdir HiggsTutorial && \
    wget https://launchpad.net/mg5amcnlo/3.0/3.6.x/+download/MG5_aMC_v3.6.1.beta.tar.gz && \
    tar -xvzf MG5_aMC_v3.6.1.beta.tar.gz && rm MG5_aMC_v3.6.1.beta.tar.gz

CMD ["start-notebook.sh"]
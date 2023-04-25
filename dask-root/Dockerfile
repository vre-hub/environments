FROM pangeo/base-notebook:2021.05.04 

LABEL maintainer="Elena Gazzarrini <elena.gazzarrini@cern.ch>"

USER root

ENV LANG=C.UTF-8

# ARG ROOT_BIN=root_v6.28.00.Linux-ubuntu22-x86_64-gcc11.3.tar.gz
ARG ROOT_BIN=root_v6.28.00.Linux-ubuntu20-x86_64-gcc9.4.tar.gz

WORKDIR /opt

COPY packages packages

# RUN  apt-get install -rpath "@loader_path/../lib/root" "@loader_path/../../lib/root"  /opt/local/Library/Frameworks/Python.framework/Versions/3.10/lib/python3.10/site-packages/libcppyy3_10.6.24.so
# RUN  apt-get install -rpath "@loader_path/../lib/root" "@loader_path/../../lib/root"  /opt/local/libexec/root6/lib/root/libROOTPythonizations3_10.6.24.00.so
# RUN  apt-get install -rpath "@loader_path/../lib/root" "@loader_path/../../lib/root"  /opt/local/libexec/root6/lib/root/libRIO.6.24.00.so

RUN apt-get -y update -qq \
 && ln -sf /usr/share/zoneinfo/UTC /etc/localtime \
 && apt-get -y install $(cat packages) wget\
 && rm -rf /var/lib/apt/lists/*\
 && wget https://root.cern/download/${ROOT_BIN} \
 && tar -xzvf ${ROOT_BIN} \
 && rm -f ${ROOT_BIN} \
 && echo /opt/root/lib >> /etc/ld.so.conf \
 && ldconfig
RUN yes | unminimize

ENV ROOTSYS /opt/root
ENV PATH $ROOTSYS/bin:$PATH
ENV PYTHONPATH $ROOTSYS/lib:$PYTHONPATH
ENV CLING_STANDARD_PCH none

CMD ["root", "-b"]

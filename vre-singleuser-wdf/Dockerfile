#FROM quay.io/jupyter/scipy-notebook:python-3.11.6
FROM  ghcr.io/vre-hub/vre-singleuser-py311    
#sha-281055c
LABEL author="Alberto Iess"
LABEL maintainer="Alberto Iess, VRE Team @ CERN - E. Garcia, G. Guerrieri"
ARG BUILD_DATE
LABEL org.label-schema.build-date=$BUILD_DATE


# runtime dependencies to install wdf
USER root

# Install gnupg so that the following gpg commands work
RUN apt-get update && apt-get install -y --no-install-recommends gnupg

RUN set -eux; \
    # Import the GPG key to verify package integrity
    gpg --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 871920D1991BC93C && \
    gpg --export 871920D1991BC93C | tee /etc/apt/trusted.gpg.d/ubuntu.lafibre.info.gpg && \
    
    # Update package list and install essential dependencies
    apt-get update && \
    apt-get install --no-install-recommends -y \
        tzdata wget git vim build-essential && \
    
    # Install runtime dependencies for WDF
    apt-get install --no-install-recommends -y \
        cmake \
        pkg-config \
        libboost-all-dev \
        pybind11-dev python3-pybind11 \
        libfftw3-3 libfftw3-dev libfftw3-bin \
        libgsl-dev && \
    
    # Clean up to reduce image size
    apt-get clean && rm -rf /var/lib/apt/lists/*

###########################
## not using venv, instead we use the base conda env and fixing env vars
ENV LD_LIBRARY_PATH="/opt/conda/lib:$LD_LIBRARY_PATH"
ENV PYTHONPATH="/opt/conda/lib/python3.11:/opt/conda/lib/python3.11/site-packages:$PYTHONPATH"  

## While the installation of pst4 and the use of `venv`, it is needed the `ENV_ROOT` env var
## > echo $ENV_ROOT/
## > /opt/venv/
ENV ENV_ROOT="/opt/conda"

# install requirements
COPY requirements.txt .
# Using installed version of pip
RUN echo "pip:"; pip -V && \
    echo "pip3:" pip3 -V
RUN pip3 install --no-cache-dir wheel
RUN pip3 install --no-cache-dir -r requirements.txt
###########################

#install GSL 
RUN set -ex \
    && wget https://mirror.ibcp.fr/pub/gnu/gsl/gsl-2.7.1.tar.gz\
    && tar -xzf gsl-2.7.1.tar.gz \
    && cd gsl-2.7.1\
    && ./configure --disable-dependency-tracking --build=aarch64-linux-gnu --host=aarch64-linux-gnu --prefix=/home/jovyan/gsl CFLAGS="-O1"\
    && make -j "$(nproc)" \
    && make install \
    && cd .. \
    && rm -rf gsl-2.7.1 \
    && rm gsl-2.7.1.tar.gz

#install FrameLib
RUN set -ex \
    && git clone https://git.ligo.org/virgo/virgoapp/Fr.git \
    && cd  Fr && cmake CMakeLists.txt \
    && make -j "$(nproc)" \
    && make install \
    && cd .. \
    && rm -rf Fr  

#install P4TSA
RUN git clone https://github.com/elenacuoco/p4TSA && cd p4TSA && git checkout a89db30 && cmake CMakeLists.txt \
    && make -j "$(nproc)" \
    && make install \
    && cd python-wrapper \
    && python setup.py  install \
    && cd .. \
    && cd .. \
    && rm -fr p4TSA

RUN /sbin/ldconfig 

RUN git clone https://gitlab.com/wdfpipe/wdf.git && cd wdf \
    && python setup.py  install \
    && cd .. \ 
    && rm -fr wdf

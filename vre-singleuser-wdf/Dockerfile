# Based on same strategy as the one done at 
# https://gitlab.in2p3.fr/escape2020/virtual-environment/docker-images/-/blob/master/datalake-singleuser-wdf/Dockerfile

python 3.11 needed... ???!!!!

# ------------------------------------------------------
# Env wdf-python
# https://gitlab.com/wdfpipe/createwdfenv/-/blob/main/dockers/env_python/Dockerfile

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Rome

# create and activate virtual environment
RUN python3.11 -m venv /opt/venv
ENV ENV_ROOT="/opt/venv"
ENV PATH="/opt/venv/bin:$PATH"
ENV LD_LIBRARY_PATH="/opt/venv/lib:$LD_LIBRARY_PATH"
ENV PYTHONPATH="/opt/venv/lib/python3.11:/opt/venv/lib/python3.11/site-packages:$PYTHONPATH"


# install requirements
COPY requirements.txt .  
RUN pip3 install -r requirements.txt

# env wdf
# https://gitlab.com/wdfpipe/createwdfenv/-/blob/main/dockers/env_wdf/Dockerfile

# runtime dependencies to install wdf
RUN set -eux; \
	apt-get update; \
	apt-get install -y --no-install-recommends \
	cmake \
    libboost-all-dev \
    pybind11-dev python3-pybind11 \
    libfftw3-3 libfftw3-dev libfftw3-bin \
    libgsl-dev; \
	rm -rf /var/lib/apt/lists/*
  
#install FrameLib
RUN set -ex \
    && git clone https://git.ligo.org/virgo/virgoapp/Fr.git \
    && cd  Fr && cmake CMakeLists.txt \
    && make -j "$(nproc)" \
    && make install \
    && cd .. \
    && rm -rf Fr  

#install P4TSA
RUN git clone https://github.com/elenacuoco/p4TSA && cd p4TSA && cmake CMakeLists.txt \
    && make -j "$(nproc)" \
    && make install \
    && cd python-wrapper \
    && python setup.py  install \
    && cd .. \
    && cd .. \
    && rm -fr p4TSA

RUN /sbin/ldconfig 

# env wdfpipe
# https://gitlab.com/wdfpipe/wdf/-/blob/master/dockers/wdfpipe/Dockerfile

RUN https://gitlab.com/wdfpipe/wdf.git && cd wdf
RUN mkdir tmp1/
ADD . tmp1/
RUN cd tmp1/ && python setup.py  install &&\
    cd .. && rm -fr tmp1/ 

CMD ["/bin/bash"]

FROM ghcr.io/vre-hub/vre-singleuser-py38:sha-7ed7d80
LABEL author="Misha Smirnov"
LABEL maintainer="VRE Team @ CERN 22/23 - E. Garcia, E. Gazzarrini, D. Gosein"
LABEL org.opencontainers.image.source https://github.com/vre-hub/environments
ARG BUILD_DATE
LABEL org.label-schema.build-date=$BUILD_DATE

USER root
WORKDIR /opt

# Install LaTeX
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    texlive-latex-base \
    texlive-fonts-recommended

COPY environment.yaml environment.yaml

RUN conda install mamba -n base -c conda-forge && \
    mamba env create -f environment.yaml && \
    conda clean --all -f -y

ENV PATH /opt/conda/envs/comb_km3net_cta/bin:$PATH
ENV CONDA_DEFAULT_ENV comb_km3net_cta

RUN echo "conda activate comb_km3net_cta" >> ~/.bashrc

WORKDIR $HOME
USER $NB_UID

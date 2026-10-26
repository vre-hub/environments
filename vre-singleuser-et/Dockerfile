ARG BASE_IMAGE=ghcr.io/vre-hub/vre-singleuser-py311:latest
FROM ${BASE_IMAGE}
LABEL author="Paul Laycock"
LABEL maintainer="Paul Laycock <paul.laycock@unige.ch>"
ARG BUILD_DATE
LABEL org.label-schema.build-date=$BUILD_DATE

USER root
# eMudhra/emSign CA incident (October 2026): the emSign root was removed from
# the OS and Python trust stores. Refresh every copy the image carries:
# the Ubuntu bundle, conda's certifi and conda itself, and pip's vendored one.
RUN apt-get update \
    && apt-get install -y --no-install-recommends --only-upgrade ca-certificates \
    && rm -rf /var/lib/apt/lists/*
RUN mamba install -y -n base -c conda-forge "certifi>=2026.10.19" "conda>=26.9.4" \
    && mamba clean -afy
RUN python -m pip install --upgrade "pip>=26.2.2" "certifi>=2026.10.19" \
    && python -m pip install nopayloaddb-client==0.3.0

USER $NB_UID

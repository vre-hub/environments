ARG BASE_IMAGE=ghcr.io/vre-hub/vre-singleuser-py311:latest
FROM ${BASE_IMAGE}
LABEL author="Paul Laycock"
LABEL maintainer="Paul Laycock <paul.laycock@unige.ch>"
ARG BUILD_DATE
LABEL org.label-schema.build-date=$BUILD_DATE

USER root
RUN python -m pip install --upgrade pip \
    && python -m pip install nopayloaddb-client==0.3.0

USER $NB_UID

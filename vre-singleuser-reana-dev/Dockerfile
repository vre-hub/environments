FROM jupyter/scipy-notebook:python-3.9.13
LABEL author="Image based on the work by Muhammad Aditya Hilmy - ESCAPE WP2 2020"
LABEL maintainer="VRE Team @ CERN 22/23 - E. Garcia, E. Gazzarrini, D. Gosein"
LABEL org.opencontainers.image.source https://github.com/vre-hub/environments
ARG BUILD_DATE
LABEL org.label-schema.build-date=$BUILD_DATE

RUN pip install --upgrade pipw

USER $NB_UID

RUN pip install reana-client ipykernel 

RUN mkdir -p /certs

USER root

ENV JUPYTER_ENABLE_LAB=yes

WORKDIR $HOME
USER $NB_UID

CMD ["start-notebook.sh"]

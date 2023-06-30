FROM jupyterhub/k8s-hub:2.0.0
LABEL maintainer="VRE Team @ CERN 22/23 - E. Garcia, E. Gazzarrini, D. Gosein"
LABEL org.opencontainers.image.source https://github.com/vre-hub/environments
ARG BUILD_DATE
LABEL org.label-schema.build-date=$BUILD_DATE


USER root

ADD ./jupyterhub.d /escape/jupyterhub.d
RUN pip install -e /escape/jupyterhub.d/AuthStateJupyterHub
RUN pip install -e /escape/jupyterhub.d/SpawnHookOAuthenticator
RUN pip install -e /escape/jupyterhub.d/OIDCAuthenticator

USER ${NB_USER}

CMD ["authstatejupyterhub", "--config", "/usr/local/etc/jupyterhub/jupyterhub_config.py"]

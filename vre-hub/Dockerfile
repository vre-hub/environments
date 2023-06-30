FROM jupyterhub/k8s-hub:2.0.0

USER root

ADD ./jupyterhub.d /escape/jupyterhub.d
RUN pip install -e /escape/jupyterhub.d/AuthStateJupyterHub
RUN pip install -e /escape/jupyterhub.d/SpawnHookOAuthenticator
RUN pip install -e /escape/jupyterhub.d/OIDCAuthenticator

USER ${NB_USER}

CMD ["authstatejupyterhub", "--config", "/usr/local/etc/jupyterhub/jupyterhub_config.py"]

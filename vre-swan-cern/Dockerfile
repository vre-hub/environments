FROM gitlab-registry.cern.ch/swan/docker-images/jupyter/swan-cern:v0.0.58

ENV RUCIO_JUPYTERLAB_VERSION="1.4.1"

COPY ./wheels/rucio_jupyterlab-*.whl /tmp/
RUN pip install --no-deps --no-cache-dir /tmp/rucio_jupyterlab-*.whl
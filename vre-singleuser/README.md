# VRE singleuser Base Image

This image based on the original [ESCAPE Data Lake-as-a-Service Singleuser Base Image](https://gitlab.cern.ch/escape-wp2/docker-images/-/tree/master/datalake-singleuser) (restricted acces) which is derived from [jupyter/scipy-notebook](https://hub.docker.com/r/jupyter/scipy-notebook) with some modifications:

1. Python version is `3.9.17`
2. [rucio-jupyterlab](https://pypi.org/project/rucio-jupyterlab) is installed.
3. The image is compatible with [rucio-clients](https://pypi.org/project/rucio-clients) version 1.30 - please report any possible bug or error found.
4. ESCAPE `ca-certificates` and [VOMSes](https://indigo-iam.github.io/escape-docs/) files are preinstalled.
5. The configuration for the Rucio JupyterLab extension is preset to connect with the ESCAPE Data Lake.
6. [python-gfal2](https://anaconda.org/conda-forge/python-gfal2) and `voms-clients-java` is installed to enable direct Rucio Download functionality.
7. [swanoauthrenew](https://pypi.org/project/swanoauthrenew/) is installed to enable automatic OIDC token refresh.

## Using the image as a standalone instance

If you want to take advantage of the extension's capability in your own machine, you can do a simple Docker run:

```sh
docker run -p 8888:8888 docker pull ghcr.io/vre-hub/vre-singleuser:latest
```

You can also override the default environment values (some of which are specific to the ESCAPE instance, such as the service URLs) specified in the [Dockerfile](Dockerfile) within the singleuser extraEnv specification inside the [zero-to-jupyterhub Helm release](https://github.com/vre-hub/vre/tree/main/infrastructure/cluster/flux-v2) (Update link when jhub moved to flux) of your deployment. Take a closer look at [configure.py](configure.py) to see all the available envs. Refer to [this configuration guide](https://github.com/rucio/jupyterlab-extension/blob/master/CONFIGURATION.md) for details.

## Extending the image

If you want to extend the image and use it as a part of the VRE, there are some things to remember:

1. Try not to modify the `CMD` directive. But if you really need to do this, make sure that `configure.sh` (located in `/usr/local/bin/configure.sh`) is called, since that script is responsible for setting up the extension and OIDC parameters.
2. If you need to add a file, make sure that the container user has the necessary permission to access the file. You can use envs `$NB_UID`, `$NB_GID`, `$NB_USER`, and `$HOME` to get the user ID, group ID, username, and home directory respectively.
3. Make sure that the user and workdir values are set to their original values:

```
WORKDIR $HOME
USER $NB_UID
```

[comment]: <> (An example of an image that extends this image is the [datalake-singleuser-root](https://gitlab.cern.ch/escape-wp2/docker-images/-/tree/master/datalake-singleuser-root) image, which comes with PyROOT preinstalled.)

Based on all the previous work done by the ESCAPE Data Lake-as-a-Service group and outputs. 


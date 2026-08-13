# VRE singleuser BASE python 3.11 iamge

This image based on the original [ESCAPE Data Lake-as-a-Service Singleuser Base Image](https://gitlab.cern.ch/escape-wp2/docker-images/-/tree/master/datalake-singleuser) (restricted acces) which is derived from [quay.io/jupyter/scipy-notebook](https://quay.io/jupyter/scipy-notebook)($\ast$) with some modifications:

1. Python version is `3.11.8`.
2. The followinf JupyterLab extensions are installed:
  * [rucio-jupyterlab](https://pypi.org/project/rucio-jupyterlab) v1.0.0.
    * The configuration for the Rucio JupyterLab extension is preset to connect with the ESCAPE Data Lake.
  * [reana-jupyterlab](https://github.com/vre-hub/reana-jupyterlab-extension) v1.0.0.
  * [inveniordm-jupyterlab](https://github.com/vre-hub/inveniordm-jupyterlab-extension).
    * See [Configuring the InvenioRDM extension](#configuring-the-inveniordm-extension) below.
  * [swanoauthrenew](https://pypi.org/project/swanoauthrenew/) v1.0.1 to enable renewal of tokens.
3. The image is compatible with [rucio-clients](https://pypi.org/project/rucio-clients)  `release-34.6.0` - please report any possible bug or error found.
4. ESCAPE `ca-certificates` and [VOMSes](https://indigo-iam.github.io/escape-docs/) files are preinstalled.
5. [python-gfal2](https://anaconda.org/conda-forge/python-gfal2) and `voms-clients-java` is installed to enable direct Rucio Download functionality.

($\ast$) Please note that since Oct 2023, Jupyter stopped pushing images to Docker Hub and start using quay.io

## Using the image as a standalone instance

If you want to take advantage of the extension's capability in your own machine, you can do a simple Docker run:

```sh
docker run -p 8888:8888 docker pull ghcr.io/vre-hub/vre-singleuser-py311:latest
```

You can also override the default environment values (some of which are specific to the ESCAPE instance, such as the service URLs) specified in the [Dockerfile](Dockerfile) within the singleuser extraEnv specification inside the [zero-to-jupyterhub Helm release](https://github.com/vre-hub/vre/tree/main/infrastructure/cluster/flux) of your deployment. Take a closer look at [configure-vre.py](configure-vre.py) to see all the available envs. Refer to [this configuration guide](https://github.com/rucio/jupyterlab-extension/blob/master/CONFIGURATION.md) for details.

## Extending the image

If you want to extend the image and use it as a part of the VRE, there are some things to remember:

1. To custimize the image please have a look to the [Startup Docker Stack documentation Hooks](https://jupyter-docker-stacks.readthedocs.io/en/latest/using/common.html#startup-hooks).
2. If you need to add a file, make sure that the container user has the necessary permission to access the file. You can use envs `$NB_UID`, `$NB_GID`, `$NB_USER`, and `$HOME` to get the user ID, group ID, username, and home directory respectively.
3. Make sure that the user and workdir values are set to their original values:

```
WORKDIR $HOME
USER $NB_UID
```

Based on all the previous work done by the ESCAPE Data Lake-as-a-Service group since 2020. 

## Configuring the InvenioRDM extension

`configure_inveniordm_extension.py` writes the extension's settings into the
Jupyter server config at spawn time. Everything below is optional; with none of
it set the image keeps its previous behaviour.

| Variable | Default | Purpose |
| --- | --- | --- |
| `INVENIORDM_REQUEST_MODE` | `local` | `local` or `proxy`. Anything else is treated as `local`. |
| `ZENODO_OAUTH_CLIENT_ID` | bundled | OAuth client ID for Zenodo. |
| `CDS_OAUTH_CLIENT_ID` | bundled | OAuth client ID for CDS. |
| `ZENODO_SANDBOX_OAUTH_CLIENT_ID` | bundled | OAuth client ID for Zenodo Sandbox. |
| `<PREFIX>_PROXY_URL` | unset | Public URL of the InvenioRDM API proxy for that server. |
| `<PREFIX>_PROXY_SESSION_COOKIE_NAME` | `<server-id>_proxy_session` | Session cookie name for that proxy. Must be unique per proxy. |

`<PREFIX>` is `ZENODO`, `CDS` or `ZENODO_SANDBOX`.

### Why proxy mode exists

In `local` mode the extension performs OAuth from the user's own Jupyter
server, and builds its redirect URI from the server's `base_url`. Under
JupyterHub that is `/user/<username>/`, so every user ends up with a different
redirect URI. InvenioRDM matches redirect URIs as exact strings, so no single
OAuth application can cover them and login cannot work for more than one
registered user.

Proxy mode sends the OAuth flow through a shared
[API proxy](https://github.com/vre-hub/inveniordm-jupyterlab-extension/tree/main/deploy)
instead, which has one fixed redirect URI for every user, and keeps the access
token out of the singleuser pods.

The bundled OAuth client IDs only work for a JupyterLab on `localhost`, so any
real deployment must supply its own.

### Behaviour worth knowing

* In proxy mode a server with no `<PREFIX>_PROXY_URL` is left out of the
  configuration. The extension requires `proxy_url` and
  `proxy_session_cookie_name` on every configured server, and refuses to load
  at all if one is missing.
* Proxy mode with no proxy configured for any server falls back to `local`,
  so browsing keeps working rather than the extension disappearing.

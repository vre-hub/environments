# Integration of the Rucio JupyterLab extension in the interTwin infrastructure

The extentension interacts with the interTwin RUCIO instance, running at DESY. The Jupyter session is spawned by [interLink](https://github.com/interTwin-eu/interLink), a package able to run a k8s pod (and thus any contenairised application) on remote resources.

Please note that this image is still under development and will be constantly evolving

## Try this image 

**Needs both an EGI CheckIn and an interTwin Rucio active account**

 - Connect to the [cluster](https://jhub.131.154.98.40.myip.cloud.infn.it/)
 - Use the following image within the `Select your desired image` field, and select the desired offload mode. You must enable an offloading mode to be able to interact with Rucio.
 ```bash
 docker://ghcr.io/vre-hub/vre-singleuser-intertwin_dev:sha-7d09a10
 ```

### Setup your image to be compatible with interLink

Within your Dockerfile image, install the following packages and add the `asyncssh_config.py` to the container. You could have a look to the [Dockerfile](./Dockerfile) as well.

```Dockerfile
# Spawning a jupyterLab session needs any jupyter BASE layer
FROM jupyter/scipy-notebook:python-3.9.13

RUN conda install -y -n base mamba \
    && mamba install -y -c conda-forge asyncssh jupyterhub==1.5.0 \
    && conda clean --all -f -y

ADD asyncssh_config.py /opt/ssh/jupyterhub-singleuser
RUN fix-permissions /opt/ssh/jupyterhub-singleuser \
    && chown -R $NB_UID /opt/ssh/jupyterhub-singleuser \
    && chmod +x /opt/ssh/jupyterhub-singleuser
```
with 
```python
$ cat asyncssh_config.py

#!/opt/conda/bin/python
# -*- coding: utf-8 -*-
#
# D. Ciangottini
#
import re
import sys
from jupyterhub.singleuser import main
import asyncssh
import logging
import sys
import asyncio
import os
from subprocess import Popen

ssh_host = os.environ.get("JHUB_HOST")
ssh_url_port = os.environ.get("SSH_PORT")
username = os.environ.get("JUPYTERHUB_USER")
token = os.environ.get("JUPYTERHUB_API_TOKEN")

fwd_port = os.environ.get("FWD_PORT")

async def run_client():
    async with asyncssh.connect(
                    host=ssh_host,
                    port=int(ssh_url_port),
                    username=username,
                    password=token,
                    known_hosts=None,
                ) as conn:
        conn.set_keepalive(interval=14.0, count_max=10)
        listener = await conn.forward_remote_port(
                "0.0.0.0",
                int(fwd_port),
                "0.0.0.0",
                int(fwd_port),
        )
        await listener.wait_closed()


if __name__ == '__main__':
    print("Connecting ssh...")
    loop = asyncio.get_event_loop()
    loop.create_task(run_client())

    print("Starting JLAB")
    sys.argv[0] = re.sub(r'(-script\.pyw|\.exe)?$', '', sys.argv[0])
    sys.exit(main())
```

### Install the Rucio [JupyterLab extension](https://github.com/rucio/jupyterlab-extension) in the container

Within your Dockerfile add the following lines. Check, and addapt if needed, the content of the bash and python files that also need to be added to the container.

```Dockerfile
# Installation of the RUCIO JupyterLab extension

RUN conda install -y -n base mamba \
    && mamba install -y -c conda-forge python-gfal2

# jupyterlab extension compatible with jlab v=3.X.Y
RUN pip install rucio-jupyterlab==0.10.0 \
    && jupyter serverextension enable --py rucio_jupyterlab --sys-prefix 

ADD configure.py /opt/setup-rucio-jupyterlab/configure.py
RUN fix-permissions /opt/setup-rucio-jupyterlab/configure.py \
    && chown -R $NB_UID /opt/setup-rucio-jupyterlab/configure.py \
    && chmod +x /opt/setup-rucio-jupyterlab/configure.py

ADD setup.sh /usr/local/bin/setup.sh
RUN fix-permissions /usr/local/bin/setup.sh \
    && sed -i -e 's/\r$/\n/' /usr/local/bin/setup.sh \
    && chmod +x /usr/local/bin/setup.sh

RUN mkdir -p /opt/rucio/etc \
    && fix-permissions /opt/rucio/etc \
    && chown -R ${NB_UID}:${NB_GID} /opt/rucio/etc 

ENV JUPYTER_ENABLE_LAB=yes

CMD ["setup.sh", "start-notebook.sh"]
```
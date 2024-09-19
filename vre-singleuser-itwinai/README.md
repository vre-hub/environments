# CERN VRE and itwinai Docker integration

This repository summarizes all the necesary steps to build an 
[interTwin/itwinai](https://github.com/interTwin-eu/itwinai) image that also contains 
the [Rucio JupyterLab extension](https://github.com/rucio/jupyterlab-extension),
and that can be spawned by a JupyterHub.

In terms of requirements, the `itwinai` library needs the `Torch` Machine 
Learning library and `CUDA` drivers, and the Rucio extension all the 
[Jupyter docker-stacks](https://jupyter-docker-stacks.readthedocs.io/en/latest/using/selecting.html).
To keep things as simple as possible, we will be using all the upstream 3rd
party base images as base layers for the following intermediate images.

Starting from a base layer provided by `itwinai`, we will install all the Jupyter machinery
following the same building stages as the Jupyter project.

- The [itwinai-docker-stacks-foundation](./itwinai-docker-stacks-foundation/)
  folder builds the same image as the `docker-stacks-foundation` image ( 
  Python versionn set to 3.10), only by changing the base layer to the 
  `ghcr.io/intertwin-eu/itwinai:0.2.2-torch2.1-root` image 
  ([link](https://github.com/interTwin-eu/itwinai/pkgs/container/itwinai/275623563?tag=0.2.2-torch2.1-root)).
    - Because of the size of the `itwinai` image, this was build locally and later
      pushed to the `ghcr.io/vre-hub` [image registry](https://github.com/orgs/vre-hub/packages).
- The [itwinai-base-notebook](./itwinai-base-notebook/) folder builds the
  equivalent `base-notebook` image, starting from the `itwinai-docker-stacks-foundation`
  base image.
- The [itwinai-minimal-notebook](./itwinai-minimal-notebook/) subdirectory 
  follows the same strategy that above with the `minimal-notebook` stage.
- Finally, the [itwinai-rucio-extension](./itwinai-rucio-extension/) folder builds
  an image with the `itwinai` package, all the Jupyter software and the
  Rucio JupyterLab extension configured to access the interTwin Rucio instace.

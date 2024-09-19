# itwin - Rucio jupyterlab extension

This directory builds a docker image containing the `itwinai` library,
the Jupyter software stack and the Rucio JupyterLab extension.

The base layer is
```Docker
FROM ghcr.io/vre-hub/itwinai-minimal-notebook:0.2.2-torch2.1-py3.10
```

The image is bubuiltild locally and pushed to the 
[vre-hub package repository](https://github.com/vre-hub/environments/pkgs/container/itwinai-rucio-jlab).
 

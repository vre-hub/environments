#  VRE singleuser root image

This image is based on the CERN [VRE singleuser Base Image](https://github.com/vre-hub/environments/tree/main/vre-singleuser) and the original [ESCAPE Data Lake-as-a-Service Singleuser Base Image](https://gitlab.cern.ch/escape-wp2/docker-images/-/tree/master/datalake-singleuser) with some modifications:

 - Python version is downfraded to version 3.8 due to compatibility issues with ROOT.
 - ROOT v6.26.10 is installed.
    - The image contains aswell a ROOT C++ kernel for JupyterLab.
 - [rucio-jupyterlab](https://pypi.org/project/rucio-jupyterlab) is installed.


## Extending the image

Follow the same instructions as for the [VRE singleuser Base Image](https://github.com/vre-hub/environments/blob/main/vre-singleuser/README.md).

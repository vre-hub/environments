## VRE-SWAN


This folder clones the content of the 
[SWAN](https://github.com/swan-cern/jupyter-images/tree/main/swan)
directory within the [swan-cern/jupyter-images](https://github.com/swan-cern/jupyter-images)
repository, solely for VRE tessting purposes and the integration of the 
[rucio-jupyterlab](https://github.com/rucio/jupyterlab-extension) within
SWAN infrastructure.

The repository is cloned at commit [28cc817](https://github.com/swan-cern/jupyter-images/commit/28cc817573674ee7287bd077eacd35752e4747b5).

Changes to the original project:
 - `/scripts/others/userconfig.sh` --> Sourcing ESCAPE CVMFS repo
 - `python/jupyter_server_config.py` --> workaround to add rucio instances configurations
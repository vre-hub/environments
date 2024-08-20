[![Docker automatic build and publish](https://github.com/vre-hub/environments/actions/workflows/env-build.yaml/badge.svg?branch=main)](https://github.com/vre-hub/environments/actions/workflows/env-build.yaml)

# Environments

VRE user environment images for workflows and notebooks available in the VRE JupyterHub service.

## VRE user environments

### Custom user environments

If you want to extend or modify any image, find below some suggestions:
 

We strongly recommend that every user enviroment image uses the latests `vre-singleuser-py311` image as a base layer (the `FROM` command in the `Dockerfile` - see below). 

- Check the latest version of the `vre-singleuser-py311` image [here](https://github.com/vre-hub/environments/pkgs/container/vre-singleuser-py311).
- To custimize an image please have a look to the [Startup Docker Stack documentation Hooks](https://jupyter-docker-stacks.readthedocs.io/en/latest/using/common.html#startup-hooks).
 - Create one folder per environments. The directory would need to contain a valid `Dockerfile`. Once your PR is merged, the CI will detect the changes in the repository and will trigger the building of the image.
 - Add a `README.md` file describing the environment and its usage.
 - We strongly recommend to add the following lines to any new user environment (thus in a `Dockerfile`), so that the image would labelled with the building date.
 
```Dockerfile
#  Beginning of the suggested Dockerfile 
FROM ghcr.io/vre-hub/vre-singleuser-py311:sha-5106e39
LABEL maintainer=<your_name>
ARG BUILD_DATE
LABEL org.label-schema.build-date=$BUILD_DATE

...

```

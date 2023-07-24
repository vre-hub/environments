[![Build and publish](https://github.com/vre-hub/environments/actions/workflows/env-build.yaml/badge.svg?branch=main)](https://github.com/vre-hub/environments/actions/workflows/env-build.yaml)

# Environments

VRE related and user environment images for workflows and notebooks.

## VRE user environments

We strongly recommend that every user enviroment image uses the latests `vre-singleuser` image as a base layer (the `FROM` command in the `Dockerfile`).

Within your PR: 
 - Add a folder per environments, the directory needs to contain a valid `Dockerfile`. 
 - Then add the folder name to the matrix array [here](https://github.com/vre-hub/environments/blob/main/.github/workflows/env-build.yaml):


```yaml
jobs:
  build-and-push-image:
    strategy:
      matrix:
        environments: [vre-singleuser, vre-hub, ...] # <-- add folder name here
```

 - We strongly recommend to add the following lines to any new user environment (thus a `Dockerfile`)
 
```Dockerfile
# After the `FROM` and other `LABEL` commands
ARG BUILD_DATE
LABEL org.label-schema.build-date=$BUILD_DATE
```
    - When building the image, the CI of this repository will add a label with the time the image was built.

    
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
        environments: [singleuser, test-image] # <-- add folder name here
```

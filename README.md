[![Build and publish](https://github.com/vre-hub/environments/actions/workflows/env-build.yaml/badge.svg?branch=main)](https://github.com/vre-hub/environments/actions/workflows/env-build.yaml)

# Environments

VRE user environment images for workflows and notebooks.

## Usage

Add folder per user environments, the folder needs to contain a valid `Dockerfile`. Then add the folder name to the matrix array [here](https://github.com/vre-hub/environments/blob/main/.github/workflows/env-build.yaml):

```yaml
jobs:
  build-and-push-image:
    strategy:
      matrix:
        environments: [singleuser, test-image] # <-- add folder name here
```

# itwinai - base-notebook image

To clone a subloder of a repository do
```bash
$ git clone --depth 1 --no-checkout https://github.com/jupyter/docker-stacks
$ cd docker-stacks
# git checkout <BRANCH> -- <SUBDIRECTORY>
$ git checkout main -- images/base-notebook
$ cd ..
$ mv docker-stacks/images/base-notebook/* . # Do not overwrite the README.md
$ rm -rf docker-stacks
```

We adapt the `Dockerfile` with
```Dockerfile
FROM ghcr.io/vre-hub/itwinai-docker-stacks:0.2.2-torch2.1-py3.10
```
build the `ghcr.io/vre-hub/itwinai-base-notebook` image locally, and push
it to the [vre-hub package repository](https://github.com/orgs/vre-hub/packages/container/package/itwinai-base-notebook).
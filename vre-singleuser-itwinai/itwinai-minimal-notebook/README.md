# itwinai - minimal-notebook

To clone a subloder of a repository do
```bash
$ git clone --depth 1 --no-checkout https://github.com/jupyter/docker-stacks
$ cd docker-stacks
# git checkout <BRANCH> -- <SUBDIRECTORY>
$ git checkout main -- images/minimal-notebook
$ cd ..
$ mv docker-stacks/images/minimal-notebook/* . # Do not overwrite the README.md
$ rm -rf docker-stacks
```

We adapt the `Dockerfile` with
```Dockerfile
FROM ghcr.io/vre-hub/itwinai-base-notebook:0.2.2-torch2.1-py3.10 
```
build the `ghcr.io/vre-hub/itwinai-minimal-notebook` image locally, and push
it to the [vre-hub package repository](https://github.com/orgs/vre-hub/packages/container/package/itwinai-minimal-notebook).
# itwinai - Jupyter Docker Foundation Stack image

To clone a subloder of a repository do
```bash
$ git clone --depth 1 --no-checkout https://github.com/jupyter/docker-stacks
$ cd docker-stacks
# git checkout <BRANCH> -- <SUBDIRECTORY>
$ git checkout main -- images/docker-stacks-foundation
$ cd ..
$ mv docker-stacks/images/docker-stacks-foundation/* .
$ rm -rf docker-stacks
```

We adapt the `Dockerfile` with
```Dockerfile
FROM ghcr.io/intertwin-eu/itwinai:0.2.2-torch2.1-root
```
and build the `ghcr.io/vre-hub/itwinai-docker-stacks` image locally and pushed
to the [vre-hub package repository](https://github.com/orgs/vre-hub/packages/container/package/itwinai-docker-stacks) because the 
`ghcr.io/intertwin-eu/itwinai:0.2.2-torch2.1-root` is 22 GB.


#### Upstream version
If the above commands does't work, just go to the docker-stacks [repository](https://github.com/jupyter/docker-stacks/tree/9e230b3b7d2418bd79c94d03bf5f45d2a601865f/images/docker-stacks-foundation) and checkout the commit [e51895b](https://github.com/jupyter/docker-stacks/commit/e51895bcbdbcec97eb52798b952190a30a02707a).
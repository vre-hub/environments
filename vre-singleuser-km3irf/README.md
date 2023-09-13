# km3irf environment

This environment is based on the latest versions of `km3irf 0.3` and `gammapy 1.1` packages.
Build image locally from `Dockerfile`
```sh
docker build -t your_image_tag .
docker run --name cont_km3irf -p 8888:8888 -it your_image_tag
```
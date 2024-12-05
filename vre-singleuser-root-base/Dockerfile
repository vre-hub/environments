# Stage 1: Pull ROOT base image
FROM rootproject/root:6.26.02-ubuntu20.04 as root-base

# Stage 2: Use scipy-notebook for Jupyter environment
FROM jupyter/scipy-notebook:latest as scipy-notebook

# Install rsync
USER root
RUN apt-get update && apt-get install -y rsync

# Copy ROOT installation from the previous stage
COPY --from=root-base /opt/root /opt/root

# Set environment variables for ROOT
ENV ROOTSYS=/opt/root
ENV PATH="$ROOTSYS/bin:$PATH"
ENV LD_LIBRARY_PATH="$ROOTSYS/lib:$LD_LIBRARY_PATH"
ENV PYTHONPATH="$ROOTSYS/lib:$PYTHONPATH"

# Add user convenience: create a workspace directory
WORKDIR /home/jovyan/work

RUN mkdir HiggsTutorial && \
    cd HiggsTutorial && \
    wget https://launchpad.net/mg5amcnlo/3.0/3.6.x/+download/MG5_aMC_v3.6.1.beta.tar.gz && \
    tar -xvzf MG5_aMC_v3.6.1.beta.tar.gz

# Expose Jupyter Notebook on the default port
EXPOSE 8888

# Command to start Jupyter Notebook
CMD ["start-notebook.sh"]
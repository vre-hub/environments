FROM rootproject/root:6.26.02-ubuntu20.04 as root-base

FROM jupyter/scipy-notebook:python-3.9.5

USER root

# Install system dependencies
RUN apt-get update -y && apt-get install -y rsync wget build-essential curl && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Copy ROOT installation
COPY --from=root-base /opt/root /opt/root

# Set ROOT environment variables
ENV ROOTSYS=/opt/root
ENV PATH="$ROOTSYS/bin:$PATH"
ENV LD_LIBRARY_PATH="$ROOTSYS/lib:$LD_LIBRARY_PATH"
ENV PYTHONPATH="$ROOTSYS/lib:$PYTHONPATH"

# Add user convenience workspace
WORKDIR /home/jovyan/work
RUN mkdir HiggsTutorial && chown -R jovyan:users /home/jovyan

USER jovyan

WORKDIR /home/jovyan/work/HiggsTutorial
RUN wget https://launchpad.net/mg5amcnlo/3.0/3.6.x/+download/MG5_aMC_v3.6.1.beta.tar.gz && \
    tar -xvzf MG5_aMC_v3.6.1.beta.tar.gz && rm MG5_aMC_v3.6.1.beta.tar.gz

# Jupyter Notebook setup
ENV JUPYTER_ENABLE_LAB=yes
EXPOSE 8888

CMD ["start-notebook.sh"]

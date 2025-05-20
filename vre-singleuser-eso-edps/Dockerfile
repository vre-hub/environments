#FROM ghcr.io/vre-hub/vre-singleuser-py311:sha-281055c
FROM quay.io/jupyter/scipy-notebook:python-3.11.8
USER root

RUN apt-get update \
    && apt-get install -y build-essential \
    procps \
    curl \
    file \
    git \
    ruby \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

ENV XDG_RUNTIME_DIR=/var/run/adari
RUN mkdir $XDG_RUNTIME_DIR && chmod 777 $XDG_RUNTIME_DIR

# Create user
#RUN useradd -m -d /home/linuxbrew -s /bin/bash linuxbrew
RUN useradd -m -s /bin/bash linuxbrew
USER linuxbrew
ENV HOME=/home/linuxbrew

# Install Homebrew
RUN curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh | bash
ENV PATH="${HOME}/.linuxbrew/bin:${HOME}/.linuxbrew/sbin:${PATH}"

WORKDIR /home/linuxbrew
RUN mkdir .edps EDPS_data

COPY --chown=linuxbrew ./requirements.txt requirements.txt
COPY --chown=linuxbrew ./edps-gui.py edps-gui.py
COPY --chown=linuxbrew ./pdf_handler.py pdf_handler.py
COPY --chown=linuxbrew ./eso-logo.jpg eso-logo.jpg
COPY --chown=linuxbrew ./application.properties .edps/application.properties
COPY --chown=linuxbrew ./logging.yaml .edps/logging.yaml

RUN brew install python@3.11
RUN brew tap eso/pipelines
RUN brew install esopipe-fors

RUN python3.11 -m venv venv && . venv/bin/activate && \
    pip install --no-cache-dir --upgrade -r requirements.txt

ENV VIRTUAL_ENV=/home/linuxbrew/venv
ENV PATH=$VIRTUAL_ENV/bin:$PATH

CMD ["panel", "serve", "edps-gui.py", "--plugins", "pdf_handler", "--address", "0.0.0.0", "--port", "7860",  "--allow-websocket-origin", "*"]
FROM fedora:40

ARG PIPE=fors

RUN dnf install -y dnf-plugins-core && \
    dnf update -y && \
    dnf config-manager -y --add-repo=https://ftp.eso.org/pub/dfs/pipelines/repositories/stable/fedora/esorepo.repo && \
    dnf clean all

# skip networkx extra-dependencies to reduce image size
RUN dnf install -y --setopt=install_weak_deps=False python3-networkx which gzip curl graphviz && \
    dnf clean all

# ESO pipeline (incl. all dependencies like ADARI, EDPS, Python3, ...)
RUN dnf install -y esopipe-${PIPE}-wkf esopipe-${PIPE}-datastatic && \
    dnf clean all

ENV XDG_RUNTIME_DIR=/var/run/adari
RUN mkdir $XDG_RUNTIME_DIR && chmod 777 $XDG_RUNTIME_DIR

# Create user
RUN useradd -m -u 1000 user
USER user

WORKDIR /home/user
RUN mkdir .edps EDPS_data

COPY --chown=user ./requirements.txt requirements.txt
COPY --chown=user ./edps-gui.py edps-gui.py
COPY --chown=user ./pdf_handler.py pdf_handler.py
COPY --chown=user ./eso-logo.jpg eso-logo.jpg
COPY --chown=user ./application.properties .edps/application.properties
COPY --chown=user ./logging.yaml .edps/logging.yaml

RUN python3 -m venv venv && . venv/bin/activate && \
    pip install --no-cache-dir --upgrade -r requirements.txt

RUN curl https://ftp.eso.org/pub/dfs/pipelines/instruments/fors/fors-demo-reflex-1.0.tar.gz | tar -zxf -

ENV VIRTUAL_ENV=/home/user/venv
ENV PATH=$VIRTUAL_ENV/bin:$PATH
ENV EDPSGUI_INPUT_DIR=/home/user/${PIPE}
CMD ["panel", "serve", "edps-gui.py", "--plugins", "pdf_handler", "--address", "0.0.0.0", "--port", "7860",  "--allow-websocket-origin", "*"]

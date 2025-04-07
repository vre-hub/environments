#!/bin/bash

# Author: Danilo Piparo, Enric Tejedor, Pedro Maximino, Diogo Castro 2023
# Copyright CERN
# The environment for Spark is configured here. It allows CERN users to
# connect to spark clusters and use their computational resources
# through SWAN.

if [[ -n $SPARK_CLUSTER_NAME ]]
then
   _log "Configuring Spark";

  LOCAL_IP=`hostname -i`
  echo "$LOCAL_IP $SERVER_HOSTNAME" >> /etc/hosts

  # Enable the extensions in Jupyter global path to avoid having to maintain this information 
  # in the user scratch json file (specially because now we persist this file in the user directory and
  # we don't want to persist the Spark extensions across sessions)
  _log "Globally enabling the Spark extensions"
  # Ensure nb configuration directory is created.
  NBCONFIG=/etc/jupyter/nbconfig/notebook.d
  mkdir -p $NBCONFIG

  jq -n --argjson sparkconnector/extension true \
        --argjson sparkmonitor/extension true \
        '{load_extensions: $ARGS.named}' > $NBCONFIG/spark.json

  IPYTHON_KERNEL_CONFIG=$IPYTHONDIR/profile_default/ipython_kernel_config.py
  sed -i "1s/^/c.InteractiveShellApp.extensions.append('sparkconnector.connector')\n/" \
      $IPYTHON_KERNEL_CONFIG
  sed -i "2s/^/c.InteractiveShellApp.extensions.append('sparkmonitor.kernelextension')\n/" \
      $IPYTHON_KERNEL_CONFIG

  # Source configuration for selected cluster
  SPARKVERSION=spark3  # Spark major version
  HADOOPVERSION='3.3'   # Classpath compatibility for YARN
  source $SPARK_CONFIG_SCRIPT $SPARK_CLUSTER_NAME $HADOOPVERSION $SPARKVERSION

  if [[ $CONNECTOR_BUNDLED_CONFIGS ]]
  then
    ln -s $CONNECTOR_BUNDLED_CONFIGS/bundles.json $JUPYTER_CONFIG_DIR/nbconfig/sparkconnector_bundles.json
    ln -s $CONNECTOR_BUNDLED_CONFIGS/spark_options.json $JUPYTER_CONFIG_DIR/nbconfig/sparkconnector_spark_options.json
  fi
else
  # Disable spark jupyterlab extensions enabled by default if no cluster is selected
  mkdir -p /etc/jupyter/labconfig
  jq -n --argjson @swan-cern/sparkconnector true \
        --argjson jupyterlab_sparkmonitor true \
        '{disabledExtensions: $ARGS.named}' > /etc/jupyter/labconfig/page_config.json
  _log "Skipping Spark configuration";
fi
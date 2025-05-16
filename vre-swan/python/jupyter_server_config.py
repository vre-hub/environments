import os

home = os.environ.get("HOME")
jupyter_path = os.environ.get("JUPYTER_PATH", f"{home}/.local/share/jupyter")

c.NotebookNotary.db_file = f"{jupyter_path}/nbsignatures.db"
c.NotebookNotary.secret_file = f"{jupyter_path}/notebook_secret"

# Configure jupyter lab to start in the HOME of the user
# which is usually EOS for CERN users.
c.ServerApp.root_dir = home

c.ServerApp.contents_manager_class = "swancontents.filemanager.SwanEosFileManager"
# To allow deleting Projects, which are never empty because of .swancontents
c.FileContentsManager.always_delete_dir = True

cernbox_oauth_id = os.environ.get("CERNBOX_OAUTH_ID", "cernbox-service")
eos_oauth_id = os.environ.get("EOS_OAUTH_ID", "eos-service")
oauth2_file = os.environ.get("OAUTH2_FILE", "")
oauth_inspection_endpoint = os.environ.get("OAUTH_INSPECTION_ENDPOINT", "")
c.SwanOauthRenew.files = [
    ("/tmp/swan_oauth.token", "access_token", "{token}"),
    ("/tmp/cernbox_oauth.token", f"exchanged_tokens/{cernbox_oauth_id}", "{token}"),
    (oauth2_file, f"exchanged_tokens/{eos_oauth_id}", "oauth2:{token}:" + oauth_inspection_endpoint)
]

# Toggle JupyterLab based on user preference
use_jupyterlab = os.environ.get('SWAN_USE_JUPYTERLAB', 'false').lower() == 'true'
if use_jupyterlab:
    c.ServerApp.default_url = '/lab'
else:
    c.ServerApp.default_url = '/projects'

user = os.environ.get('USER')
# Change the HOME environment variable to the local user home instead of EOS
# to prevent xelatex from touching EOS during the PDF conversion and so
# reduce the time it takes to convert a PDF (including preventing timeouts).
c.PDFExporter.latex_command = ['env', f'HOME=/home/{user}' , 'xelatex', '-quiet', '{filename}']


# CERN-VRE - Configure the JupyterLab server - TRIGGERED TO ALWAYS WORK
use_rucio_extension = os.environ.get('USE_RUCIO_EXTENSION', 'true').lower() == 'true'
if use_rucio_extension:

    def write_jupyterlab_config():
        dir_config_jupyterlab = os.getenv('JUPYTER_CONFIG_DIR', 
                                        os.path.join(os.getenv('HOME'), '.jupyter')
                                        )
        file_server_config = os.path.join(dir_config_jupyterlab, 'jupyter_server_config.json')

        if not os.path.exists(dir_config_jupyterlab):
            os.makedirs( dir_config_jupyterlab, exist_ok=True)
        elif os.path.isfile(file_server_config) :
            with open(file_server_config, "r") as config_file:
                config_payload = config_file.read()

        try:
            config_json = json.loads(config_payload)
        except:
            config_json = {}

        escape_config = {
            "name": os.getenv('RUCIO_NAME', 'vre-rucio.cern.ch'),
            "display_name": os.getenv('RUCIO_DISPLAY_NAME', 'ESCAPE Rucio instance'),
            "rucio_base_url": os.getenv('RUCIO_BASE_URL', 'https://vre-rucio.cern.ch'),
            "rucio_auth_url": os.getenv('RUCIO_AUTH_URL', 'https://vre-rucio-auth.cern.ch'),
            "rucio_webui_url": os.getenv('RUCIO_WEBUI_URL', 'https://vre-rucio-ui.cern.ch'),
            "rucio_ca_cert": os.getenv('RUCIO_CA_CERT', '/certs/rucio_ca.pem'),
            "site_name": os.getenv('RUCIO_SITE_NAME', 'CERN'),
            "vo": os.getenv('RUCIO_VO', 'escape'),
            "voms_enabled": os.getenv('RUCIO_VOMS_ENABLED', '0') == '1',
            "voms_vomses_path": os.getenv('RUCIO_VOMS_VOMSES_PATH', '/etc/vomses'),
            "voms_certdir_path": os.getenv('RUCIO_VOMS_CERTDIR_PATH',),
            "voms_vomsdir_path": os.getenv('RUCIO_VOMS_VOMSDIR_PATH', '/etc/grid-security/vomsdir'),
            "destination_rse": os.getenv('RUCIO_DESTINATION_RSE', 'CERN-EOSPILOT'),
            "rse_mount_path": os.getenv('RUCIO_RSE_MOUNT_PATH', '/eos/eulake'),
            "replication_rule_lifetime_days": int(os.getenv('RUCIO_REPLICATION_RULE_LIFETIME_DAYS')) if os.getenv('RUCIO_REPLICATION_RULE_LIFETIME_DAYS') else None,
            "path_begins_at": int(os.getenv('RUCIO_PATH_BEGINS_AT', '5')),
            "mode": os.getenv('RUCIO_MODE', 'replica'),
            "wildcard_enabled": os.getenv('RUCIO_WILDCARD_ENABLED', '0') == '1',
            #"oidc_auth": os.getenv('RUCIO_OIDC_AUTH'),
            #"oidc_env_name": os.getenv('RUCIO_OIDC_ENV_NAME'),
            #"oidc_file_name": os.getenv('RUCIO_OIDC_FILE_NAME'),
        }
        atlas_config = {
            "name": os.getenv('ATLAS_RUCIO_NAME', 'https://voatlasrucio-server-prod.cern.ch'),
            "display_name": os.getenv('ATLAS_RUCIO_DISPLAY_NAME', 'ATLAS RUCIO'),
            "rucio_base_url": os.getenv('ATLAS_RUCIO_BASE_URL', 'https://voatlasrucio-server-prod.cern.ch:443'),
            "rucio_auth_url": os.getenv('ATLAS_RUCIO_AUTH_URL', 'https://atlas-rucio-auth.cern.ch:443'),
            "rucio_webui_url": os.getenv('ATLAS_RUCIO_WEBUI_URL', 'https://rucio-ui.cern.ch'),
            "rucio_ca_cert": os.getenv('RUCIO_CA_CERT', '/certs/rucio_ca.pem'),
            "site_name": os.getenv('ATLAS_RUCIO_SITE_NAME', 'CERN'),
            "vo": os.getenv('ATLAS_RUCIO_VO', 'atlas'),
            "voms_enabled": os.getenv('RUCIO_VOMS_ENABLED', '0') == '1',
            "voms_vomses_path": os.getenv('RUCIO_VOMS_VOMSES_PATH', '/etc/vomses'),
            "voms_certdir_path": os.getenv('RUCIO_VOMS_CERTDIR_PATH',),
            "voms_vomsdir_path": os.getenv('RUCIO_VOMS_VOMSDIR_PATH', '/etc/grid-security/vomsdir'),
            "destination_rse": os.getenv('ATLAS_RUCIO_DESTINATION_RSE', 'CERN-PROD_PHYS-TOP'),
            "rse_mount_path": os.getenv('ATLAS_RUCIO_RSE_MOUNT_PATH', '/eos/atlas/atlasscratchdisk/rucio'),
            "replication_rule_lifetime_days": int(os.getenv('ATLAS_RUCIO_REPLICATION_RULE_LIFETIME_DAYS')) if os.getenv('ATLAS_RUCIO_REPLICATION_RULE_LIFETIME_DAYS') else None,
            "path_begins_at": int(os.getenv('ATLAS_RUCIO_PATH_BEGINS_AT', '4')),
            "mode": os.getenv('ATLAS_RUCIO_MODE', 'replica'),
            "wildcard_enabled": os.getenv('ATLAS_RUCIO_WILDCARD_ENABLED', '0') == '1',
        }
        
        # Working atlas config
        # atlas_config = {
        #     "name": "https://voatlasrucio-server-prod.cern.ch",
        #     "display_name": "ATLAS RUCIO",
        #     "rucio_base_url": "https://voatlasrucio-server-prod.cern.ch:443",
        #     "rucio_auth_url": "https://atlas-rucio-auth.cern.ch:443",
        #     "rucio_ca_cert": "/certs/rucio_ca.pem",
        #     "site_name": "CERN",
        #     "vo": "atlas",
        #     "voms_enabled": os.getenv('RUCIO_VOMS_ENABLED', '0') == '1',
        #     "destination_rse": "CERN-PROD_PHYS-TOP",
        #     "rse_mount_path": "/eos/atlas/atlasscratchdisk/rucio",
        #     "path_begins_at": 4,
        #     "mode": "replica", 
        #     "wildcard_enabled": os.getenv('RUCIO_WILDCARD_ENABLED', '0') == '0'
        # }

        escape_config = {k: v for k,
                        v in escape_config.items() if v is not None}

        atlas_config = {k: v for k,
                        v in atlas_config.items() if v is not None}                       

        config_json['RucioConfig'] = {
            'instances': [escape_config, atlas_config], # cms, 
            "default_instance": os.getenv('RUCIO_DEFAULT_INSTANCE', escape_config['name']),
            "default_auth_type": os.getenv('RUCIO_DEFAULT_AUTH_TYPE', 'x509_proxy'),
        }

        config_file = open(file_server_config, 'w')
        config_file.write(json.dumps(config_json, indent=2))
        config_file.close()
        
    write_jupyterlab_config()

else:
    pass
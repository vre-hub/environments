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

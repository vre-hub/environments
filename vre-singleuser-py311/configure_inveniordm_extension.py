import os

# Remote servers offered by the InvenioRDM extension.
#
# Everything here can be overridden at deploy time through environment
# variables, because only the deployment knows its own OAuth applications and,
# in proxy mode, where its proxies live. Per server, with <PREFIX> as below:
#
#   <PREFIX>_OAUTH_CLIENT_ID
#   <PREFIX>_PROXY_URL
#   <PREFIX>_PROXY_SESSION_COOKIE_NAME
#
# The bundled client IDs only work for a JupyterLab on localhost, so any real
# deployment has to set its own.
REMOTE_SERVERS = (
    {
        "id": "zenodo",
        "label": "Zenodo",
        "base_url": "https://zenodo.org",
        "env_prefix": "ZENODO",
        "default_oauth_client_id": "HaWBPRb7lsif7cqTypUNeFni9PJOoTm5IcjTJrtt",
    },
    {
        "id": "cds",
        "label": "CDS",
        "base_url": "https://repository.cern",
        "env_prefix": "CDS",
        "default_oauth_client_id": "q4szrkotZqAuRA6HhGeajJsqTqEd6t6lTHHGLWD4",
    },
    {
        "id": "zenodo_sandbox",
        "label": "Zenodo Sandbox",
        "base_url": "https://sandbox.zenodo.org",
        "env_prefix": "ZENODO_SANDBOX",
        "default_oauth_client_id": "ca8NzRHmqp6tVA0IE9XUlmbL74cGm9RqguC9DZlU",
    },
)

PREFERRED_DEFAULT_SERVER = "zenodo"


def _build_remote_server(server, request_mode):
    """Build one remote server entry, or None if it cannot be used."""
    prefix = server["env_prefix"]
    proxy_url = (os.getenv(prefix + "_PROXY_URL") or "").strip().rstrip("/")

    # In proxy mode the extension requires proxy_url and
    # proxy_session_cookie_name on *every* configured server -
    # validate_proxy_configuration() raises otherwise and the server extension
    # then fails to load. Drop a server with no proxy instead of taking the
    # whole extension down with it.
    if request_mode == "proxy" and not proxy_url:
        return None

    entry = {
        "label": server["label"],
        "base_url": server["base_url"],
        "oauth_client_id": (
            os.getenv(prefix + "_OAUTH_CLIENT_ID")
            or server["default_oauth_client_id"]
        ),
    }

    if proxy_url:
        entry["proxy_url"] = proxy_url
        # Must be unique per proxy: the OAuth state cookie is derived from it
        # as "<name>_oauth_state", so two proxies sharing a name clobber each
        # other's login flows.
        entry["proxy_session_cookie_name"] = (
            os.getenv(prefix + "_PROXY_SESSION_COOKIE_NAME")
            or server["id"] + "_proxy_session"
        )

    return entry


def configure_inveniordm_extension(config: dict):
    """
    Update the jupyter server configuration with settings for the InvenioRDM extension.
    """
    request_mode = (os.getenv("INVENIORDM_REQUEST_MODE") or "local").strip().lower()
    if request_mode not in ("local", "proxy"):
        request_mode = "local"

    remote_servers = {}
    for server in REMOTE_SERVERS:
        entry = _build_remote_server(server, request_mode)
        if entry is not None:
            remote_servers[server["id"]] = entry

    # Proxy mode with no proxy configured anywhere would leave an empty
    # registry, which the extension rejects outright. Fall back to local mode
    # so browsing still works instead of losing the extension entirely.
    if not remote_servers:
        request_mode = "local"
        for server in REMOTE_SERVERS:
            remote_servers[server["id"]] = _build_remote_server(server, "local")

    default_remote_server = (
        PREFERRED_DEFAULT_SERVER
        if PREFERRED_DEFAULT_SERVER in remote_servers
        else next(iter(remote_servers))
    )

    config["InvenioRDMJupyterLab"] = {
        "request_mode": request_mode,
        "default_remote_server": default_remote_server,
        "remote_servers": remote_servers,
    }

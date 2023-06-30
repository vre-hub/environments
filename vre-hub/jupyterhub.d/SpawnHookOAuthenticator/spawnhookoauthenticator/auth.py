from jupyterhub.utils import maybe_future
from oauthenticator.generic import GenericOAuthenticator
from traitlets import Unicode, Bool, List, Any, TraitError, default, validate


class SpawnHookOAuthenticator(GenericOAuthenticator):
    pre_spawn_hook = Any(
        allow_none=True,
        config=True,
        help="""
        Callable to execute before spawning a session. Usefull to inject extra variables, like the oauth tokens
        Example::
            def pre_spawn_hook(authenticator, spawner, auth_state):
                spawner.environment['ACCESS_TOKEN'] = auth_state['exchanged_tokens']['eos-service']
            c.OIDCAuthenticator.pre_spawn_hook = pre_spawn_hook
        """
    )

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        # Force auth state so that we can store the tokens in the user dict
        self.enable_auth_state = True

    @validate('pre_spawn_hook')
    def _validate_pre_spawn_hook(self, proposal):
        value = proposal['value']
        if not callable(value):
            raise TraitError("pre_spawn_hook must be callable")
        return value

    async def pre_spawn_start(self, user, spawner):
        if self.pre_spawn_hook:
            auth_state = await user.get_auth_state()
            await maybe_future(self.pre_spawn_hook(self, spawner, auth_state))

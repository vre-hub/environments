# Useful functions to run in the build or startup

run_as_user() {
    if [ "$(whoami)" = "$NB_USER" ]; then
        eval "$@"
    else
        local cmd="$@"
        sudo -E -u $NB_USER sh -c "$cmd"
    fi
}
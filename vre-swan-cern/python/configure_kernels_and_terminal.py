"""
Writes kernel.json and terminal .bash_profile environment variables
from the current process environment
"""

import json
import logging
import os
import re
import shutil

SWAN_ENV_FILE = os.environ["SWAN_ENV_FILE"]
KERNEL_DIR = os.environ["KERNEL_DIR"]
HOME = os.environ["HOME"]
PYTHONEXECPATH = shutil.which(f"python3")


def modify_python_argv(kernel_json):
    """Make sure that `python` points to the correct binary from CVMFS"""
    if re.match(r"python[0-9.]*", kernel_json["argv"][0]):
        kernel_json["argv"][0] = PYTHONEXECPATH


def configure_kernels():
    """Writes kernel.json with env and argv from software stack"""
    kernel_json_file_names = [
        f"{KERNEL_DIR}/{kernel_name}/kernel.json"
        for kernel_name in os.listdir(KERNEL_DIR)
    ]
    for kernel_json_file in kernel_json_file_names:
        kernel_json = None
        with open(kernel_json_file, "r") as file:
            kernel_json = json.loads(file.read())

        kernel_json["env"] = kernel_json.get("env", {}) | dict(os.environ)
        modify_python_argv(kernel_json)
        with open(kernel_json_file, "w") as file:
            file.write(json.dumps(kernel_json, indent=4))


def configure_terminal():
    """Writes bash profile with environment from software stack"""
    with open(SWAN_ENV_FILE, "w") as terminal_environment_file:
        for key, val in dict(os.environ).items():
            if key == "SUDO_COMMAND":
                continue
            if key == "TERM": # prevent TERM=unknown from being injected in the env
                continue
            if key == "PYTHONPATH":
                val = re.sub("/usr/local/lib/swan/(extensions/)?:", "", val)
            terminal_environment_file.write(f'export {key}="{val}"\n')

        terminal_environment_file.writelines(
            [
                f'alias python="{PYTHONEXECPATH}"\n',
                # Setting up colors
                "alias ls='ls --color'\n",
                "alias grep='grep --color'\n",
                # There's no JupyterLab setting for the terminal directory, so we
                # set it here to always be HOME
                f"cd {HOME}\n"
            ]
        )


if __name__ == "__main__":
    logging.basicConfig(
        format="[%(levelname)s %(asctime)s.%(msecs)03d %(filename)s:%(lineno)d] %(message)s",
        level=logging.INFO,
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    logging.info("Configuring kernelspecs and terminal profiles")
    configure_terminal()
    configure_kernels()

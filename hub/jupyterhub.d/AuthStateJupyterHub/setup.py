import os

from jupyter_packaging import get_version
import setuptools

name="authstatejupyterhub"

# Get our version
version = get_version(os.path.join(name, "_version.py"))

setup_args = dict(
    name=name,
    version=version,
    packages=setuptools.find_packages(),
    install_requires=[
          'jupyterhub==1.1.*'
    ],
    zip_safe=False,
    include_package_data=True,
    license="AGPL-3.0",
    platforms="Linux, Mac OS X",
    entry_points={
        'console_scripts': [
            'authstatejupyterhub = authstatejupyterhub.app:main',
        ],
    },
    classifiers=[
        "License :: OSI Approved :: GNU Affero General Public License v3",
        'Intended Audience :: Developers',
        'Intended Audience :: System Administrators',
        'Intended Audience :: Science/Research',
        'Programming Language :: Python',
        'Programming Language :: Python :: 3',
    ],
)


if __name__ == "__main__":
    setuptools.setup(**setup_args)
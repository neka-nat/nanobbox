import sys

try:
    from skbuild import setup
    import nanobind
except ImportError:
    print("The preferred way to invoke 'setup.py' is via pip, as in 'pip "
          "install .'. If you wish to run the setup script directly, you must "
          "first install the build dependencies listed in pyproject.toml!",
          file=sys.stderr)
    raise

setup(
    name="nanobbox",
    version="0.3.0",
    author="neka-nat",
    author_email="nekanat.stock@gmail.com",
    description="A bbox project that compiles bindings using nanobind and scikit-build",
    url="https://github.com/neka-nat/nanobbox",
    license="MIT",
    packages=['nanobbox'],
    package_dir={'': 'src'},
    cmake_install_dir="src/nanobbox",
    include_package_data=True,
    python_requires=">=3.8"
)
===========
Fingerboard
===========

    | A fprintd_ based fingerprint GUI for Linux

Fingerboard is a fingerprint GUI to enroll, list, delete and verify fingerprints.
Fingerboard is a GUI interface to fprint, and uses the D-Bus interfaces to communicate with fprint.

Building
--------
The project uses CMake build system. Follow the steps below to build, compile and install this project.

Dependencies - Ubuntu
^^^^^^^^^^^^^^^^^^^^^
Note: Requires ``universe`` repository to be enabled for qt dependencies.

.. code-block:: bash

  apt install \
    gcc \
    g++ \
    make \
    cmake \
    extra-cmake-modules \
    qtbase5-dev \
    qtdeclarative5-dev \
    qtquickcontrols2-5-dev \
    libqt5svg5-dev \
    qml-module-qtquick-controls \
    qml-module-qtquick-controls2 \
    qml-module-qtgraphicaleffects \
    qml-module-qtquick-layouts

Dependencies - Arch
^^^^^^^^^^^^^^^^^^^
   
.. code-block:: bash

  pacman -S \
    gcc \
    make \
    cmake \
    extra-cmake-modules \
    qt5-base \
    qt5-graphicaleffects \
    qt5-svg \
    qt5-quickcontrols \
    qt5-quickcontrols2

Build and compile
^^^^^^^^^^^^^^^^^
    
.. code-block:: bash

  # Make a build directory and cd into it
  mkdir build && cd build

  # Run cmake
  cmake .. -DCMAKE_INSTALL_PREFIX=/usr

  # Build the project
  make -j$(nproc)

  # [OPTIONAL] Install to system (requires root access)
  sudo make install

Hacking
-------
#. Any kind of contribution is appreciated
#. Format the cpp sources and headers with ``clang-format -i -style=file <cpp source or header>``
#. Properly indent qml source

.. References
.. ----------
.. _fprintd: https://fprint.freedesktop.org/
.. _HACKING.rst: HACKING.rst

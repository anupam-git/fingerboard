===========
Fingerboard
===========

    | A fprintd_ based fingerprint GUI for Linux

Fingerboard is a fingerprint GUI to enroll/list/delete fingerprints.
Fingerboard is an GUI interface to fprint, and used the D-Bus interfaces to communicate with fprint.

Building
--------
The project uses CMake to build the project. Follow the steps below to build and install this project.
   
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
#. Read the instructions in HACKING.rst_ guide before commiting
#. It is recommended to create an issue and discuss before making any Pull Requests otherwise the Pull Request
   may not be merged

.. References
.. ----------
.. _fprintd: https://fprint.freedesktop.org/
.. _HACKING.rst: HACKING.rst

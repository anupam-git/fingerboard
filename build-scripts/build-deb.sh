#!/bin/bash

set -ex
SCRIPTPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

(
  mkdir -p $SCRIPTPATH/build
  cd $SCRIPTPATH/build
  
  cmake $SCRIPTPATH/.. -DCMAKE_INSTALL_PREFIX=/usr
  make -j$(nproc)

  make -j$(nproc) package

  rm -rf $SCRIPTPATH/build
)
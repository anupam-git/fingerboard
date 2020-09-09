#!/bin/bash

set -ex
SCRIPTPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

(
  mkdir -p $SCRIPTPATH/build
  
  pushd $SCRIPTPATH/build  
    cmake $SCRIPTPATH/.. -DCMAKE_INSTALL_PREFIX=/usr
    make -j$(nproc)

    make -j$(nproc) package
    
    source /etc/lsb-release
    version=$(basename fingerboard*.deb | grep -Po '\d*\.\d*\.\d*')
    arch=$(arch)
    
    mv fingerboard*.deb "${SCRIPTPATH}/fingerboard-${version}-$(echo ${DISTRIB_ID} | tr '[:upper:]' '[:lower:]')_${DISTRIB_CODENAME}-${arch}.deb"
  popd
  
  rm -rf $SCRIPTPATH/build
)

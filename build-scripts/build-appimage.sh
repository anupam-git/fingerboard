#!/bin/bash

set -ex
SCRIPTPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

(
  mkdir -p $SCRIPTPATH/build-appimage
  
  pushd $SCRIPTPATH/build-appimage
    cmake $SCRIPTPATH/.. -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=RelWithDebInfo
    make -j$(nproc)
    DESTDIR=$SCRIPTPATH/AppDir make install
    
    mkdir -p $SCRIPTPATH/AppDir/usr/include/x86_64-linux-gnu/
    cp -r /usr/include/x86_64-linux-gnu/qt5/ $SCRIPTPATH/AppDir/usr/include/x86_64-linux-gnu/
  popd
  
  export APP_VERSION=$(cat $SCRIPTPATH/../CMakeLists.txt | grep -Po '(?<=FINGERBOARD_VERSION )\d*.\d*.\d*')
  appimage-builder --skip-tests

  rm -rf $SCRIPTPATH/build-appimage
  rm -rf $SCRIPTPATH/AppDir
)

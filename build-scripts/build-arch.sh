#!/bin/bash

set -ex
SCRIPTPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

(
  cd $SCRIPTPATH
  makepkg -f --skipinteg
  rm -rf $SCRIPTPATH/pkg $SCRIPTPATH/src
)
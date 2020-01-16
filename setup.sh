#!/usr/bin/env bash

#export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
#source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh
#lsetup "root 6.14.04-x86_64-slc6-gcc62-opt"
#lsetup "cmake 3.11.0"

export WORKDIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" >/dev/null 2>&1 && pwd  )"
export PATH=${WORKDIR}/build:${PATH}

function compile(){
    CURRENTDIR=${PWD}
    cd ${WORKDIR}/build
    make
    cd ${CURRENTDIR}
}


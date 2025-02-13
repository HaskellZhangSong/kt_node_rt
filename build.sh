#!/bin/bash

PLATFORM=$(uname)

if [[ ${PLATFORM} == 'Darwin' ]]; then
    ENABLE=ENABLE_MACOS
elif [[ ${PLATFORM} == 'Linux' ]]; then
    ENABLE=ENABLE_LINUX
fi

echo building for ${ENABLE}

set -e
pushd . > /dev/null
PROJECT_DIR=$(cd $(dirname "${BASH_SOURCE[0]})" > /dev/null 2>&1 && pwd -P))
echo $PROJECT_DIR
echo "cmake ${ENABLE}=ON -S . -B build"
cmake -D${ENABLE}=ON -S . -B build
cd build
make

popd > /dev/null
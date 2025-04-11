#!/bin/bash
set -e
pushd . > /dev/null
PLATFORM=$(uname | tr '[:upper:]' '[:lower:]')
if [[ ${PLATFORM} == 'darwin' ]]; then
    ENABLE=ENABLE_MACOS
elif [[ ${PLATFORM} == 'linux' ]]; then
    ENABLE=ENABLE_LINUX
fi
ARCH=$(uname -m)

echo building for ${ENABLE}
LOCAL_BUILD_PATH=build/${ARCH}-${PLATFORM}

PROJECT_DIR=$(dirname "${BASH_SOURCE[0]})" > /dev/null 2>&1 && pwd -P)

echo "cmake ${ENABLE}=ON -S . -B build"
cmake -D${ENABLE}=ON -S . -B ${LOCAL_BUILD_PATH}
cd ${LOCAL_BUILD_PATH}
make


cd ${PROJECT_DIR}

ohos_sdk_native_dir=${OHOS_SDK_HOME}/sdk/default/openharmony/native/
build_path=build/aarch64-linux-ohos
$ohos_sdk_native_dir/build-tools/cmake/bin/cmake \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_TOOLCHAIN_FILE=$ohos_sdk_native_dir/build/cmake/ohos.toolchain.cmake \
    -DCMAKE_MAKE_PROGRAM=$ohos_sdk_native_dir/build-tools/cmake/bin/ninja \
    -DCMAKE_SYSTEM_NAME=OHOS \
    -DOHOS_ARCH=arm64-v8a \
    -GNinja \
    -DENABLE_OHOS=ON \
    -B ${build_path}
ninja -C ${build_path}
popd > /dev/null

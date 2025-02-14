#!/bin/bash
set -e
pushd . > /dev/null

ohos_sdk_native_dir=/Applications/DevEco-Studio.app/Contents/sdk/default/openharmony/native/
build_path=build_ohos
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
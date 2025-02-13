#pragma once
#if KONAN_OHOS
#include <napi/native_api.h>
#include "hilog/log.h"
#elif KONAN_LINUX || KONAN_MACOSX
#include <node/node_api.h>
#endif
struct ObjHeader;
typedef const ObjHeader* KConstRef;
extern "C" {
ObjHeader* CreateStringFromArkTsString(napi_env env, napi_value jsstr, ObjHeader** __result__);
napi_value CreateArkTsStringFromString(napi_env env, KConstRef kref);
}

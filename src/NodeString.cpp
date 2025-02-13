/*
 * Copyright 2010-2017 JetBrains s.r.o.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdio>
#include <cstdlib>
#include <limits>
#include <string.h>
#include <string>

#include "KAssert.h"
#include "Exceptions.h"
#include "Memory.h"
#include "Natives.h"
#include "KString.h"
#include "Porting.h"
#include "Types.h"

#include "utf8.h"

#include "polyhash/PolyHash.h"

using namespace kotlin;

extern "C" {
#if KONAN_OHOS || KONAN_LINUX || KONAN_MACOSX
OBJ_GETTER(CreateStringFromArkTsString, napi_env env, napi_value jsstr) {
  size_t len;
  napi_status st = napi_get_value_string_utf16(env, jsstr, NULL, 0, &len);
  RuntimeAssert(st == napi_ok, "must be a js string");
  ArrayHeader* result = AllocArrayInstance(theStringTypeInfo, len + 1, OBJ_RESULT)->array();
  KChar* rawResult = CharArrayAddressOfElementAt(result, 0);
  napi_get_value_string_utf16(env, jsstr, (char16_t*)rawResult, len + 1, NULL);
  result->count_ -= 1;
  RETURN_OBJ(result->obj());
}

napi_value CreateArkTsStringFromString(napi_env env, KConstRef kref) {
  if (kref == nullptr) return nullptr;
    std::string utf8 = to_string(kref->array());
  // char* result = reinterpret_cast<char*>(std::calloc(1, utf8.size() + 1));
  napi_value result_js_string;
  napi_create_string_utf8(env, utf8.c_str(), utf8.size(), &result_js_string);
  return result_js_string;
}
#endif
}
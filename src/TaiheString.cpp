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

#include "core/string.hpp"

#include "utf8.h"

#include "polyhash/PolyHash.h"

using namespace kotlin;

namespace {
typedef KChar* utf8to16(const char*, const char*, KChar*);

template<utf8to16 conversion>
OBJ_GETTER(utf8ToUtf16Impl, const char* rawString, const char* end, uint32_t charCount) {
  if (rawString == nullptr) RETURN_OBJ(nullptr);
  ArrayHeader* result = AllocArrayInstance(theStringTypeInfo, charCount, OBJ_RESULT)->array();
  KChar* rawResult = CharArrayAddressOfElementAt(result, 0);
  conversion(rawString, end, rawResult);
  RETURN_OBJ(result->obj());
}

OBJ_GETTER(utf8ToUtf16, const char* rawString, size_t rawStringLength) {
  const char* end = rawString + rawStringLength;
  uint32_t charCount = utf8::with_replacement::utf16_length(rawString, end);
  RETURN_RESULT_OF(utf8ToUtf16Impl<utf8::with_replacement::utf8to16>, rawString, end, charCount);
}

}

#ifdef __cplusplus
extern "C" {
#endif

OBJ_GETTER(CreateStringFromTHString, ::taihe::core::string_view thstring) {
    const char* cstring = thstring.c_str();
    RETURN_RESULT_OF(utf8ToUtf16, cstring, cstring ? strlen(cstring) : 0);
}

::taihe::core::string CreateTHStringFromString(KConstRef kref) {
    if (kref == nullptr) return nullptr;
      std::string utf8 = to_string(kref->array());
    TString tstr;
    tstr_initialize(&tstr, utf8.size() + 1);
    ::memcpy((void*)tstr.ptr, utf8.c_str(), utf8.size());
    return ::taihe::core::string(tstr);
}

#ifdef __cplusplus
}
#endif
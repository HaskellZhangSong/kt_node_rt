#pragma once
#include "core/string.hpp"
struct ObjHeader;
typedef const ObjHeader* KConstRef;

#ifdef __cplusplus
extern "C" {
#endif

ObjHeader* CreateStringFromTHString(::taihe::core::string_view thstr, ObjHeader** __result__);
::taihe::core::string CreateTHStringFromString(KConstRef kref);

#ifdef __cplusplus
}
#endif
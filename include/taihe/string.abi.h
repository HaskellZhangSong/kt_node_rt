#pragma once
#include <stddef.h>
#include <stdint.h>

#include "common.h"

/////////////////////////////////////////
// Private ABI: Don't use in your code //
/////////////////////////////////////////

enum TStringFlags {
  TSTRING_REF = 1,
};

struct TString {
  uint32_t flags;
  uint32_t length;
  char const* ptr;  // Always valid and non-null.
};

struct TStringData {
  TRefCount count;
  char buffer[];
};

//////////////////
// Public C API //
//////////////////

TH_INLINE const char* tstr_buf(struct TString tstr) {
  return tstr.ptr;
}

TH_INLINE size_t tstr_len(struct TString tstr) {
  return tstr.length;
}

TH_INLINE struct TString tstr_new_ref(const char* buf TH_NONNULL, size_t len) {
  struct TString tstr;
  tstr.flags = TSTRING_REF;
  tstr.length = len;
  tstr.ptr = buf;
  return tstr;
}

TH_EXPORT char *tstr_initialize(struct TString *tstr_ptr, uint32_t capacity);

TH_EXPORT struct TString tstr_new(const char* buf TH_NONNULL, size_t len);

TH_EXPORT void tstr_drop(struct TString tstr);


TH_EXPORT struct TString tstr_dup(struct TString tstr);

TH_EXPORT struct TString tstr_concat(struct TString left, struct TString right);

TH_EXPORT struct TString tstr_substr(struct TString tstr, size_t pos, size_t len);

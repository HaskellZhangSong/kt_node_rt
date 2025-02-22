#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define TH_NONNULL __attribute__((nonnull))

#define TH_ASSERT(condition, message)                               \
    do {                                                            \
        if (!(condition)) {                                         \
            fprintf(stderr, "Assertion failed: (%s), function %s, " \
                            "file %s, line %d.\n"                   \
                            "Message: %s\n",                        \
                    #condition, __FUNCTION__, __FILE__, __LINE__,   \
                    message);                                       \
            abort();                                                \
        }                                                           \
    } while (0)

#ifdef __cplusplus
#define TH_EXPORT extern "C" __attribute__((visibility("default")))
#else
#define TH_EXPORT extern __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
#define TH_INLINE inline
#else
#define TH_INLINE static inline
#endif

#ifdef __cplusplus
#define TH_TYPEOF decltype
#else
#define TH_TYPEOF typeof
#endif

#ifdef __cplusplus
#define TH_STATIC_ASSERT static_assert
#else
#include <assert.h>
#define TH_STATIC_ASSERT static_assert
#endif

#ifdef __cplusplus
#include <type_traits>
#define TH_IS_SAME(...) std::is_same<__VA_ARGS__>::value
#else
#define TH_IS_SAME __builtin_types_compatible_p
#endif

////////////////////////
// REFERENCE COUNTING //
////////////////////////

typedef uint32_t TRefCount;

// Sets the counter to a fixed value.
TH_INLINE void tref_set(TRefCount *c, TRefCount i) {
  __atomic_store_n(c, i, __ATOMIC_SEQ_CST);
}

// Increments the refcount and returns the *original* value before add.
TH_INLINE TRefCount tref_inc(TRefCount *c) {
  return __atomic_fetch_add(c, 1, __ATOMIC_SEQ_CST);
}

// Decrements the refcount and returns whether the memory should be freed.
TH_INLINE int tref_dec(TRefCount *c) {
  return __atomic_sub_fetch(c, 1, __ATOMIC_SEQ_CST) == 0;
}

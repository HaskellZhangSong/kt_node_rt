#ifndef RUNTIME_BOXING_H
#define RUNTIME_BOXING_H
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
typedef bool            KBoolean;
#else
typedef _Bool            KBoolean;
#endif
typedef unsigned short     KChar;
typedef signed char        KByte;
typedef short              KShort;
typedef int                KInt;
typedef long long          KLong;
typedef unsigned char      KUByte;
typedef unsigned short     KUShort;
typedef unsigned int       KUInt;
typedef unsigned long long KULong;
typedef float              KFloat;
typedef double             KDouble;
typedef float __attribute__ ((__vector_size__ (16))) KVector128;
typedef void*              KNativePtr;
struct KType;
typedef struct KType KType;

typedef struct {
KNativePtr pinned;
} Kref_kotlin_Byte;
typedef struct {
KNativePtr pinned;
} Kref_kotlin_Short;
typedef struct {
KNativePtr pinned;
} Kref_kotlin_Int;
typedef struct {
KNativePtr pinned;
} Kref_kotlin_Long;
typedef struct {
KNativePtr pinned;
} Kref_kotlin_Float;
typedef struct {
KNativePtr pinned;
} Kref_kotlin_Double;
typedef struct {
KNativePtr pinned;
} Kref_kotlin_Char;
typedef struct {
KNativePtr pinned;
} Kref_kotlin_Boolean;
typedef struct {
    KNativePtr pinned;
} Kref_kotlin_Unit;
typedef struct {
    KNativePtr pinned;
} Kref_kotlin_UByte;
typedef struct {
    KNativePtr pinned;
} Kref_kotlin_UShort;
typedef struct {
    KNativePtr pinned;
} Kref_kotlin_UInt;
typedef struct {
    KNativePtr pinned;
} Kref_kotlin_ULong;
typedef struct {
    KNativePtr pinned;
} Kref_kotlin_Any;

typedef struct {
  /* Service functions. */
  void (*DisposeStablePointer)(KNativePtr ptr);
  void (*DisposeString)(const char* string);
  KBoolean (*IsInstance)(KNativePtr ref, const KType* type);
  Kref_kotlin_Byte (*createNullableByte)(KByte);
  KByte (*getNonNullValueOfByte)(Kref_kotlin_Byte);
  Kref_kotlin_Short (*createNullableShort)(KShort);
  KShort (*getNonNullValueOfShort)(Kref_kotlin_Short);
  Kref_kotlin_Int (*createNullableInt)(KInt);
  KInt (*getNonNullValueOfInt)(Kref_kotlin_Int);
  Kref_kotlin_Long (*createNullableLong)(KLong);
  KLong (*getNonNullValueOfLong)(Kref_kotlin_Long);
  Kref_kotlin_Float (*createNullableFloat)(KFloat);
  KFloat (*getNonNullValueOfFloat)(Kref_kotlin_Float);
  Kref_kotlin_Double (*createNullableDouble)(KDouble);
  KDouble (*getNonNullValueOfDouble)(Kref_kotlin_Double);
  Kref_kotlin_Char (*createNullableChar)(KChar);
  KChar (*getNonNullValueOfChar)(Kref_kotlin_Char);
  Kref_kotlin_Boolean (*createNullableBoolean)(KBoolean);
  KBoolean (*getNonNullValueOfBoolean)(Kref_kotlin_Boolean);
  Kref_kotlin_Unit (*createNullableUnit)(void);
  Kref_kotlin_UByte (*createNullableUByte)(KUByte);
  KUByte (*getNonNullValueOfUByte)(Kref_kotlin_UByte);
  Kref_kotlin_UShort (*createNullableUShort)(KUShort);
  KUShort (*getNonNullValueOfUShort)(Kref_kotlin_UShort);
  Kref_kotlin_UInt (*createNullableUInt)(KUInt);
  KUInt (*getNonNullValueOfUInt)(Kref_kotlin_UInt);
  Kref_kotlin_ULong (*createNullableULong)(KULong);
  KULong (*getNonNullValueOfULong)(Kref_kotlin_ULong);

} RuntimeBoxingExportedSymbols;

#ifdef __cplusplus
}  /* extern "C" */
#endif
#endif  /* RUNTIME_BOXING_H */

struct KObjHeader;
typedef struct KObjHeader KObjHeader;
struct KTypeInfo;
typedef struct KTypeInfo KTypeInfo;

struct FrameOverlay;
typedef struct FrameOverlay FrameOverlay;

#define RUNTIME_NOTHROW __attribute__((nothrow))

#if __has_attribute(retain)
#define RUNTIME_EXPORT __attribute__((used,retain))
#else
#define RUNTIME_EXPORT __attribute__((used))
#endif

#define RUNTIME_NORETURN __attribute__((noreturn))

extern "C" {
void UpdateStackRef(KObjHeader**, const KObjHeader*) RUNTIME_NOTHROW;
KObjHeader* AllocInstance(const KTypeInfo*, KObjHeader**) RUNTIME_NOTHROW;
KObjHeader* DerefStablePointer(void*, KObjHeader**) RUNTIME_NOTHROW;
void* CreateStablePointer(KObjHeader*) RUNTIME_NOTHROW;
void DisposeStablePointer(void*) RUNTIME_NOTHROW;
KBoolean IsInstanceInternal(const KObjHeader*, const KTypeInfo*) RUNTIME_NOTHROW;
void EnterFrame(KObjHeader** start, int parameters, int count) RUNTIME_NOTHROW;
void LeaveFrame(KObjHeader** start, int parameters, int count) RUNTIME_NOTHROW;
void SetCurrentFrame(KObjHeader** start) RUNTIME_NOTHROW;
FrameOverlay* getCurrentFrame() RUNTIME_NOTHROW;
void Kotlin_initRuntimeIfNeeded();
void Kotlin_mm_switchThreadStateRunnable() RUNTIME_NOTHROW;
void Kotlin_mm_switchThreadStateNative() RUNTIME_NOTHROW;
void HandleCurrentExceptionWhenLeavingKotlinCode();

void DisposeCString(char* cstring);
}  // extern "C"

struct lib_FrameOverlay {
  lib_FrameOverlay* previous;
  int parameters;
  int count;
};

class KObjHolder {
public:
  KObjHolder() : obj_(nullptr) {
    EnterFrame(frame(), 0, sizeof(*this)/sizeof(void*));
  }
  explicit KObjHolder(const KObjHeader* obj) : obj_(nullptr) {
    EnterFrame(frame(), 0, sizeof(*this)/sizeof(void*));
    UpdateStackRef(&obj_, obj);
  }
  ~KObjHolder() {
    LeaveFrame(frame(), 0, sizeof(*this)/sizeof(void*));
  }
  KObjHeader* obj() { return obj_; }
  KObjHeader** slot() { return &obj_; }
  private:
  lib_FrameOverlay frame_;
  KObjHeader* obj_;

  KObjHeader** frame() { return reinterpret_cast<KObjHeader**>(&frame_); }
};

class ScopedRunnableState {
public:
  ScopedRunnableState() noexcept { Kotlin_mm_switchThreadStateRunnable(); }
  ~ScopedRunnableState() { Kotlin_mm_switchThreadStateNative(); }
  ScopedRunnableState(const ScopedRunnableState&) = delete;
  ScopedRunnableState(ScopedRunnableState&&) = delete;
  ScopedRunnableState& operator=(const ScopedRunnableState&) = delete;
  ScopedRunnableState& operator=(ScopedRunnableState&&) = delete;
};

static void DisposeStablePointerImpl(KNativePtr ptr) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  DisposeStablePointer(ptr);
}

static void DisposeStringImpl(const char* ptr) {
  DisposeCString((char*)ptr);
}

static KBoolean IsInstanceImpl(KNativePtr ref, const KType* type) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder holder;
  return IsInstanceInternal(DerefStablePointer(ref, holder.slot()), (const KTypeInfo*)type);
}
extern "C" KObjHeader* Kotlin_boxByte(KByte value, KObjHeader**);
static Kref_kotlin_Byte createNullableByteImpl(KByte value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder result_holder;
  KObjHeader* result = Kotlin_boxByte(value,  result_holder.slot());
  return Kref_kotlin_Byte { .pinned = CreateStablePointer(result) };
}
extern "C" KByte Kotlin_unboxByte(KObjHeader*);
static KByte getNonNullValueOfByteImpl(Kref_kotlin_Byte value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder value_holder;
  return Kotlin_unboxByte(DerefStablePointer(value.pinned, value_holder.slot()));
}
extern "C" KObjHeader* Kotlin_boxShort(KShort value, KObjHeader**);
static Kref_kotlin_Short createNullableShortImpl(KShort value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder result_holder;
  KObjHeader* result = Kotlin_boxShort(value,  result_holder.slot());
  return Kref_kotlin_Short { .pinned = CreateStablePointer(result) };
}
extern "C" KShort Kotlin_unboxShort(KObjHeader*);
static KShort getNonNullValueOfShortImpl(Kref_kotlin_Short value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder value_holder;
  return Kotlin_unboxShort(DerefStablePointer(value.pinned, value_holder.slot()));
}
extern "C" KObjHeader* Kotlin_boxInt(KInt value, KObjHeader**);
static Kref_kotlin_Int createNullableIntImpl(KInt value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder result_holder;
  KObjHeader* result = Kotlin_boxInt(value,  result_holder.slot());
  return Kref_kotlin_Int { .pinned = CreateStablePointer(result) };
}
extern "C" KInt Kotlin_unboxInt(KObjHeader*);
static KInt getNonNullValueOfIntImpl(Kref_kotlin_Int value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder value_holder;
  return Kotlin_unboxInt(DerefStablePointer(value.pinned, value_holder.slot()));
}
extern "C" KObjHeader* Kotlin_boxLong(KLong value, KObjHeader**);
static Kref_kotlin_Long createNullableLongImpl(KLong value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder result_holder;
  KObjHeader* result = Kotlin_boxLong(value,  result_holder.slot());
  return Kref_kotlin_Long { .pinned = CreateStablePointer(result) };
}
extern "C" KLong Kotlin_unboxLong(KObjHeader*);
static KLong getNonNullValueOfLongImpl(Kref_kotlin_Long value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder value_holder;
  return Kotlin_unboxLong(DerefStablePointer(value.pinned, value_holder.slot()));
}
extern "C" KObjHeader* Kotlin_boxFloat(KFloat value, KObjHeader**);
static Kref_kotlin_Float createNullableFloatImpl(KFloat value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder result_holder;
  KObjHeader* result = Kotlin_boxFloat(value,  result_holder.slot());
  return Kref_kotlin_Float { .pinned = CreateStablePointer(result) };
}
extern "C" KFloat Kotlin_unboxFloat(KObjHeader*);
static KFloat getNonNullValueOfFloatImpl(Kref_kotlin_Float value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder value_holder;
  return Kotlin_unboxFloat(DerefStablePointer(value.pinned, value_holder.slot()));
}
extern "C" KObjHeader* Kotlin_boxDouble(KDouble value, KObjHeader**);
static Kref_kotlin_Double createNullableDoubleImpl(KDouble value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder result_holder;
  KObjHeader* result = Kotlin_boxDouble(value,  result_holder.slot());
  return Kref_kotlin_Double { .pinned = CreateStablePointer(result) };
}
extern "C" KDouble Kotlin_unboxDouble(KObjHeader*);
static KDouble getNonNullValueOfDoubleImpl(Kref_kotlin_Double value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder value_holder;
  return Kotlin_unboxDouble(DerefStablePointer(value.pinned, value_holder.slot()));
}
extern "C" KObjHeader* Kotlin_boxChar(KChar value, KObjHeader**);
static Kref_kotlin_Char createNullableCharImpl(KChar value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder result_holder;
  KObjHeader* result = Kotlin_boxChar(value,  result_holder.slot());
  return Kref_kotlin_Char { .pinned = CreateStablePointer(result) };
}
extern "C" KChar Kotlin_unboxChar(KObjHeader*);
static KChar getNonNullValueOfCharImpl(Kref_kotlin_Char value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder value_holder;
  return Kotlin_unboxChar(DerefStablePointer(value.pinned, value_holder.slot()));
}
extern "C" KObjHeader* Kotlin_boxBoolean(KBoolean value, KObjHeader**);
static Kref_kotlin_Boolean createNullableBooleanImpl(KBoolean value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder result_holder;
  KObjHeader* result = Kotlin_boxBoolean(value,  result_holder.slot());
  return Kref_kotlin_Boolean { .pinned = CreateStablePointer(result) };
}
extern "C" KBoolean Kotlin_unboxBoolean(KObjHeader*);
static KBoolean getNonNullValueOfBooleanImpl(Kref_kotlin_Boolean value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder value_holder;
  return Kotlin_unboxBoolean(DerefStablePointer(value.pinned, value_holder.slot()));
}
extern "C" KObjHeader* Kotlin_boxUnit( KObjHeader**);
static Kref_kotlin_Unit createNullableUnitImpl() {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
 KObjHolder result_holder;
  KObjHeader* result = Kotlin_boxUnit( result_holder.slot());
  return Kref_kotlin_Unit { .pinned = CreateStablePointer(result) };
}
extern "C" KObjHeader* Kotlin_boxUByte(KUByte value, KObjHeader**);
static Kref_kotlin_UByte createNullableUByteImpl(KUByte value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder result_holder;
  KObjHeader* result = Kotlin_boxUByte(value,  result_holder.slot());
  return Kref_kotlin_UByte { .pinned = CreateStablePointer(result) };
}
extern "C" KUByte Kotlin_unboxUByte(KObjHeader*);
static KUByte getNonNullValueOfUByteImpl(Kref_kotlin_UByte value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder value_holder;
  return Kotlin_unboxUByte(DerefStablePointer(value.pinned, value_holder.slot()));
}
extern "C" KObjHeader* Kotlin_boxUShort(KUShort value, KObjHeader**);
static Kref_kotlin_UShort createNullableUShortImpl(KUShort value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder result_holder;
  KObjHeader* result = Kotlin_boxUShort(value,  result_holder.slot());
  return Kref_kotlin_UShort { .pinned = CreateStablePointer(result) };
}
extern "C" KUShort Kotlin_unboxUShort(KObjHeader*);
static KUShort getNonNullValueOfUShortImpl(Kref_kotlin_UShort value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder value_holder;
  return Kotlin_unboxUShort(DerefStablePointer(value.pinned, value_holder.slot()));
}
extern "C" KObjHeader* Kotlin_boxUInt(KUInt value, KObjHeader**);
static Kref_kotlin_UInt createNullableUIntImpl(KUInt value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder result_holder;
  KObjHeader* result = Kotlin_boxUInt(value,  result_holder.slot());
  return Kref_kotlin_UInt { .pinned = CreateStablePointer(result) };
}
extern "C" KUInt Kotlin_unboxUInt(KObjHeader*);
static KUInt getNonNullValueOfUIntImpl(Kref_kotlin_UInt value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder value_holder;
  return Kotlin_unboxUInt(DerefStablePointer(value.pinned, value_holder.slot()));
}
extern "C" KObjHeader* Kotlin_boxULong(KULong value, KObjHeader**);
static Kref_kotlin_ULong createNullableULongImpl(KULong value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder result_holder;
  KObjHeader* result = Kotlin_boxULong(value,  result_holder.slot());
  return Kref_kotlin_ULong { .pinned = CreateStablePointer(result) };
}
extern "C" KULong Kotlin_unboxULong(KObjHeader*);
static KULong getNonNullValueOfULongImpl(Kref_kotlin_ULong value) {
  Kotlin_initRuntimeIfNeeded();
  ScopedRunnableState stateGuard;
  KObjHolder value_holder;
  return Kotlin_unboxULong(DerefStablePointer(value.pinned, value_holder.slot()));
}

static RuntimeBoxingExportedSymbols __konan_symbols = {
  .DisposeStablePointer = DisposeStablePointerImpl,
  .DisposeString = DisposeStringImpl,
  .IsInstance = IsInstanceImpl,
  .createNullableByte = createNullableByteImpl,
  .getNonNullValueOfByte = getNonNullValueOfByteImpl,
  .createNullableShort = createNullableShortImpl,
  .getNonNullValueOfShort = getNonNullValueOfShortImpl,
  .createNullableInt = createNullableIntImpl,
  .getNonNullValueOfInt = getNonNullValueOfIntImpl,
  .createNullableLong = createNullableLongImpl,
  .getNonNullValueOfLong = getNonNullValueOfLongImpl,
  .createNullableFloat = createNullableFloatImpl,
  .getNonNullValueOfFloat = getNonNullValueOfFloatImpl,
  .createNullableDouble = createNullableDoubleImpl,
  .getNonNullValueOfDouble = getNonNullValueOfDoubleImpl,
  .createNullableChar = createNullableCharImpl,
  .getNonNullValueOfChar = getNonNullValueOfCharImpl,
  .createNullableBoolean = createNullableBooleanImpl,
  .getNonNullValueOfBoolean = getNonNullValueOfBooleanImpl,
  .createNullableUnit = createNullableUnitImpl,
  .createNullableUByte = createNullableUByteImpl,
  .getNonNullValueOfUByte = getNonNullValueOfUByteImpl,
  .createNullableUShort = createNullableUShortImpl,
  .getNonNullValueOfUShort = getNonNullValueOfUShortImpl,
  .createNullableUInt = createNullableUIntImpl,
  .getNonNullValueOfUInt = getNonNullValueOfUIntImpl,
  .createNullableULong = createNullableULongImpl,
  .getNonNullValueOfULong = getNonNullValueOfULongImpl,
};
RUNTIME_EXPORT RuntimeBoxingExportedSymbols* runtimeboxing_symbols(void) { return &__konan_symbols;}
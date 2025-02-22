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
extern RuntimeBoxingExportedSymbols* runtimeboxing_symbols(void);
#ifdef __cplusplus
}  /* extern "C" */
#endif
#endif  /* RUNTIME_BOXING_H */
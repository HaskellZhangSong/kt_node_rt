#pragma once

#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>

#include <taihe/common.h>

namespace taihe::core {
template<typename cpp_t, typename = void>
struct cpp_type_traits;

template<typename cpp_t>
struct cpp_type_traits<cpp_t, std::enable_if_t<std::is_arithmetic_v<cpp_t>>> {
    using abi_t = cpp_t;
};

template<>
struct cpp_type_traits<void> {
    using abi_t = void;
};

template<typename cpp_t>
using as_abi_t = typename cpp_type_traits<cpp_t>::abi_t;

template<typename cpp_t, std::enable_if_t<!std::is_reference_v<cpp_t>, int> = 0>
inline as_abi_t<cpp_t> into_abi(cpp_t&& cpp_val) {
    as_abi_t<cpp_t> abi_val;
    new (&abi_val) cpp_t(std::move(cpp_val));
    return abi_val;
}

template<typename cpp_t, std::enable_if_t<!std::is_reference_v<cpp_t>, int> = 0>
inline as_abi_t<cpp_t> into_abi(cpp_t& cpp_val) {
    as_abi_t<cpp_t> abi_val;
    new (&abi_val) cpp_t(std::move(cpp_val));
    return abi_val;
}

template<typename cpp_t, std::enable_if_t<!std::is_reference_v<cpp_t>, int> = 0>
inline cpp_t&& from_abi(as_abi_t<cpp_t>& abi_val) {
    return reinterpret_cast<cpp_t&&>(abi_val);
}

template<typename cpp_t, std::enable_if_t<!std::is_reference_v<cpp_t>, int> = 0>
inline cpp_t&& from_abi(as_abi_t<cpp_t>&& abi_val) {
    return reinterpret_cast<cpp_t&&>(abi_val);
}

template<typename cpp_t, std::enable_if_t<std::is_reference_v<cpp_t>, int> = 0>
inline as_abi_t<cpp_t> into_abi(cpp_t cpp_val) {
    return reinterpret_cast<as_abi_t<cpp_t>>(&cpp_val);
}

template<typename cpp_t, std::enable_if_t<std::is_reference_v<cpp_t>, int> = 0>
inline cpp_t from_abi(as_abi_t<cpp_t> abi_val) {
    return reinterpret_cast<cpp_t>(*abi_val);
}

///////////////
// enum tags //
///////////////

template<auto tag>
struct static_tag_t {};

template<auto tag>
constexpr static_tag_t<tag> static_tag = {};

/////////////////////////
// hash and comparison //
/////////////////////////

struct adl_helper_t {};

template<typename T>
inline std::size_t hash(T&& val) {
    adl_helper_t adl_helper;
    return hash_impl(adl_helper, std::forward<T>(val));
}

template<typename L, typename R>
inline bool same(L&& lhs, R&& rhs) {
    adl_helper_t adl_helper;
    return same_impl(adl_helper, std::forward<L>(lhs), std::forward<R>(rhs));
}

template<typename T, typename std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline std::size_t hash_impl(adl_helper_t, T val) {
    return std::hash<T>{}(val);
}

template<typename T, typename std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline bool same_impl(adl_helper_t, T lhs, T rhs) {
    return lhs == rhs;
}
}

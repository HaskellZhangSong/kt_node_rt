#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <utility>
#include <string>
#include <string_view>
#include <iostream>
#include <charconv>

#include "taihe/common.hpp"
#include "taihe/string.abi.h"

namespace taihe::core {
struct string_view;
struct string;

struct string_view {
    using value_type = char;
    using size_type = std::size_t;
    using const_reference = value_type const&;
    using const_pointer = value_type const*;
    using const_iterator = const_pointer;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    explicit string_view(struct TString handle) : m_handle(handle) {}

    string_view(const char* value TH_NONNULL)
        : string_view(tstr_new_ref(value, strlen(value))) {}

    string_view(const char* value TH_NONNULL, size_type size)
        : string_view(tstr_new_ref(value, size)) {}

    string_view(std::initializer_list<char> value)
        : string_view(value.begin(), static_cast<uint32_t>(value.size())) {}

    string_view(std::string_view value)
        : string_view(value.data(), value.size()) {}

    string_view(std::string const &value)
        : string_view(value.data(), value.size()) {}

    operator std::string_view() const noexcept {
        return { tstr_buf(m_handle), tstr_len(m_handle) };
    }

    const_pointer c_str() const noexcept {
        return tstr_buf(m_handle);
    }

protected:
    struct TString m_handle;

    friend struct string;

    friend string concat(string_view left, string_view right);
    friend string substr(string_view sv, std::size_t pos, std::size_t len);
};

struct string : public string_view {
    explicit string(struct TString handle) : string_view(handle) {}

    string(const char* value TH_NONNULL)
        : string(tstr_new(value, std::strlen(value))) {}

    string(const char* value TH_NONNULL, size_type size)
        : string(tstr_new(value, size)) {}

    string(std::initializer_list<char> value)
        : string(value.begin(), static_cast<uint32_t>(value.size())) {}

    string(std::string_view value)
        : string(value.data(), value.size()) {}

    string(std::string const &value)
        : string(value.data(), value.size()) {}

    string(string_view const& other)
        : string(tstr_dup(other.m_handle)) {}

    string(string const& other)
        : string(tstr_dup(other.m_handle)) {}

    string(string&& other) noexcept
        : string(other.m_handle) {
        other.m_handle.ptr = NULL;
    }

    string& operator=(string other) {
        std::swap(this->m_handle, other.m_handle);
        return *this;
    }

    ~string() {
        if (m_handle.ptr != NULL) {
            tstr_drop(m_handle);
        }
    }
};

}

#ifndef ANYTYPE_HPP
#define ANYTYPE_HPP

#include "Utils.hpp"
#include "TypeName.hpp"

#include <algorithm>
#include <stdexcept>

class BadAnyTypeAccess : public std::logic_error
{
public:
    BadAnyTypeAccess(std::string_view type_name) : std::logic_error(
                                                       std::string("Anytype object is not containing value of type <") + std::string(type_name) + std::string("> at the moment")) {}
};

//--------------------------------------------------------------------------------

template <typename... Ts>
class AnyTypeImplementation
{
public:
    static_assert(distinct<Ts...>, "Error: Some types repeated in parameter pack");
    using This = AnyTypeImplementation<Ts...>;

    constexpr static auto size = max_size<Ts...>;
    constexpr static auto default_tag = sizeof...(Ts) + 1;

    AnyTypeImplementation() : tag(default_tag) {}

    //
    template <typename T>
    AnyTypeImplementation(const T &other)
    {
        static_assert(is_in_list<T, Ts...>, "Error: constructing AnyType from unexpected type");
        std::copy(
            reinterpret_cast<const std::byte *>(&other),
            reinterpret_cast<const std::byte *>(&other + 1),
            std::begin(raw_data));
        tag = get_type_index<T, Ts...>;
    }

    AnyTypeImplementation(const This &other)
    {
        std::copy(
            std::begin(other.raw_data),
            std::end(other.raw_data),
            std::begin(raw_data));
        tag = other.tag;
    }

    AnyTypeImplementation(const This &&other)
    {
        std::move(
            std::begin(other.raw_data),
            std::end(other.raw_data),
            std::begin(raw_data));
        tag = std::move(other.tag);
    }

    void swap(This &other)
    {
        using std::swap;

        swap(raw_data, other.raw_data);
        swap(tag, other.tag);
    }

    template <typename T>
    This &operator=(const T &other)
    {
        static_assert(is_in_list<T, Ts...>, "Error: assigning unexpected type to AnyType");
        std::copy(
            reinterpret_cast<const std::byte *>(&other),
            reinterpret_cast<const std::byte *>(&other + 1),
            std::begin(raw_data));
        tag = get_type_index<T, Ts...>;
        return *this;
    }

    This &operator=(const This &other)
    {
        This tmp(other);
        swap(tmp);
        return *this;
    }

    This &operator=(This &&other)
    {
        swap(other);
        return *this;
    }

    template <typename T>
    bool contains()
    {
        if constexpr (is_in_list<T, Ts...>)
        {
            return tag == get_type_index<T, Ts...>;
        }
        else
        {
            return false;
        }
    }

    template <typename T>
    T to()
    {
        static_assert(is_in_list<T, Ts...>, "Error: trying to get value of unexpected type from AnyType");
        if (!contains<T>())
        {
            throw BadAnyTypeAccess(type_name<T>);
        }
        return *reinterpret_cast<T *>(raw_data);
    }

    void destroy()
    {
        std::fill(std::begin(raw_data), std::end(raw_data), std::byte(0));
        tag = default_tag;
    }

private:
    std::byte raw_data[size];
    std::size_t tag;
};

using AnyType = AnyTypeImplementation<
    bool,

    char,
    signed char,
    unsigned char,

    wchar_t,
    char16_t,
    char32_t,

    signed short,
    unsigned short,

    signed int,
    unsigned int,

    signed long,
    unsigned long,

    signed long long,
    unsigned long long,

    float,
    double,
    long double>;

#endif /* ANYTYPE_HPP */

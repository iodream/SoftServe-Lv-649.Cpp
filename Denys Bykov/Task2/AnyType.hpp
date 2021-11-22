#ifndef ANYTYPE_HPP_SENTRY
#define ANYTYPE_HPP_SENTRY

#include <string>
#include <exception>
#include <algorithm>

template <class Target, class T, class... Tail>
struct type_index {
    const int value = type_index<Target, Tail...>().value + 1;
};

template <class Target, class... Tail>
struct type_index<Target, Target, Tail...> {
    const int value = 0;
};

// finds an index of the type in its parameter pack
template <class Target, class... T>
int get_index()
{
    return type_index<Target, T...>().value;
}

constexpr int max(int val1, int val2)
{
    return (val1 > val2) ? val1 : val2;
}

template <class T, class... Tail>
struct max_size {
    const int value = max(sizeof(T), max_size<Tail...>().value);
};

template <class T>
struct max_size<T> {
    const int value = sizeof(T);
};

// finds a size of the largest type in its parameter pack
template <class... T>
constexpr int get_max_size()
{
    return max_size<T...>().value;
}

class TypeError: public std::exception {
public:
    explicit TypeError(const char* message)
        : msg_(message) {}

    explicit TypeError(const std::string& message)
        : msg_(message) {}

    virtual ~TypeError() noexcept {}
    virtual const char* what() const noexcept {
       return msg_.c_str();
    }

protected:
    std::string msg_;
};

template <class... Types>
class AnyTypeBase {
    int type_idx{-1};
    int size{0};
    char data[get_max_size<Types...>()];
public:
    AnyTypeBase(): data{} {}

    template<class T>
    AnyTypeBase(const T& x):
        type_idx{get_index<T, Types...>()}
    {
        size = sizeof(T);
        auto ptr = reinterpret_cast<const char*>(&x);
        std::copy(ptr, ptr + size, data);
    }

    AnyTypeBase(const AnyTypeBase<Types...>& other):
        type_idx{other.type_idx}
    {
        size = other.size;
        std::copy(other.data, other.data + size, data);
    }

    AnyTypeBase(AnyTypeBase<Types...>&& other):
        type_idx{other.type_idx}
    {
        size = other.size;
        std::copy(other.data, other.data + size, data);
        other.Destroy();
    }

    template<class T>
    void operator=(const T& x)
    {
        type_idx = get_index<T, Types...>();
        size = sizeof(T);
        auto ptr = reinterpret_cast<const char*>(&x);
        std::copy(ptr, ptr + size, data);
    }

    void operator=(const AnyTypeBase<Types...>& other)
    {
        type_idx = other.type_idx;
        size = other.size;
        std::copy(other.data, other.data + size, data);
    }

    void operator=(AnyTypeBase<Types...>&& other)
    {
        type_idx = other.type_idx;
        size = other.size;
        std::copy(other.data, other.data + size, data);
        other.Destroy();
    }

    void Destroy()
    {
        type_idx = -1;
        size = 0;
    }

    void Swap(AnyTypeBase<Types...>& other)
    {
        std::swap(type_idx, other.type_idx);
        std::swap(size, other.size);
        char tmp[get_max_size<Types...>()];
        std::copy(other.data, other.data + size, tmp);
        std::copy(data, data + other.size, other.data);
        std::copy(tmp, tmp + size, data);
    }

    template<class T>
    T To()
    {
        if (type_idx == -1)
            throw TypeError("No value stored");
        if (type_idx != get_index<T, Types...>())
            throw TypeError("Stored value is not of the requested type");
        T res;
        std::copy(data, data + size, reinterpret_cast<char*>(&res));
        return res;
    }

    int GetTypeIndex()
    {
        return type_idx;
    }
};

class AnyType
    : public AnyTypeBase<bool, char, signed char, unsigned char, wchar_t,
                         char16_t, char32_t, int, unsigned int, short int,
                         unsigned short int, long int, unsigned long int,
                         long long int, unsigned long long int, float,
                         double, long double> {
public:
    enum class Type {
    NoType = -1,

    Bool,

    Char,
    SignedChar,
    UnsignedChar,
    Wchar,
    Char16,
    Char32,

    Int,
    UnsignedInt,
    ShortInt,
    UnsignedShortInt,
    LongInt,
    UnsignedLongInt,
    LongLongInt,
    UnsignedLongLongInt,

    Float,
    Double,
    LongDouble
};
private:
    Type IdxToType(int idx) { return static_cast<Type>(idx); }
public:
    using AnyTypeBase<bool, char, signed char, unsigned char, wchar_t,
                      char16_t, char32_t, int, unsigned int, short int,
                      unsigned short int, long int, unsigned long int,
                      long long int, unsigned long long int, float,
                      double, long double>::AnyTypeBase;
    Type GetType() {
        return IdxToType(GetTypeIndex());
    }
};

#endif

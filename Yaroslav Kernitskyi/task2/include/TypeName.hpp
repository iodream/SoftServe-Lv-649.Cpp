#include <string_view>

// Best way i could think of
template <typename T>
constexpr std::string_view type_name = "unknown";

template <>
constexpr std::string_view type_name<bool> = "bool";

template <>
constexpr std::string_view type_name<char> = "char";
template <>
constexpr std::string_view type_name<signed char> = "signed char";
template <>
constexpr std::string_view type_name<unsigned char> = "unsigned char";
template <>
constexpr std::string_view type_name<wchar_t> = "wchar_t";
template <>
constexpr std::string_view type_name<char16_t> = "char16_t";
template <>
constexpr std::string_view type_name<char32_t> = "char32_t";

template <>
constexpr std::string_view type_name<signed short> = "signed short";
template <>
constexpr std::string_view type_name<unsigned short> = "unsigned short";
template <>
constexpr std::string_view type_name<int> = "int";
template <>
constexpr std::string_view type_name<unsigned int> = "unsigned int";
template <>
constexpr std::string_view type_name<signed long> = "signed long";
template <>
constexpr std::string_view type_name<unsigned long> = "unsigned long";
template <>
constexpr std::string_view type_name<signed long long> = "signed long long";
template <>
constexpr std::string_view type_name<unsigned long long> = "unsigned long long";

template <>
constexpr std::string_view type_name<float> = "float";
template <>
constexpr std::string_view type_name<double> = "double";
template <>
constexpr std::string_view type_name<long double> = "long double";

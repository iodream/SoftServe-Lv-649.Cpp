#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstddef>

// Some utility functions
template <typename T, typename... Ts>
constexpr auto max_size_impl()
{
    auto maximum = sizeof(T);
    ((maximum = std::max(maximum, sizeof(Ts))), ...);
    return maximum;
}
template <typename T, typename... Ts>
constexpr auto max_size = max_size_impl<T, Ts...>();

template <typename T, typename U, typename... Ts>
constexpr std::size_t get_type_index_impl()
{
    if constexpr (std::is_same_v<T, U>)
    {
        return 0;
    }
    else
    {
        return 1 + get_type_index_impl<T, Ts...>();
    }
}
template <typename T, typename... Ts>
constexpr auto get_type_index = get_type_index_impl<T, Ts...>();

template <typename T, typename... Ts>
constexpr bool is_in_list = (std::is_same_v<T, Ts> || ...);
template <typename T>
constexpr bool is_in_list<T> = false;

template <typename T, typename... Ts>
constexpr bool distinct = (!is_in_list<T, Ts...> && distinct<Ts...>);
template <typename T>
constexpr bool distinct<T> = true;

#endif /* UTILS_HPP */

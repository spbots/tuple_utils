#pragma once
#include "is_in_tuple.hpp"

#include <tuple>
#include <type_traits>

namespace tuple_utils
{

namespace detail
{
template <typename InputTuple, typename OutputTuple>
struct unique
{};

template <typename OutputTuple>
struct unique<std::tuple<>, OutputTuple>
{
  using type = OutputTuple;
};

template <typename T, typename... Ts, typename... Us>
struct unique<std::tuple<T, Ts...>, std::tuple<Us...>>
  : unique<
      std::tuple<Ts...>,
      typename std::conditional<is_in_tuple<T, std::tuple<Us...>>::value,
        std::tuple<Us...>,
        std::tuple<Us..., T >>::type>
{
};
} // namespace detail


/** Provide a tuple that has no duplicate types.

Requires that the input is a flat tuple (i.e. no nested tuples).
*/
template <typename T>
using unique = detail::unique<T, std::tuple<>>;

template <typename T>
using unique_t = typename unique<T>::type;

} // namespace tuple_utils

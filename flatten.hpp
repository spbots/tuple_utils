#pragma once
#include <tuple>

namespace tuple_utils
{

namespace detail
{
/** flatten converts a tree of std::tuple to to a flat std::tuple.

flatten takes in an std::tuple as its ...Inputs type, an empty tuple as
its output, and the ::type of the deduced type will be a flat tuple of
all the non-tuple types from the input.

It's most likely that you actually want to use flatten_t.
*/
template <typename Output = std::tuple<>, //< output
          typename... Inputs>             //< inputs
struct flatten;

/**
If the first of the input parameters is a tuple, extract the individual
types from the tuple.
*/
template <typename... OutTs, typename... Ts, typename... Rest>
struct flatten<std::tuple<OutTs...>, //< output
               std::tuple<Ts...>,    //< input tuple
               Rest...>
  : flatten<std::tuple<OutTs...>, Ts..., Rest...>
{
};

/**
If the first of the input parameters is not a tuple, add it to the output tuple.
*/
template <typename Input, typename... OutTs, typename... Rest>
struct flatten<std::tuple<OutTs...>, //< output
               Input,                //< non-tuple type
               Rest...>
  : flatten<std::tuple<OutTs..., Input>, Rest...>
{
};

/**
If there are no more inputs "return" the flattened output tuple.
*/
template <typename... OutTs>
struct flatten<std::tuple<OutTs...>>
{
  using type = std::tuple<OutTs...>;
};
} // namespace detail

template <typename T>
using flatten = detail::flatten<std::tuple<>, T>;

template <typename T>
using flatten_t = typename flatten<T>::type;

} // namespace tuple_utils

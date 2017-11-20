#pragma once
#include <tuple>
#include <type_traits>

namespace tuple_utils
{

/** is_in_tuple is used to check whether a given type exists in a tuple.

Note that it only looks at the top level of the tuple - if you provide
a tuple tree it will not flatten it to search for the type.
*/
template <typename TypeToCheck, typename Tuple>
struct is_in_tuple;

template <typename TypeToCheck, typename T, typename... Ts>
struct is_in_tuple <TypeToCheck, std::tuple<T, Ts...>>
{
  static const bool value = is_in_tuple<TypeToCheck, std::tuple<Ts...>>::value;
};

template <typename TypeToCheck, typename... Ts>
struct is_in_tuple <TypeToCheck, std::tuple<TypeToCheck, Ts...>> : std::true_type
{
};

template <typename TypeToCheck>
struct is_in_tuple <TypeToCheck, std::tuple<>> : std::false_type
{
};

} // namespace tuple_utils

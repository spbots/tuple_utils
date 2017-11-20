#pragma once
#include <tuple>
#include <type_traits>

namespace tuple_utils
{

namespace detail
{
template <template <typename> class Predicate,
          typename InputTuple,
          typename OutputTuple = std::tuple<>>
struct filter;

template <template <typename> class Predicate, typename Result>
struct filter<Predicate, std::tuple<>, Result>
{
  using type = Result;
};

template <template <typename> class Predicate,
          typename T,
          typename... Ts,
          typename... Filtered>
struct filter<Predicate, std::tuple<T, Ts...>, std::tuple<Filtered...>>
  : filter<
      Predicate,
      std::tuple<Ts...>,
      typename std::conditional<Predicate<T>::value,
        std::tuple<Filtered..., T>,
        std::tuple<Filtered... >>::type>
{
};
} // namespace detail

/** Return a tuple type that only contains types that satisfy the Predicate.
*/
template <typename unfiltered_t, template <typename> class Predicate>
using filtered_t = typename detail::filter<Predicate, unfiltered_t>::type;

} // namespace tuple_utils

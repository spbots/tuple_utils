#include "filter.hpp"
#include "flatten.hpp"
#include "is_in_tuple.hpp"
#include "unique.hpp"

namespace tuple_utils
{
namespace test
{

template <typename T> struct IsGreaterThanOne {
  static const bool value = T::value > 1;
};
using test_filtered_t = filtered_t<std::tuple<
  std::integral_constant<size_t, 0>, std::integral_constant<size_t, 1>,
  std::integral_constant<size_t, 2>, std::integral_constant<size_t, 3>>,
  IsGreaterThanOne>;
using expected_filtered_t = std::tuple<
  std::integral_constant<size_t, 2>, std::integral_constant<size_t, 3>>;
static_assert(std::is_same<test_filtered_t, expected_filtered_t>::value,
  "filter is broken.");


using test_flatten_t = flatten_t<
std::tuple<
  std::tuple<
    double,
    int,
    int,
    std::tuple<
      float,
      char,
      std::tuple<>,
      std::tuple<int>
    >
  >,
  size_t
>>;
using expected_flatten_t = std::tuple<double, int, int, float, char, int, size_t>;
static_assert(std::is_same<test_flatten_t, expected_flatten_t>::value,
  "flatten is broken.");


using test_is_in_tuple_t = std::tuple<int, float, std::tuple<double>>;
static_assert(is_in_tuple<int, test_is_in_tuple_t>::value, "is_in_tuple broken.");
static_assert(is_in_tuple<float, test_is_in_tuple_t>::value, "is_in_tuple broken.");
static_assert(!is_in_tuple<double, test_is_in_tuple_t>::value, "is_in_tuple broken.");


using test_unique_t = unique_t<std::tuple<int, float, int, float, double, int, bool>>;
using expected_unique_t = std::tuple<int, float, double, bool>;
static_assert(std::is_same<test_unique_t, expected_unique_t>::value,
  "unique is broken.");

} // namespace test
} // namespace tuple_utils

int main() { return 0; }
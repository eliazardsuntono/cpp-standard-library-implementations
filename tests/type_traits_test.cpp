#include <assert.h>
#include <cassert>

#include "../custom_std/include/type_traits.h"

int main() {
  using two_t = custom_std::integral_constant<int, 2>;
  using four_t = custom_std::integral_constant<int, 4>;

  static_assert(not custom_std::is_same_v<two_t, four_t>, "2 != 4");
  static_assert(two_t() != four_t::value, "2 != 4");
}

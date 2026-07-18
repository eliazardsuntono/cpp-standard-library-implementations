#include <cstddef>
#include <iostream>

#include "vector.h"

int main() {
  custom_std::vector<int> test_list(6, 7);
  int * data = test_list.data();
  std::size_t size = test_list.size();
  std::cout << "first: " << data[0] << std::endl;
  std::cout << "last: "  << data[size - 1] << std::endl;
  return 0;
}

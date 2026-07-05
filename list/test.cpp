#include <iostream>
#include <cassert>
#include <vector>

#include "list.h"

int main() {
  int value = 5;
  custom_std::list<int> test_list(3, value);
  assert(test_list.size() == 3 && "test list size should return 2");
  assert(test_list.front() == 5 && test_list.back() == 5 &&
      "front and back of list must return 2");

  std::vector<int> num_array{ 1, 2, 3, 4, 5 };
  custom_std::list<int> test_list2(std::begin(num_array), std::end(num_array));
  assert(test_list2.size() == 5 && "test list size should return 5");
  assert(test_list2.front() == 1 && test_list2.back() == 5 &&
      "front and back of list must return 1 and 2");

  return 0;

}

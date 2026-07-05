#include <iostream>
#include <cassert>

#include "list.h"

int main() {
  int value = 5;
  custom_std::list<int> test_list(3, value);
  assert(test_list.size() == 3 && "test list size should return 5");
  assert(test_list.front() == 5 && test_list.back() == 5 &&
      "front and back of list must return 2");
}

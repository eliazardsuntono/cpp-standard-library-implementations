#include <iostream>
#include <cassert>

#include "list.h"

int main() {
  int value = 5;
  custom_std::list<int> test_list(2, value);
  assert(test_list.size() == 5 && "test list size should return 5");
  assert(test_list.front() == 2 && test_list.back() == 2 &&
      "front and back of list must return 2");
}

#include <cstddef>
#include <iostream>

#include "vector.h"

int main() {
  custom_std::vector<int> test_list{ 1, 2, 3, 4, 5 };
  auto * data = test_list.data();
  std::size_t size = test_list.size();
  std::cout << "first: " << data[0]        << std::endl;
  std::cout << "last: "  << data[size - 1] << std::endl;

  int const & cr = test_list.at(0);
  int & ref      = test_list.at(0);
  std::cout << "Const ref: " << cr  << std::endl;
  std::cout << "Reference: " << ref << std::endl;
 
  int const & cr_ = test_list[0];
  int & ref_      = test_list[0];
  std::cout << "Const ref_: " << cr  << std::endl;
  std::cout << "Reference_: " << ref << std::endl;

  custom_std::vector<int> test_list2{ 5, 4, 3, 2, 1 };
  auto * data_2 = test_list2.data();
  std::cout << "Old cap: "    << test_list2.capacity() << std::endl;
  test_list2.reserve(6);
  std::cout << "New cap: "    << test_list2.capacity() << std::endl;
  test_list2.shrink_to_fit();
  std::cout << "Shrunk cap: " << test_list2.capacity() << std::endl;

  test_list2.push_back(0);
  std::size_t size2 = test_list2.size();
  std::cout << "Appended back: " << data_2[size2 - 1]     << std::endl;
  std::cout << "New capacitiy: " << test_list2.capacity() << std::endl;
  return 0;
}

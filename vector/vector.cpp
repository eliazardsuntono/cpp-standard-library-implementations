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
  
  return 0;
}

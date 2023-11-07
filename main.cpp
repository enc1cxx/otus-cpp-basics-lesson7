#include "vector.hpp"
#include <iostream>


int main() {
  static int counters = 0;
  class Helper {
  public:
    ~Helper() { ++counters; }
  };
  vector::Vector<Helper> vector1;
  Helper h;
  vector1.push_back(h);
  vector1.push_back(h);
  vector1.push_back(h);
  // vector1.~Vector();
  // std::cout << counters << std::endl;
  std::cout << "Empty main" << std::endl;
  return 0;
}
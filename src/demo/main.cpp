#include "cpp-physics.hpp"
#include <iostream>

using namespace cpp_physics;
using namespace std;

int main() {
  Matrix a = Matrix::Identity(3);
  Matrix b(3, 3);
  b[2, 0] = 1;
  b[1, 1] = 1;
  b[0, 2] = 1;
  Matrix c = a + b;
  std::cout << c << std::endl;
  return 0;
}

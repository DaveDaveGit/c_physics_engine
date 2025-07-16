#include "cpp-physics.hpp"

using namespace cpp_physics;

int main() {

  Matrix a = Matrix::Identity(7);
  Matrix b = a + a;
  if (a * b != 2 * a) return 1;
  return 0;
}

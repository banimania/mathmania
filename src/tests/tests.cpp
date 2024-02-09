#include <iostream>
#include "../../include/mathmania.hpp"

template <typename T>
inline int test(T output, T expected, const char* testName) {
  int pass = output == expected;
  if (!pass) std::cout << "Test " << testName << " failed! Output: " << output << " Expected: " << expected << std::endl;
  return pass;
}

int main() {
  Matrix matrix2 = {2, 2};
  matrix2.setElements(new float[]{20, 30, 40, 50}, 4);

  Matrix matrix3 = {3, 3};
  matrix3.setElements(new float[]{1, 2, 3, 4, 5, 6, 7, 8, 9}, 9);

  Matrix matrix3adj = *MatrixAdjugate(&matrix3);
  Matrix matrixTest = *MatrixTest(&matrix3, 0, 0);

  test(Determinant(&matrix2), -200, "Determinant 2x2");
  test(Determinant(&matrix3), 5, "Determinant 3x3");
  test<float>(ElementAdjugate(&matrix3, 1, 1), -12, "Adjugate Element 3x3");
  test(Determinant(MatrixAdjugate(&matrix3)), 27, "Adjugate Matrix 3x3");
  
  matrixTest.print();
  return 0;
}

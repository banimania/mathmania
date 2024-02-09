#include <cstdlib>
#include <iostream>
#include "../../include/mathmania.hpp"

template <typename T>
inline int test(T output, T expected, const char* testName) {
  float epsilon = 0.00001f;
  int pass = std::abs(output - expected) < epsilon;
  if (!pass) std::cout << "Test " << testName << " failed! Output: " << output << " Expected: " << expected << std::endl;
  return pass;
}

int main() {
  //TESTS
  //Check actual code in /include/
  Matrix matrix2 = {2, 2};
  matrix2.setElements(new float[]{20, 30, 40, 50});

  Matrix matrix3 = {3, 3};
  matrix3.setElements(new float[]{1, 2, 3, 4, 5, 6, 7, 8, 9});

  Matrix matrix3_2 = {3, 3};
  matrix3_2.setElements(new float[]{9, 4, -2, -1, 0, 3, 4, 2, -1});

  Matrix matrix3adj = *MatrixAdjugate(&matrix3);

  Matrix matrix3_transpose = *MatrixTranspose(&matrix3);
  Matrix matrix3_2_inverse = *MatrixInverse(&matrix3_2);

  Matrix matrix4 = {4, 4};
  matrix4.setElements(new float[]{10, 55, 84, 81, 92, 97, 29, 47, 41, 46, 20, 19, 2, 3, 4, 99});

  Matrix matrix2_addition = matrix2 + matrix2;
  Matrix matrix2_substraction = matrix2 - matrix2;
  Matrix matrix2_multiplication = matrix2 * matrix2;

  test<float>(Determinant(&matrix2), -200, "Determinant 2x2");
  test<float>(Determinant(&matrix3), 0, "Determinant 3x3");
  test<float>(Determinant(&matrix4), -850758, "Determinant 4x4");
  test<float>(ElementAdjugate(&matrix3, 1, 1), -12, "Adjugate Element 3x3");
  test<float>(Determinant(MatrixAdjugate(&matrix3)), 0, "Determinant Adjugate Matrix 3x3");
  test<float>(Determinant(&matrix3_transpose), 0, "Determinant Transposed Matrix");
  test<float>(Determinant(&matrix3_2_inverse), -1.0f / 6.0f, "Determinant Transposed Matrix");
  test<float>(Determinant(&matrix2_multiplication), 40000, "Determinant Matrix Product");

  return 0;
}

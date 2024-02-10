#include <cstdlib>
#include <iostream>
#include <tuple>
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
  matrix matrix2 = {2, 2};
  matrix2.setElements(new float[]{20, 30, 40, 50});

  matrix matrix3 = {3, 3};
  matrix3.setElements(new float[]{1, 2, 3, 4, 5, 6, 7, 8, 9});

  matrix matrix3c = {3, 3};
  matrix3c.setElements(new float[]{10, 6, 1, 3, 5, 9, 11, 10, 8});
  
  matrix matrix3_2 = {3, 3};
  matrix3_2.setElements(new float[]{9, 4, -2, -1, 0, 3, 4, 2, -1});

  matrix matrix3adj = *MatrixAdjugate(&matrix3);

  matrix matrix3_transpose = *MatrixTranspose(&matrix3);
  matrix matrix3_2_inverse = *MatrixInverse(&matrix3_2);

  matrix matrix4 = {4, 4};
  matrix4.setElements(new float[]{10, 55, 84, 81, 92, 97, 29, 47, 41, 46, 20, 19, 2, 3, 4, 99});

  matrix matrix2_addition = matrix2 + matrix2;
  matrix matrix2_substraction = matrix2 - matrix2;
  matrix matrix2_multiplication = matrix2 * matrix2;

  vector v = {4, 4, 4};
  vector v_2 = {4, 4, 4};
  vector u = {2, 1, 3};
  

  vector p_p = {4, 0, 0};
  vector p_u = {-2, 1, 0};
  vector p_v = {3, 0, 1};

  plane p = {&p_p, &p_u, &p_v};
  float a = std::get<0>(p.getCoefficients());
  float b = std::get<1>(p.getCoefficients());
  float c = std::get<2>(p.getCoefficients());
  float d = std::get<3>(p.getCoefficients());
 
  vector l_p = {1, 1, 1};
  vector l_v = {2, 3, 4};
  line l = {&l_p, &l_v};

  line l2 = {new vector{1, 5, -2}, new vector{2, -1, 3}};
  line l3 = {new vector{-7, 4, 1}, new vector{1, 2, -6}};

  test<float>(Determinant(&matrix2), -200, "Determinant 2x2");
  test<float>(Determinant(&matrix3), 0, "Determinant 3x3");
  test<float>(Determinant(&matrix4), -850758, "Determinant 4x4");
  test<float>(ElementAdjugate(&matrix3, 1, 1), -12, "Adjugate Element 3x3");
  test<float>(Determinant(MatrixAdjugate(&matrix3)), 0, "Determinant Adjugate Matrix 3x3");
  test<float>(Determinant(&matrix3_transpose), 0, "Determinant Transposed Matrix");
  test<float>(Determinant(&matrix3_2_inverse), -1.0f / 6.0f, "Determinant Transposed Matrix");
  test<float>(Determinant(&matrix2_multiplication), 40000, "Determinant Matrix Product");
  test<float>(Determinant(MatrixInverse(&matrix3_2)), 1.0f / Determinant(&matrix3_2), "Determinant Inverse Matrix");
  test<float>(matrix3c - matrix3_2 == matrix3, true, "Matrix Comparison");
  test<float>(Sqrt(300), 17.3205f, "Square Root");
  test<float>(NormalizeVector(&v)->x, 0.57735, "Normalize Vector");
  test<float>(v * u, 24, "Vector Dot Product");
  test<float>(v == v_2, true, "Vector Comparison");
  test<float>(a + b + c + d, - 4, "Plane Coefficients");
  test<float>(*IntersectionPlaneLine(&p, &l) == *(new vector{-1, -2, -3}), true, "Plane Line Intersection");
  test<float>(*IntersectionLineLine(&l2, &l3) == *(new vector{-5, 8, -11}), true, "Line Line Intersection");

  return 0;
}

#ifndef DETERMINANTS_HPP
#define DETERMINANTS_HPP

#include "matrix.hpp"
#include <cassert>
#include <cstdlib>

Matrix* MatrixDeleteRowAndColumn(Matrix* matrix, int i, int j) {
  assert(matrix->isSquare());

  int newOrder = std::get<0>(matrix->getOrder()) - 1;
  Matrix* auxMatrix = new Matrix{newOrder, newOrder};

  float* newElements = (float*) malloc(newOrder * newOrder * sizeof(float));

  int count = 0;
  for (int k = 0; k < newOrder + 1; k++) {
    for (int l = 0; l < newOrder + 1; l++) {
      if (i == k || j == l) continue;
      *(newElements + count) = matrix->getElement(k, l);
      count++;
    }
  }

  auxMatrix->setElements(newElements, newOrder * newOrder);

  return auxMatrix;
}

float Determinant1x1(Matrix* matrix) {
  assert(std::get<0>(matrix->getOrder()) == 1 && std::get<1>(matrix->getOrder()) == 1);
  
  return matrix->getElement(0, 0);
}

float Determinant2x2(Matrix* matrix) {
  assert(std::get<0>(matrix->getOrder()) == 2 && std::get<1>(matrix->getOrder()) == 2);
  
  return matrix->getElement(0, 0) * matrix->getElement(1, 1) - matrix->getElement(0, 1) * matrix->getElement(1, 0);
}

/*float DeterminantLarger(Matrix* matrix, int order) {
  assert(matrix->isSquare());
  
  float determinant = 0.0f;
  
  int sign = 1;
  for (int i = 0; i < order; i++) {
    float element = matrix->getElement(i, 0);

    determinant += element * sign * Determinant(MatrixDeleteRowAndColumn(matrix, i, 0));

    sign = sign == 1 ? -1 : 1;
  }

  return determinant;
}*/

Matrix* MatrixTranspose(Matrix* matrix) {
  int m = std::get<0>(matrix->getOrder());
  int n = std::get<1>(matrix->getOrder());

  Matrix* result = new Matrix{n, m};

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      result->setElement(i, j, matrix->getElement(j, i));
    }
  }

  return result;
}

float Determinant(Matrix* matrix) {
  assert(std::get<0>(matrix->getOrder()) == std::get<1>(matrix->getOrder()));
  
  int order = std::get<0>(matrix->getOrder());
  switch (order) {
    case 1:
      return Determinant1x1(matrix);
      break;
    case 2:
      return Determinant2x2(matrix);
      break;
    default:
      float determinant = 0.0f;

      int sign = 1;
      for (int i = 0; i < order; i++) {
        float element = matrix->getElement(i, 0);

        determinant += element * sign * Determinant(MatrixDeleteRowAndColumn(matrix, i, 0));

        sign = sign == 1 ? -1 : 1;
      }

      return determinant;
      break;
  }
}

float ElementAdjugate(Matrix* matrix, int i, int j) {
  assert(matrix->isSquare());

  int sign = (i + j) % 2 == 0 ? 1 : -1;

  Matrix* auxMatrix = MatrixDeleteRowAndColumn(matrix, i, j);

  return sign * Determinant(auxMatrix);
}

Matrix* MatrixAdjugate(Matrix* matrix) {
  assert(matrix->isSquare());

  int order = std::get<0>(matrix->getOrder());

  Matrix* adjugate = new Matrix{order, order};
  for (int i = 0; i < order; i++) {
    for (int j = 0; j < order; j++) {
      adjugate->setElement(i, j, ElementAdjugate(matrix, i, j));
    }
  }

  return adjugate;
}

Matrix* MatrixInverse(Matrix* matrix) {
  assert(matrix->isSquare() && Determinant(matrix) != 0);

  int order = std::get<0>(matrix->getOrder());
  float multiplier = 1.0f / Determinant(matrix);

  Matrix* transposeAdjugateMatrix = MatrixTranspose(MatrixAdjugate(matrix));
  Matrix* inverseMatrix = new Matrix{order, order};
  
  for (int i = 0; i < order; i++) {
    for (int j = 0; j < order; j++) {
      inverseMatrix->setElement(i, j, multiplier * transposeAdjugateMatrix->getElement(i, j));
    }
  }

  return inverseMatrix;
}
#endif

#ifndef DETERMINANTS_HPP
#define DETERMINANTS_HPP

#include "matrix.hpp"
#include <cassert>

int Determinant1x1(Matrix* matrix) {
  assert(std::get<0>(matrix->getOrder()) == 1 && std::get<1>(matrix->getOrder()) == 1);
  
  return matrix->getElement(0, 0);
}

int Determinant2x2(Matrix* matrix) {
  assert(std::get<0>(matrix->getOrder()) == 2 && std::get<1>(matrix->getOrder()) == 2);
  
  return matrix->getElement(0, 0) * matrix->getElement(1, 1) - matrix->getElement(0, 1) * matrix->getElement(1, 0);
}

//TODO
int DeterminantLarger(Matrix* matrix, int order) {
  assert(matrix->isSquare());
  
  

  return 5;
}

int Determinant(Matrix* matrix) {
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
      return DeterminantLarger(matrix, order);
      break;
  }
}

//TODO: fix this
float ElementAdjugate(Matrix* matrix, int i, int j) {
  assert(matrix->isSquare());

  int sign = i + j % 2 == 0 ? 1 : -1;

  int newOrder = std::get<0>(matrix->getOrder()) - 1;
  Matrix auxMatrix = {newOrder, newOrder};

  int carry = 0;
  for (int k = 0; k < newOrder + 1; k++) {
    for (int l = 0; l < newOrder + 1; l++) {
      if (k == i || l == j) {
        if (!carry) carry++;
        continue;
      }
      auxMatrix.setElement(k - carry, l - carry, matrix->getElement(k, l));
    }
  }

  return sign * Determinant(&auxMatrix);
}

//TODO: fix this
Matrix* MatrixTest(Matrix* matrix, int i, int j) {
  assert(matrix->isSquare());

  int newOrder = std::get<0>(matrix->getOrder()) - 1;
  Matrix* auxMatrix = new Matrix{newOrder, newOrder};

  int carryRow = 0;
  int carryCol = 0;
  for (int k = 0; k < newOrder; k++) {
    carryCol = 0;
    if (k == i) {
      carryRow = 1;
      continue;
    }
    for (int l = 0; l < newOrder; l++) {
      if (l == j) {
        carryCol = 1;
        continue;
      }
      auxMatrix->setElement(k - carryRow, l - carryCol, matrix->getElement(k, l));
    }
  }

  return auxMatrix;
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

#endif

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <tuple>

struct Matrix {
private:
  int m, n;
  float* elements;
public:
  void setZero() {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        setElement(i, j, 0.0f);
      }
    }
  }

  void setIdentity() {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        setElement(i, j, i == j);
      }
    }
  }

  void setElement(int i, int j, float value) {
    *(elements + i * n + j) = value;
  }

  void setElements(float* newElements, int size) {
    assert(sizeof(float) * size == m * n * sizeof(float));

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        setElement(i, j, *(newElements + i * n + j));
      }
    }
  }

  void setElements(float* newElements) {
    setElements(newElements, m * n);
  }

  float getElement(int i, int j) {
    return *(elements + i * n + j);
  }

  bool isSquare() {
    return n == m;
  }

  std::tuple<int, int> getOrder() {
    return std::make_tuple(m, n);
  }

  Matrix(int m, int n) : m(m), n(n) {
    elements = (float*) malloc(m * n * sizeof(float));
    setZero();
  }

  Matrix& operator+(Matrix& matrix) {
    assert(matrix.n == n && matrix.m == m);
    
    Matrix* newMatrix = new Matrix(n, m);
    
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        newMatrix->setElement(i, j, matrix.getElement(i, j) + getElement(i, j));
      }
    }

    return *newMatrix;
  }
  
  Matrix& operator-(Matrix& matrix) {
    assert(matrix.n == n && matrix.m == m);
    
    Matrix* newMatrix = new Matrix(n, m);
    
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        newMatrix->setElement(i, j, getElement(i, j) - matrix.getElement(i, j));
      }
    }

    return *newMatrix;
  }

  Matrix& operator*(Matrix& matrix) {
    assert(matrix.m == n);

    int newM = m;
    int newN = matrix.n;

    Matrix* newMatrix = new Matrix(newM, newN);
    
    for (int i = 0; i < newM; i++) {
      for (int j = 0; j < newN; j++) {
        float sum = 0;
        for (int k = 0; k < n; k++) {
          sum += matrix.getElement(i, k) * matrix.getElement(k, j);
        }

        newMatrix->setElement(i, j, sum);
      }
    }

    return *newMatrix;
  }

  bool& operator==(Matrix& matrix) {
    if (matrix.m != m || matrix.n != n) return *(new bool(false));

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (matrix.getElement(i, j) != getElement(i, j)) return *(new bool(false));
      }
    }

    return *(new bool(true));
  }

  void print() {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        std::cout << getElement(i, j) << " ";
      }
      std::cout << std::endl;
    }
  }
};

typedef Matrix matrix;

#endif

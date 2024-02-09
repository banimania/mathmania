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

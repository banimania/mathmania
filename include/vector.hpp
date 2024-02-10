#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "sqrt.hpp"
#include <iostream>

struct Vector {
public:
  float x, y, z;

  Vector(float x, float y, float z) : x(x), y(y), z(z) {}

  Vector& operator+(Vector& vector) {
    return *(new Vector(x + vector.x, y + vector.y, z + vector.z));
  }

  Vector& operator-(Vector& vector) {
    return *(new Vector(x - vector.x, y - vector.y, z - vector.z));
  }

  float& operator*(Vector& vector) {
    return *(new float(x * vector.x + y * vector.y + z * vector.z));
  }

  Vector& operator^(Vector& vector) {
    return *(new Vector(y * vector.z - vector.y * z, z * vector.x - vector.z * x, x * vector.y - vector.x * y));
  }

  bool& operator==(Vector& vector) {
    return *(new bool(x == vector.x && y == vector.y && z == vector.z));
  }

  float getLenght() {
    return Sqrt(x * x + y * y + z * z);
  }

  void print() {
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
  }
};

typedef Vector vector;

inline Vector* NormalizeVector(Vector* v) {
  return new Vector{v->x / v->getLenght(), v->y / v->getLenght(), v->z / v->getLenght()};
}

#endif

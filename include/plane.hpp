#ifndef PLANE_HPP
#define PLANE_HPP

#include "vector.hpp"
#include <tuple>

struct Plane {
private:
  Vector* p;
  Vector* u;
  Vector* v;
public:
  Vector* getFirstVector() {
    return u;
  }

  Vector* getSecondVector() {
    return v;
  }

  Vector* getPoint() {
    return p;
  }

  void setFirstVector(Vector* newU) {
    u = newU;
  }

  void setSecondVector(Vector* newV) {
    v = newV;
  }

  void setPoint(Vector* newP) {
    p = newP;
  }

  std::tuple<float, float, float, float> getCoefficients() {
    float A = getFirstVector()->y * getSecondVector()->z - getSecondVector()->y * getFirstVector()->z;
    float B = getSecondVector()->x * getFirstVector()->z - getFirstVector()->x * getSecondVector()->z;
    float C = getFirstVector()->x * getSecondVector()->y - getSecondVector()->x * getFirstVector()->y;
    float D = - A * getPoint()->x - B * getPoint()->y - C * getPoint()->z;
    return std::make_tuple(A, B, C, D);
  }

  Plane(Vector* p, Vector* u, Vector* v) : p(p), u(u), v(v) {}
};

typedef Plane plane;

#endif

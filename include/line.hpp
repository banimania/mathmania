#ifndef LINE_HPP
#define LINE_HPP

#include "vector.hpp"
#include <iostream>

struct Line {
private:
  Vector* p;
  Vector* v;
public:
  Line(Vector* p, Vector* v) : p(p), v(v) {}

  Vector* getPoint() {
    return p;
  }

  Vector* getVector() {
    return v;
  }

  Vector* getPointWithParameter(float lambda) {
    return new Vector(p->x + v->x * lambda, p->y + v->y * lambda, p->z + v->z * lambda);
  }

  void setPoint(Vector* newP) {
    p = newP;
  }

  void setVector(Vector* newV) {
    v = newV;
  }
};

typedef Line line;

inline Vector* IntersectionLineLine(Line* l1, Line* l2) {
  float lambda = ((l2->getPoint()->x - l1->getPoint()->x)/(l1->getVector()->x) + (l2->getVector()->x * l1->getPoint()->y - l2->getPoint()->y)/(l2->getVector()->y * l1->getVector()->x)) / (1 - ((l2->getVector()->x * l1->getVector()->y)/(l2->getVector()->y * l1->getVector()->x)));
  return l1->getPointWithParameter(lambda);
}

#endif

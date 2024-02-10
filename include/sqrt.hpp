#ifndef SQRT_HPP
#define SQRT_HPP

inline float Sqrt(float x) {
  float alpha = x / 1.5f;
  for (int i = 0; i < 7; i++) {
    alpha -= (alpha * alpha - x) / (2 * alpha);
  }
  return alpha;
}

#endif

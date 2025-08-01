#include "s21_math.h"

// If x is a NaN, a NaN is returned.
// If x is -0, +0 is returned.
// If x is negative infinity or positive infinity, positive infinity is
// returned.

long double s21_fabs(double x) {
  if (s21_is_nan(x)) {
    x = S21_NAN;
  } else if (s21_is_inf(x)) {
    x = S21_INF;
  } else if (0 > x) {
    x *= -1;
  }
  return x;
}

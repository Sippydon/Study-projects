#include "s21_math.h"

// If x is integral, +0, -0, NaN, or infinite, x itself is returned.

long double s21_ceil(double x) {
  long double ret = 0;
  if (s21_is_nan(x)) {
    x = S21_NAN;
    ret = x;
  } else if (!s21_is_inf(x)) {
    if (0 >= x) {
      ret = x - s21_fmod(x, 1);
    } else {
      ret = x - s21_fmod(x, 1) + (s21_fmod(x, 1) != 0);
    }
  } else {
    ret = x;
  }
  return ret;
}

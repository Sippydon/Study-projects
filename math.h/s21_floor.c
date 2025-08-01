#include "s21_math.h"

// If x is integral, +0, -0, NaN, or an infinity, x itself is returned.

long double s21_floor(double x) {
  long double ret = 0;
  if (!s21_is_nan(x) && !s21_is_inf(x)) {
    if (x > 1e+16 || x < -1e+16) {
      ret = x;
    } else if (0 <= x) {
      ret = x - s21_fmod(x, 1);
    } else {
      ret = x - s21_fmod(x, 1) - (s21_fmod(x, 1) != 0);
    }
  } else {
    ret = x;
  }
  return ret;
}

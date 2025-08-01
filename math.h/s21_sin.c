#include "s21_math.h"

long double s21_sin(double x) {
  long double res = 0, an = 0;
  if (!s21_is_nan(x) && !s21_is_inf(x)) {
    x = s21_fmod(x, S21_PI * 2);
    an = x;
    res = x;
    int i = 1;
    while (s21_fabs(an) > S21_EPS) {
      an *= -x * x / (2 * i * (2 * i + 1));
      i++;
      res += an;
    }
  } else {
    res = S21_NAN;
  }
  return res;
}

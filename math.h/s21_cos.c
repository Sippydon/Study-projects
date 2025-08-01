#include "s21_math.h"

long double s21_cos(double x) {
  long double res = 0, an = 0;
  if (!s21_is_nan(x) && !s21_is_inf(x)) {
    x = s21_fmod(x, S21_PI * 2);
    an = 1;
    int i = 1;
    while (!(an >= -S21_EPS && an <= S21_EPS)) {
      res += an;
      an *= -x * x / ((2 * i - 1) * (2 * i));
      i++;
      if (s21_is_nan(res) == 1) break;
    }
  } else {
    res = S21_NAN;
  }
  return res;
}

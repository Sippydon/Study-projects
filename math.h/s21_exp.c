#include "s21_math.h"

long double s21_exp(double x) {
  long double add_value = 1.0, series = 1, i = 1;
  int flag = 0;

  if (x < 0) {
    x = -x;
    flag = 1;
  }
  if (s21_is_nan(x) || x == S21_INF) {
    series = x;
  } else if (x == -S21_INF) {
    series = 0;
  } else {
    while (s21_fabs(add_value) > S21_EPS) {
      add_value *= (long double)x / i;
      i++;
      series += add_value;
      if (series > S21_MAX_DOUBLE) {
        series = S21_INF;
        break;
      }
    }
  }
  series = flag == 1 ? series > S21_MAX_DOUBLE ? 0 : 1. / series : series;
  return series;
}

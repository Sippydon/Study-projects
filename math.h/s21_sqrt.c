#include "s21_math.h"

int validation_sqrt_data(double x, long double *res);

long double s21_sqrt(double x) {
  long double res = 0.0;
  if (validation_sqrt_data(x, &res)) {
    for (long double i = 1.0; i != -1;) {
      double tmp = (i + x / i) / 2;
      if (s21_fabs(i - tmp) < S21_EPS) {
        break;
      }
      i = tmp;
      res = tmp;
    }
  }
  return res;
}

int validation_sqrt_data(double x, long double *res) {
  int flag = 1;

  if (x < 0 || x != x) {
    *res = S21_NAN;
    flag = 0;
  } else if (x == S21_INF) {
    *res = S21_INF;
    flag = 0;
  } else if (x == 1.0) {
    *res = 1.0;
    flag = 0;
  } else if (x == 0.0) {
    *res = 0;
    flag = 0;
  }

  return flag;
}

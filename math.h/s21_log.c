#include "s21_math.h"

int validation_log_data(double x, long double *res);

long double s21_log(double x) {
  long double res = 0;
  if (validation_log_data(x, &res)) {
    if (x == 0.0)
      res = -S21_INF;
    else if (x < 0.0)
      res = S21_NAN;
    else {
      int ex_pow = 0;
      double result = 0, compare = 0;

      for (; x >= S21_E; x /= S21_E, ex_pow++) continue;

      for (int i = 0; i < 100; i++) {
        compare = result;
        result = compare + 2 * (x - s21_exp(compare)) / (x + s21_exp(compare));
      }
      res = result + ex_pow;
    }
  }
  return res;
}

int validation_log_data(double x, long double *res) {
  int flag = 1;

  if (x == -S21_INF || s21_is_nan(x)) {
    *res = S21_NAN;
    flag = 0;
  } else if (x == S21_INF) {
    *res = S21_INF;
    flag = 0;
  } else if (x == 1.0) {
    *res = 0;
    flag = 0;
  }

  return flag;
}

#include "s21_math.h"

long double ss21_exp(long double x);
long double ss21_log(long double x);
int validation_pow_data(double base, double exp1, long double *result);

long double s21_pow(double base, double exp1) {
  long double result = 0;
  if (validation_pow_data(base, exp1, &result)) {
    if (base < 0.) {
      result = ss21_exp(exp1 * ss21_log(base));
      if (s21_fmod(exp1, 2) != 0.) result = -result;
    } else {
      result = ss21_exp(exp1 * ss21_log(base));
    }
  }
  return result;
}

long double ss21_exp(long double x) {
  long double add_value = 1.0, series = 1;
  int i = 1, flag = 0;
  x = (long double)x;
  if (x < 0) {
    x *= -1;
    flag = 1;
  }
  if (s21_is_nan(x) || x == S21_INF) {
    series = x;
  } else if (x == -S21_INF) {
    series = 0;
  } else {
    while (s21_fabs(add_value) > S21_EPS) {
      add_value *= x / i;
      i += 1;
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

long double ss21_log(long double x) {
  long double res = 0;
  if (x == S21_INF || x == -S21_INF) {
    res = S21_NAN;
  } else {
    if (x == 0)
      res = -S21_INF;
    else if (x < 0)
      res = S21_NAN;
    else {
      long double ex_pow = 0;
      long double result = 0, compare = 0;

      for (; x >= S21_E; x /= S21_E, ex_pow++) continue;

      for (int i = 0; i < 100; i++) {
        result = compare + 2 * (x - s21_exp(compare)) / (x + s21_exp(compare));
        compare = result;
      }
      res = result + ex_pow;
    }
  }
  return res;
}

int validation_pow_data(double base, double exp1, long double *result) {
  int is_valid = 1;
  if (base == 1.0 || exp1 == 0.0 ||
      ((base == -1.0) && (exp1 == S21_INF || exp1 == -S21_INF))) {
    *result = 1.0;
    is_valid = 0;
  } else if (exp1 == 1.0) {
    *result = base;
    is_valid = 0;
  } else if (base == 0.0 && exp1 > 0.0 && (exp1 - s21_floor(exp1) == 0.0)) {
    *result = 0.0;
    is_valid = 0;
  } else if (((s21_fabs(base) < 1.0) && exp1 == -S21_INF) ||
             ((s21_fabs(base) > 1.0) && exp1 == S21_INF)) {
    *result = S21_INF;
    is_valid = 0;
  } else if (((s21_fabs(base) > 1.0) && exp1 == -S21_INF) ||
             ((s21_fabs(base) < 1.0) && exp1 == S21_INF)) {
    *result = 0;
    is_valid = 0;
  } else if ((base == -S21_INF) && (exp1 - s21_floor(exp1) == 0.0) &&
             exp1 < 0.0) {
    *result = 0;
    is_valid = 0;
  } else if ((base == -S21_INF) && ((exp1 - s21_floor(exp1) == 0.0)) &&
             exp1 > 0.0 && ((int)exp1 % 2) == 0.0) {
    *result = S21_INF;
    is_valid = 0;
  } else if ((base == -S21_INF) && ((exp1 - s21_floor(exp1) == 0.0)) &&
             exp1 > 0.0 && ((int)exp1 % 2) == 1.0) {
    *result = -S21_INF;
    is_valid = 0;
  } else if (s21_is_nan(exp1)) {
    *result = S21_NAN;
    is_valid = 0;
  } else if ((base == -S21_INF) || (base == S21_INF && exp1 < 0.0)) {
    *result = 0;
    is_valid = 0;
  } else if (base == S21_INF && exp1 > 0.0) {
    *result = S21_INF;
    is_valid = 0;
  } else if (base - s21_floor(base) == 0.0 && exp1 - s21_floor(exp1) == 0.0) {
    *result = 1;
    for (int i = 0; i < s21_fabs(exp1); i++) {
      *result *= base;
    }
    if (exp1 < 0) {
      *result = 1.0 / *result;
    }
    is_valid = 0;
  } else if (base < 0.0 && exp1 == -S21_MAX_DOUBLE) {
    *result = S21_INF;
    is_valid = 0;
  }

  return is_valid;
}
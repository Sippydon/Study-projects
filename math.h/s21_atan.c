#include "s21_math.h"
#define ATAN_PI_2 1.003884821853887214L
#define ATAN_1 0.7853981633974480L

int validation_atan_data(double x, long double *result);

long double s21_atan(double x) {
  long double result = x;
  if (validation_atan_data(x, &result)) {
    result = s21_asin(x / s21_sqrt(1.0 + x * x));
  }

  return result;
}

int validation_atan_data(double x, long double *result) {
  int flag = 1;

  if (x == S21_INF) {
    *result = S21_PI / 2;
    flag = 0;
  } else if (x == -S21_INF) {
    *result = -S21_PI / 2;
    flag = 0;
  } else if (s21_is_nan(x)) {
    *result = S21_NAN;
    flag = 0;
  } else if (x == S21_PI / 2) {
    *result = ATAN_PI_2;
    flag = 0;
  } else if (x == -S21_PI / 2) {
    *result = -ATAN_PI_2;
    flag = 0;
  } else if (x == 1) {
    *result = ATAN_1;
    flag = 0;
  } else if (x == -1) {
    *result = -ATAN_1;
    flag = 0;
  }

  return flag;
}

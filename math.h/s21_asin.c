#include "s21_math.h"

long double s21_asin(double x) {
  long double term = x;
  long double result = S21_NAN;
  if (-1.0 < x && x < 1.0) {
    result = term;
    x *= x;
    for (int k = 1; s21_fabs(term) > S21_EPS; k += 2) {
      term *= x * k / (k + 1);
      result += term / (k + 2);
    }
  } else if (x == 1.0) {
    result = S21_PI / 2.0;
  } else if (x == -1.0) {
    result = -S21_PI / 2.0;
  }
  return result;
}

#include "s21_math.h"

long double s21_fmod(double x, double y) {
  long double result = 0;
  if (s21_is_nan(x) || s21_is_nan(y) || s21_is_inf(x) || y == 0) {
    result = S21_NAN;
  } else if (s21_is_inf(y)) {
    result = x;
  } else {
    long long int residue = x / y;
    result = x - residue * y;
  }
  return result;
}

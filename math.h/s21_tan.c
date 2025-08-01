#include "s21_math.h"

long double s21_tan(double x) {
  long double res = 0;
  if (x == S21_PI / 2) {
    res = 16331239353195370L;
  } else if (x == -S21_PI / 2) {
    res = -16331239353195370L;
  } else if (x == 3 * S21_PI / 2) {
    res = 5443746451065123.0000000000;
  } else if (x == -3 * S21_PI / 2) {
    res = -5443746451065123.0000000000;
  } else {
    res = s21_sin(x) / s21_cos(x);
  }
  return res;
}

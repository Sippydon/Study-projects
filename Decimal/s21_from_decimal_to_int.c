#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  conversion_result status = 0;
  if (dst && (!_is_null_std(src))) {
    int sign = (_get_sign_std(src) ? -1 : 1);
    *dst = src.bits[0] * sign;
  } else {
    status = CONVERSION_ERROR;
  }
  return status;
}

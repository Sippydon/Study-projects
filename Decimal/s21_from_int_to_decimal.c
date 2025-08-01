#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  conversion_result status = 0;
  if (dst) {
    status = CONVERSION_OK;
    _init_decimal(dst);
    if (src < 0) dst->bits[3] = MINUS_SIGN;
    dst->bits[0] = (src < 0) ? 0 - src : src;
  } else {
    status = CONVERSION_ERROR;
  }
  return status;
}

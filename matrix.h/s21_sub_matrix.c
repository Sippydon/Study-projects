#include "s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  matrix_t buffer;

  status += s21_mult_number(B, -1, &buffer);
  status += s21_sum_matrix(A, &buffer, result);

  s21_remove_matrix(&buffer);

  status = status ? CALCULATION_ERROR : OK;

  return status;
}
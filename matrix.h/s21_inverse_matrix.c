#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = OK;

  double determinant;
  s21_determinant(A, &determinant);

  if (A->rows == A->columns && determinant != 0) {
    matrix_t M, T;
    s21_calc_complements(A, &M);
    s21_transpose(&M, &T);
    s21_mult_number(&T, 1 / determinant, result);

    s21_remove_matrix(&M);
    s21_remove_matrix(&T);
  } else {
    status = CALCULATION_ERROR;
  }

  return status;
}

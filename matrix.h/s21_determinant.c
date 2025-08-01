#include "s21_matrix.h"

double get_derminant(matrix_t *A);

int s21_determinant(matrix_t *A, double *result) {
  int status = OK;

  if (A->rows == A->columns) {
    *result = get_derminant(A);
  } else {
    status = CALCULATION_ERROR;
  }

  return status;
}

double get_derminant(matrix_t *A) {
  double result = 0;

  if (A->rows != 1) {
    for (int i = 0; i < A->rows; ++i) {
      matrix_t minor;

      get_minor(A, 0, i, &minor);
      result += A->matrix[0][i] * get_derminant(&minor) * (i % 2 ? -1 : 1);

      s21_remove_matrix(&minor);
    }
  } else {
    result = A->matrix[0][0];
  }

  return result;
}
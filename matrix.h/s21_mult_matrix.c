#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;

  if (A->columns == B->rows) {
    s21_create_matrix(A->rows, B->columns, result);

    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < B->columns; ++j) {
        result->matrix[i][j] = 0;
        for (int p = 0; p < A->columns; ++p) {
          result->matrix[i][j] += A->matrix[i][p] * B->matrix[p][j];
        }
      }
    }
  } else {
    status = CALCULATION_ERROR;
  }

  return status;
}
#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = OK;

  if (A->rows == A->columns && A->rows > 1) {
    int N = A->rows;
    s21_create_matrix(N, N, result);
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        matrix_t minor;
        get_minor(A, i, j, &minor);

        double determinant;
        s21_determinant(&minor, &determinant);
        result->matrix[i][j] = determinant * ((i + j) % 2 ? -1 : 1);

        s21_remove_matrix(&minor);
      }
    }
  } else if (A->rows == A->columns && A->rows == 1) {
    s21_create_matrix(1, 1, result);
    result->matrix[0][0] = A->matrix[0][0];
  } else {
    status = CALCULATION_ERROR;
  }

  return status;
}
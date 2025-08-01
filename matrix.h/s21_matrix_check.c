#include "s21_matrix.h"

int get_minor(matrix_t *A, int x, int y, matrix_t *minor) {
  int status = OK;

  if (A->rows > 1 && A->columns > 1 && x < A->rows && y < A->columns) {
    s21_create_matrix(A->rows - 1, A->columns - 1, minor);
    int i_skip = 0;
    for (int i = 0; i < A->rows; ++i) {
      if (i == x) {
        i_skip = 1;
      } else {
        int j_skip = 0;
        for (int j = 0; j < A->columns; ++j) {
          if (j == y) {
            j_skip = 1;
          } else {
            minor->matrix[i - i_skip][j - j_skip] = A->matrix[i][j];
          }
        }
      }
    }
  } else {
    status = CALCULATION_ERROR;
  }

  return status;
}

int is_valid(matrix_t *A, matrix_t *B) {
  int is_valid = FAILURE;
  if (A->rows == B->rows && A->columns == B->columns) {
    is_valid = SUCCESS;
  }

  return is_valid;
}

int is_empty(matrix_t *matrix) {
  int status = OK;
  if (matrix == NULL || matrix->matrix == NULL || matrix->rows <= 0 ||
      matrix->columns <= 0) {
    status = INCORRECT_MATRIX;
  }

  return status;
}
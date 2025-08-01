#include "s21_matrix.h"

int epsilon_comparison(double A, double B);

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int is_equal = SUCCESS;

  if (is_valid(A, B)) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        if (!epsilon_comparison(A->matrix[i][j], B->matrix[i][j])) {
          is_equal = FAILURE;
        }
      }
    }
  } else {
    is_equal = FAILURE;
  }

  return is_equal;
}

int epsilon_comparison(double A, double B) {
  double diff;
  int result = FAILURE;

  if (A > B) {
    diff = A - B;
  } else {
    diff = B - A;
  }

  if (diff < 1e-7) {
    result = SUCCESS;
  }

  return result;
}
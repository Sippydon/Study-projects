#include "test.h"

// CREATE MATRIX
START_TEST(s21_create_matrix_0) {
  matrix_t data;
  int error_message = s21_create_matrix(1, 2, &data);

  ck_assert_int_eq(0, error_message);
  ck_assert_int_eq(1, data.rows);
  ck_assert_int_eq(2, data.columns);

  s21_remove_matrix(&data);
}
END_TEST

START_TEST(s21_create_matrix_1) {
  matrix_t data;
  int error_message = s21_create_matrix(0, 2, &data);

  ck_assert_int_eq(CALCULATION_ERROR, error_message);
}
END_TEST

START_TEST(s21_create_matrix_2) {
  matrix_t data;
  int error_message = s21_create_matrix(10, 0, &data);

  ck_assert_int_eq(CALCULATION_ERROR, error_message);
}
END_TEST

START_TEST(s21_create_matrix_3) {
  matrix_t data;
  int error_message = s21_create_matrix(-1, 7, &data);

  ck_assert_int_eq(CALCULATION_ERROR, error_message);
}
END_TEST

START_TEST(s21_create_matrix_4) {
  matrix_t data;
  int error_message = s21_create_matrix(7, -1, &data);

  ck_assert_int_eq(CALCULATION_ERROR, error_message);
}
END_TEST

// EQUALITY OF MATRIX
START_TEST(s21_eq_matrix_0) {
  matrix_t A, B;
  s21_create_matrix(1, 2, &A);
  s21_create_matrix(1, 2, &B);

  int answer = s21_eq_matrix(&A, &B);
  int true_answer = SUCCESS;

  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_1) {
  matrix_t A, B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 2, &B);

  A.matrix[0][0] = 1;
  B.matrix[0][0] = 1;

  int answer = s21_eq_matrix(&A, &B);
  int true_answer = FAILURE;

  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_2) {
  matrix_t A, B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 2, &B);

  A.matrix[0][0] = 1;
  B.matrix[0][0] = 1;

  int answer = s21_eq_matrix(&A, &B);
  int true_answer = FAILURE;

  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_3) {
  matrix_t A, B;
  s21_create_matrix(1, 2, &A);
  s21_create_matrix(1, 2, &B);

  A.matrix[0][0] = 1;
  B.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  B.matrix[0][1] = 2;

  int answer = s21_eq_matrix(&A, &B);
  int true_answer = SUCCESS;

  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_4) {
  matrix_t A, B;
  s21_create_matrix(1, 2, &A);
  s21_create_matrix(1, 2, &B);

  A.matrix[0][0] = 1;
  B.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  B.matrix[0][1] = 1010;

  int answer = s21_eq_matrix(&A, &B);
  int true_answer = FAILURE;

  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_5) {
  matrix_t A, B;
  s21_create_matrix(15, 10, &A);
  s21_create_matrix(15, 10, &B);

  for (int p = 0; p < 25; ++p) {
    for (int i = 0; i < A.rows; ++i) {
      for (int j = 0; j < A.columns; ++j) {
        int n = rand() % 100;
        A.matrix[i][j] = n;
        B.matrix[i][j] = n;
      }
    }

    int answer = s21_eq_matrix(&A, &B);
    int true_answer = SUCCESS;

    ck_assert_int_eq(answer, true_answer);
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_6) {
  matrix_t A, B;
  s21_create_matrix(1, 2, &A);
  s21_create_matrix(1, 2, &B);

  A.matrix[0][0] = 0.00000002;
  B.matrix[0][0] = 0.00000001;
  A.matrix[0][1] = 2;
  B.matrix[0][1] = 2;

  int answer = s21_eq_matrix(&A, &B);
  int true_answer = SUCCESS;

  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// SUM MATRIX
START_TEST(s21_sum_matrix_0) {
  matrix_t A, B, result;
  int rows = 1, columns = 1;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  A.matrix[0][0] = 56;
  B.matrix[0][0] = 22;

  int error = s21_sum_matrix(&A, &B, &result);
  int true_error = OK;

  matrix_t true_result;
  s21_create_matrix(rows, columns, &true_result);
  true_result.matrix[0][0] = 78;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(error, true_error);
  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

START_TEST(s21_sum_matrix_1) {
  matrix_t A, B, result;
  int rows = 1, columns = 2;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  A.matrix[0][0] = 195;
  B.matrix[0][0] = 35;
  A.matrix[0][1] = 21;
  B.matrix[0][1] = -46;

  int error = s21_sum_matrix(&A, &B, &result);
  int true_error = OK;

  matrix_t true_result;
  s21_create_matrix(rows, columns, &true_result);
  true_result.matrix[0][0] = 230;
  true_result.matrix[0][1] = -25;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(error, true_error);
  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

START_TEST(s21_sum_matrix_2) {
  matrix_t A, B, result;
  int rows = 2, columns = 1;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  A.matrix[0][0] = 101;
  B.matrix[0][0] = 1;
  A.matrix[1][0] = 0;
  B.matrix[1][0] = 0;

  int error = s21_sum_matrix(&A, &B, &result);
  int true_error = OK;

  matrix_t true_result;
  s21_create_matrix(rows, columns, &true_result);
  true_result.matrix[0][0] = 102;
  true_result.matrix[1][0] = 0;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(error, true_error);
  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

START_TEST(s21_sum_matrix_3) {
  matrix_t A, B, result;
  s21_create_matrix(10, 13, &A);
  s21_create_matrix(10, 10, &B);

  int error = s21_sum_matrix(&A, &B, &result);
  int true_error = CALCULATION_ERROR;

  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// SUB MATRIX
START_TEST(s21_sub_matrix_0) {
  matrix_t A, B, result;
  int rows = 1, columns = 1;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  A.matrix[0][0] = 56;
  B.matrix[0][0] = 22;

  int error = s21_sub_matrix(&A, &B, &result);
  int true_error = OK;

  matrix_t true_result;
  s21_create_matrix(rows, columns, &true_result);
  true_result.matrix[0][0] = 34;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(error, true_error);
  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

START_TEST(s21_sub_matrix_1) {
  matrix_t A, B, result;
  int rows = 1, columns = 2;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  A.matrix[0][0] = 195;
  B.matrix[0][0] = 35;
  A.matrix[0][1] = 21;
  B.matrix[0][1] = -46;

  int error = s21_sub_matrix(&A, &B, &result);
  int true_error = OK;

  matrix_t true_result;
  s21_create_matrix(rows, columns, &true_result);
  true_result.matrix[0][0] = 160;
  true_result.matrix[0][1] = 67;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(error, true_error);
  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

START_TEST(s21_sub_matrix_2) {
  matrix_t A, B, result;
  int rows = 2, columns = 1;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  A.matrix[0][0] = 101;
  B.matrix[0][0] = 1;
  A.matrix[1][0] = 0;
  B.matrix[1][0] = 0;

  int error = s21_sub_matrix(&A, &B, &result);
  int true_error = OK;

  matrix_t true_result;
  s21_create_matrix(rows, columns, &true_result);
  true_result.matrix[0][0] = 100;
  true_result.matrix[1][0] = 0;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(error, true_error);
  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

START_TEST(s21_sub_matrix_3) {
  matrix_t A, B, result;
  s21_create_matrix(10, 13, &A);
  s21_create_matrix(10, 10, &B);

  int error = s21_sub_matrix(&A, &B, &result);
  int true_error = CALCULATION_ERROR;

  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// MULT MUTRIX
START_TEST(s21_mult_matrix_0) {
  matrix_t A, B, result;
  int rows = 1, columns = 1;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);

  A.matrix[0][0] = 21;
  B.matrix[0][0] = -40;

  int error = s21_mult_matrix(&A, &B, &result);
  int true_error = OK;

  matrix_t true_result;
  s21_create_matrix(rows, columns, &true_result);
  true_result.matrix[0][0] = -840;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(error, true_error);
  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

START_TEST(s21_mult_matrix_1) {
  matrix_t A, B, result;
  int rows_A = 1, general = 2, columns_B = 2;
  s21_create_matrix(rows_A, general, &A);
  s21_create_matrix(general, columns_B, &B);

  //  MATRIX A
  //
  //  21  -40

  A.matrix[0][0] = 21;
  A.matrix[0][1] = -40;

  //  MATRIX B
  //
  //  1  2
  //  3  4

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 4;

  int error = s21_mult_matrix(&A, &B, &result);
  int true_error = OK;

  matrix_t true_result;
  s21_create_matrix(rows_A, columns_B, &true_result);

  //  MATRIX RESULT
  //
  //  -99  -118

  true_result.matrix[0][0] = -99;
  true_result.matrix[0][1] = -118;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(error, true_error);
  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

START_TEST(s21_mult_matrix_2) {
  matrix_t A, B, result;
  int rows_A = 2, general = 1, columns_B = 2;
  s21_create_matrix(rows_A, general, &A);
  s21_create_matrix(general, columns_B, &B);

  //  MATRIX A
  //
  //  0
  //  -1

  A.matrix[0][0] = 0;
  A.matrix[1][0] = -1;

  //  MATRIX B
  //
  //  1  2

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;

  int error = s21_mult_matrix(&A, &B, &result);
  int true_error = OK;

  matrix_t true_result;
  s21_create_matrix(rows_A, columns_B, &true_result);

  //  MATRIX RESULT
  //
  //  0  0
  //  -1 -2

  true_result.matrix[0][0] = 0;
  true_result.matrix[0][1] = 0;
  true_result.matrix[1][0] = -1;
  true_result.matrix[1][1] = -2;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(error, true_error);
  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

START_TEST(s21_mult_matrix_3) {
  matrix_t A, B, result;
  s21_create_matrix(4, 6, &A);
  s21_create_matrix(4, 4, &B);

  int error = s21_mult_matrix(&A, &B, &result);
  int true_error = CALCULATION_ERROR;

  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_mult_matrix_4) {
  matrix_t A, B, result;
  int rows_A = 3, general = 2, columns_B = 3;
  s21_create_matrix(rows_A, general, &A);
  s21_create_matrix(general, columns_B, &B);

  //  MATRIX A
  //
  //  1  4
  //  2  5
  //  3  6

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;

  //  MATRIX B
  //
  //  1  -1  1
  //  2   3  4

  B.matrix[0][0] = 1;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 3;
  B.matrix[1][2] = 4;

  int error = s21_mult_matrix(&A, &B, &result);
  int true_error = OK;

  matrix_t true_result;
  s21_create_matrix(rows_A, columns_B, &true_result);

  //  MATRIX RESULT
  //
  //   9  11  17
  //  12  13  22
  //  15  15  27

  true_result.matrix[0][0] = 9;
  true_result.matrix[0][1] = 11;
  true_result.matrix[0][2] = 17;
  true_result.matrix[1][0] = 12;
  true_result.matrix[1][1] = 13;
  true_result.matrix[1][2] = 22;
  true_result.matrix[2][0] = 15;
  true_result.matrix[2][1] = 15;
  true_result.matrix[2][2] = 27;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(error, true_error);
  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

// MULT NUMBER
START_TEST(s21_mult_number_0) {
  matrix_t A, result;
  int rows = 2, columns = 3, number = 2;
  s21_create_matrix(rows, columns, &A);

  //  MATRIX A
  //
  //  0  1  10
  //  2  3  11

  A.matrix[0][0] = 0;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 3;
  A.matrix[0][2] = 10;
  A.matrix[1][2] = 11;

  s21_mult_number(&A, number, &result);

  matrix_t true_result;
  s21_create_matrix(rows, columns, &true_result);

  //  MATRIX RESULT
  //
  //  0  2  20
  //  4  6  22

  true_result.matrix[0][0] = 0;
  true_result.matrix[0][1] = 2;
  true_result.matrix[1][0] = 4;
  true_result.matrix[1][1] = 6;
  true_result.matrix[0][2] = 20;
  true_result.matrix[1][2] = 22;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

START_TEST(s21_mult_number_1) {
  matrix_t A, result;
  int rows = 1, columns = 1, number = -10;
  s21_create_matrix(rows, columns, &A);

  //  MATRIX A
  //
  //  1

  A.matrix[0][0] = 1;

  s21_mult_number(&A, number, &result);

  matrix_t true_result;
  s21_create_matrix(rows, columns, &true_result);

  //  MATRIX RESULT
  //
  //  -10

  true_result.matrix[0][0] = -10;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

START_TEST(s21_mult_number_2) {
  matrix_t A, result;
  int rows = 2, columns = 2, number = 0;
  s21_create_matrix(rows, columns, &A);

  //  MATRIX A
  //
  //  1092  923
  //  182  123

  A.matrix[0][0] = 1092;
  A.matrix[0][1] = 923;
  A.matrix[1][0] = 182;
  A.matrix[1][1] = 123;

  s21_mult_number(&A, number, &result);

  matrix_t true_result;
  s21_create_matrix(rows, columns, &true_result);

  //  MATRIX RESULT
  //
  //  0  0
  //  0  0

  true_result.matrix[0][0] = 0;
  true_result.matrix[0][1] = 0;
  true_result.matrix[1][0] = 0;
  true_result.matrix[1][1] = 0;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

// TRANSPOSE
START_TEST(s21_transpose_0) {
  matrix_t A, result;
  int rows = 1, columns = 1;
  s21_create_matrix(rows, columns, &A);

  //  MATRIX A
  //
  //  0

  A.matrix[0][0] = 0;

  s21_transpose(&A, &result);

  matrix_t true_result;
  s21_create_matrix(rows, columns, &true_result);

  //  MATRIX RESULT
  //
  //  0

  true_result.matrix[0][0] = 0;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

START_TEST(s21_transpose_1) {
  matrix_t A, result;
  int rows = 1, columns = 2;
  s21_create_matrix(rows, columns, &A);

  //  MATRIX A
  //
  //  0  1

  A.matrix[0][0] = 0;
  A.matrix[0][1] = 1;

  s21_transpose(&A, &result);

  matrix_t true_result;
  s21_create_matrix(columns, rows, &true_result);

  //  MATRIX RESULT
  //
  //  0
  //  1

  true_result.matrix[0][0] = 0;
  true_result.matrix[1][0] = 1;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

START_TEST(s21_transpose_2) {
  matrix_t A, result;
  int rows = 2, columns = 2;
  s21_create_matrix(rows, columns, &A);

  //  MATRIX A
  //
  //  0  1
  //  2  3

  A.matrix[0][0] = 0;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 3;

  s21_transpose(&A, &result);

  matrix_t true_result;
  s21_create_matrix(columns, rows, &true_result);

  //  MATRIX RESULT
  //
  //  0  2
  //  1  3

  true_result.matrix[0][0] = 0;
  true_result.matrix[0][1] = 2;
  true_result.matrix[1][0] = 1;
  true_result.matrix[1][1] = 3;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

START_TEST(s21_transpose_3) {
  matrix_t A, result;
  int rows = 2, columns = 3;
  s21_create_matrix(rows, columns, &A);

  //  MATRIX A
  //
  //  0  1  10
  //  2  3  11

  A.matrix[0][0] = 0;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 3;
  A.matrix[0][2] = 10;
  A.matrix[1][2] = 11;

  s21_transpose(&A, &result);

  matrix_t true_result;
  s21_create_matrix(columns, rows, &true_result);

  //  MATRIX RESULT
  //
  //  0  2
  //  1  3
  //  10 11

  true_result.matrix[0][0] = 0;
  true_result.matrix[0][1] = 2;
  true_result.matrix[1][0] = 1;
  true_result.matrix[1][1] = 3;
  true_result.matrix[2][0] = 10;
  true_result.matrix[2][1] = 11;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(answer, true_answer);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

// DETERMINANT
START_TEST(s21_determinant_0) {
  matrix_t A;
  double result;
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 21;

  int error = s21_determinant(&A, &result);
  int true_error = OK;

  double true_result = 21;

  ck_assert_int_eq(error, true_error);
  ck_assert_uint_eq(result, true_result);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_1) {
  matrix_t A;
  double result;
  s21_create_matrix(2, 2, &A);

  // MATRIX A
  //
  //  1  2
  //  3  4

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  int error = s21_determinant(&A, &result);
  int true_error = OK;

  double true_result = -2;

  ck_assert_int_eq(error, true_error);
  ck_assert_uint_eq(result, true_result);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_2) {
  matrix_t A;
  double result;
  s21_create_matrix(3, 3, &A);

  // MATRIX A
  //
  //  1.123    2.001     0.12
  //  3.1203   12344.12  1023.198
  //  0.00001  1234.123  9832.826

  A.matrix[0][0] = 1.123;
  A.matrix[0][1] = 2.001;
  A.matrix[0][2] = 0.12;
  A.matrix[1][0] = 3.1203;
  A.matrix[1][1] = 12344.12;
  A.matrix[1][2] = 1023.198;
  A.matrix[2][0] = 0.00001;
  A.matrix[2][1] = 1234.123;
  A.matrix[2][2] = 9832.826;

  int error = s21_determinant(&A, &result);
  int true_error = OK;

  double true_result = 134828024.91163;
  double diff = fabs(true_result - result);

  ck_assert_int_eq(error, true_error);
  ck_assert(diff < 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_3) {
  matrix_t A;
  double result;
  s21_create_matrix(2, 3, &A);

  int error = s21_determinant(&A, &result);
  int true_error = CALCULATION_ERROR;

  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_4) {
  matrix_t A, minor;
  s21_create_matrix(1, 10, &A);

  int error = get_minor(&A, 0, 0, &minor);
  int true_error = CALCULATION_ERROR;

  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_5) {
  matrix_t A, minor;
  s21_create_matrix(6, 10, &A);

  int error = get_minor(&A, 12, 1, &minor);
  int true_error = CALCULATION_ERROR;

  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
}
END_TEST

// CALCULATE COMPONENTS
START_TEST(s21_calc_complements_0) {
  matrix_t A, result;
  int size = 3;
  s21_create_matrix(size, size, &A);

  // MATRIX A
  //
  //  1  2  3
  //  4  5  6
  //  7  8  9

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  int error = s21_calc_complements(&A, &result);
  int true_error = OK;

  matrix_t true_result;
  s21_create_matrix(size, size, &true_result);

  //  MATRIX RESULT
  //
  //  -3  6   -3
  //  6  -12  6
  //  -3  6   -3

  true_result.matrix[0][0] = -3;
  true_result.matrix[0][1] = 6;
  true_result.matrix[0][2] = -3;
  true_result.matrix[1][0] = 6;
  true_result.matrix[1][1] = -12;
  true_result.matrix[1][2] = 6;
  true_result.matrix[2][0] = -3;
  true_result.matrix[2][1] = 6;
  true_result.matrix[2][2] = -3;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(answer, true_answer);
  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

START_TEST(s21_calc_complements_1) {
  matrix_t A, result;
  int size = 2;
  s21_create_matrix(size, size, &A);

  // MATRIX A
  //
  //  1  1
  //  1  1

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 1;

  int error = s21_calc_complements(&A, &result);
  int true_error = OK;

  matrix_t true_result;
  s21_create_matrix(size, size, &true_result);

  //  MATRIX RESULT
  //
  //   1  -1
  //  -1   1

  true_result.matrix[0][0] = 1;
  true_result.matrix[0][1] = -1;
  true_result.matrix[1][0] = -1;
  true_result.matrix[1][1] = 1;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(answer, true_answer);
  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

START_TEST(s21_calc_complements_2) {
  matrix_t A, result;
  s21_create_matrix(3, 4, &A);

  int error = s21_calc_complements(&A, &result);
  int true_error = CALCULATION_ERROR;

  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_calc_complements_3) {
  matrix_t A, result;
  int size = 3;
  s21_create_matrix(size, size, &A);

  // MATRIX A
  //
  //  1  2  3
  //  0  4  2
  //  5  2  1

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  int error = s21_calc_complements(&A, &result);
  int true_error = OK;

  matrix_t true_result;
  s21_create_matrix(size, size, &true_result);

  //  MATRIX RESULT
  //
  //   0   10  -20
  //  -4  -14   -8
  //  -8    2    4

  true_result.matrix[0][0] = 0;
  true_result.matrix[0][1] = 10;
  true_result.matrix[0][2] = -20;
  true_result.matrix[1][0] = 4;
  true_result.matrix[1][1] = -14;
  true_result.matrix[1][2] = 8;
  true_result.matrix[2][0] = -8;
  true_result.matrix[2][1] = -2;
  true_result.matrix[2][2] = 4;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(answer, true_answer);
  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
  s21_remove_matrix(&true_result);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_4) {
  matrix_t A, result;
  s21_create_matrix(1, 2, &A);

  int error = s21_calc_complements(&A, &result);
  int true_error = CALCULATION_ERROR;

  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
}
END_TEST

// INVERSE MATRIX
START_TEST(s21_inverse_matrix_0) {
  matrix_t A, result;
  int size = 3;
  s21_create_matrix(size, size, &A);

  // MATRIX A
  //
  //  2   5   7
  //  6   3   4
  //  5  -2  -3

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  int error = s21_inverse_matrix(&A, &result);
  int true_error = OK;

  matrix_t true_result;
  s21_create_matrix(size, size, &true_result);

  //  MATRIX RESULT
  //
  //    1   -1    1
  //  -38   41  -34
  //   27  -29   24

  true_result.matrix[0][0] = 1;
  true_result.matrix[0][1] = -1;
  true_result.matrix[0][2] = 1;
  true_result.matrix[1][0] = -38;
  true_result.matrix[1][1] = 41;
  true_result.matrix[1][2] = -34;
  true_result.matrix[2][0] = 27;
  true_result.matrix[2][1] = -29;
  true_result.matrix[2][2] = 24;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(answer, true_answer);
  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

START_TEST(s21_inverse_matrix_1) {
  matrix_t A, result;
  s21_create_matrix(3, 4, &A);

  int error = s21_inverse_matrix(&A, &result);
  int true_error = CALCULATION_ERROR;

  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_2) {
  matrix_t A, result;
  int size = 3;
  s21_create_matrix(size, size, &A);

  // MATRIX A
  //
  //   1   2   3
  //   6   5   4
  //  -3  -6  -9

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = -3;
  A.matrix[2][1] = -6;
  A.matrix[2][2] = -9;

  int error = s21_inverse_matrix(&A, &result);
  int true_error = CALCULATION_ERROR;

  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_3) {
  matrix_t A, result;
  int size = 1;
  s21_create_matrix(size, size, &A);

  // MATRIX A
  //
  //  1

  A.matrix[0][0] = 1;

  int error = s21_inverse_matrix(&A, &result);
  int true_error = OK;

  matrix_t true_result;
  s21_create_matrix(size, size, &true_result);

  //  MATRIX RESULT
  //
  //  1

  true_result.matrix[0][0] = 1;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(answer, true_answer);
  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

Suite *s21_matrix_test(void) {
  Suite *s1 = suite_create("s21_matrix tests");

  TCase *s21_create_matrix = tcase_create("Create matrix");
  suite_add_tcase(s1, s21_create_matrix);
  tcase_add_test(s21_create_matrix, s21_create_matrix_0);
  tcase_add_test(s21_create_matrix, s21_create_matrix_1);
  tcase_add_test(s21_create_matrix, s21_create_matrix_2);
  tcase_add_test(s21_create_matrix, s21_create_matrix_3);
  tcase_add_test(s21_create_matrix, s21_create_matrix_4);

  TCase *s21_eq_matrix = tcase_create("Equality of matrix");
  suite_add_tcase(s1, s21_eq_matrix);
  tcase_add_test(s21_eq_matrix, s21_eq_matrix_0);
  tcase_add_test(s21_eq_matrix, s21_eq_matrix_1);
  tcase_add_test(s21_eq_matrix, s21_eq_matrix_2);
  tcase_add_test(s21_eq_matrix, s21_eq_matrix_3);
  tcase_add_test(s21_eq_matrix, s21_eq_matrix_4);
  tcase_add_test(s21_eq_matrix, s21_eq_matrix_5);
  tcase_add_test(s21_eq_matrix, s21_eq_matrix_6);

  TCase *s21_sum_matrix = tcase_create("Sum matrix");
  suite_add_tcase(s1, s21_sum_matrix);
  tcase_add_test(s21_sum_matrix, s21_sum_matrix_0);
  tcase_add_test(s21_sum_matrix, s21_sum_matrix_1);
  tcase_add_test(s21_sum_matrix, s21_sum_matrix_2);
  tcase_add_test(s21_sum_matrix, s21_sum_matrix_3);

  TCase *s21_sub_matrix = tcase_create("Sub matrix");
  suite_add_tcase(s1, s21_sub_matrix);
  tcase_add_test(s21_sub_matrix, s21_sub_matrix_0);
  tcase_add_test(s21_sub_matrix, s21_sub_matrix_1);
  tcase_add_test(s21_sub_matrix, s21_sub_matrix_2);
  tcase_add_test(s21_sub_matrix, s21_sub_matrix_3);

  TCase *s21_mult_matrix = tcase_create("Mult matrix");
  suite_add_tcase(s1, s21_mult_matrix);
  tcase_add_test(s21_mult_matrix, s21_mult_matrix_0);
  tcase_add_test(s21_mult_matrix, s21_mult_matrix_1);
  tcase_add_test(s21_mult_matrix, s21_mult_matrix_2);
  tcase_add_test(s21_mult_matrix, s21_mult_matrix_3);
  tcase_add_test(s21_mult_matrix, s21_mult_matrix_4);

  TCase *s21_mult_number = tcase_create("Mult number");
  suite_add_tcase(s1, s21_mult_number);
  tcase_add_test(s21_mult_number, s21_mult_number_0);
  tcase_add_test(s21_mult_number, s21_mult_number_1);
  tcase_add_test(s21_mult_number, s21_mult_number_2);

  TCase *s21_transpose = tcase_create("Transpose");
  suite_add_tcase(s1, s21_transpose);
  tcase_add_test(s21_transpose, s21_transpose_0);
  tcase_add_test(s21_transpose, s21_transpose_1);
  tcase_add_test(s21_transpose, s21_transpose_2);
  tcase_add_test(s21_transpose, s21_transpose_3);

  TCase *s21_determinant = tcase_create("Determinant");
  suite_add_tcase(s1, s21_determinant);
  tcase_add_test(s21_determinant, s21_determinant_0);
  tcase_add_test(s21_determinant, s21_determinant_1);
  tcase_add_test(s21_determinant, s21_determinant_2);
  tcase_add_test(s21_determinant, s21_determinant_3);
  tcase_add_test(s21_determinant, s21_determinant_4);
  tcase_add_test(s21_determinant, s21_determinant_5);

  TCase *s21_calc_complements = tcase_create("Calculate components");
  suite_add_tcase(s1, s21_calc_complements);
  tcase_add_test(s21_calc_complements, s21_calc_complements_0);
  tcase_add_test(s21_calc_complements, s21_calc_complements_1);
  tcase_add_test(s21_calc_complements, s21_calc_complements_2);
  tcase_add_test(s21_calc_complements, s21_calc_complements_3);
  tcase_add_test(s21_calc_complements, s21_calc_complements_4);

  TCase *s21_inverse_matrix = tcase_create("Inversr matrix");
  suite_add_tcase(s1, s21_inverse_matrix);
  tcase_add_test(s21_inverse_matrix, s21_inverse_matrix_0);
  tcase_add_test(s21_inverse_matrix, s21_inverse_matrix_1);
  tcase_add_test(s21_inverse_matrix, s21_inverse_matrix_2);
  tcase_add_test(s21_inverse_matrix, s21_inverse_matrix_3);

  return s1;
}
#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_

#include <errno.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>

#include "malloc.h"

#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2
#define SUCCESS 1
#define FAILURE 0

#define NOT_ENOUGH_MANA 3

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A,
                  matrix_t *B);  //сравнивать до 7 знака включительно
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(
    matrix_t *A,
    matrix_t *result);  //минор матрицы и матрица алгебраических дополнений
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

int get_minor(matrix_t *A, int x, int y, matrix_t *minor);
int is_valid(matrix_t *A, matrix_t *B);
int is_empty(matrix_t *matrix);

#endif  // S21_MATRIX_H_

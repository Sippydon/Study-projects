#ifndef CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_H_

#include <math.h>

#include <cstring>
#include <iostream>

#define EPS (1e-6)

class S21Matrix;
S21Matrix operator*(double value, const S21Matrix &matrix);

class S21Matrix {
 public:
  // constructors
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &o);
  S21Matrix(S21Matrix &&o) noexcept;
  ~S21Matrix();

  // operator overloads
  double &operator()(int row, int col);
  //  double &operator()(int row, int col) const;
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) noexcept;
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix operator*(double number);
  S21Matrix &operator*=(double number);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  bool operator==(const S21Matrix &other);

  // operation with matrix
  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // accessors & mutator
  void SetRows(int rows);
  void SetCols(int cols);
  int GetRows() const noexcept;
  int GetCols() const noexcept;

 private:
  int rows_, cols_;

  double **matrix_;
  void create_matrix();
  void remove_matrix();
  void matrixcpu(const S21Matrix &other) const;
  void Swap(int row1, int row2);

  S21Matrix Minor(int skip_row, int skip_col);
};

#endif  // CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_H_

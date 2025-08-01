#include "s21_matrix_oop.h"

double &S21Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_ ||
      matrix_ == nullptr) {
    throw std::out_of_range("Row or сolumn out of range or invalid matrix!");
  }
  return matrix_[row][col];
}
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  S21Matrix copy(other);
  *this = std::move(copy);
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;

  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}
S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}
S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}
S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(double number) {
  S21Matrix tmp(*this);
  tmp.MulNumber(number);
  return tmp;
}

S21Matrix operator*(const double value, const S21Matrix &matrix) {
  S21Matrix result = matrix;
  result.MulNumber(value);
  return result;
}

S21Matrix &S21Matrix::operator*=(double number) {
  MulNumber(number);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix tmp(*this);
  tmp.MulMatrix(other);
  return tmp;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }
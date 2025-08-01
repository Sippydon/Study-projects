#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

// constructors
S21Matrix::S21Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  if (rows < 0 || cols < 0) {
    throw std::out_of_range("Rows or columns less then 0!");
  }
  create_matrix();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  create_matrix();
  matrixcpu(other);
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    remove_matrix();
  }
}

// accessors & mutators
void S21Matrix::SetRows(int rows) {
  if (rows < 1) throw std::out_of_range("Row out of range!");

  S21Matrix temp = std::move(*this);
  rows_ = rows;
  cols_ = temp.cols_;
  create_matrix();
  if (rows_ >= 1 && cols_ >= 1) {
    //    rows = rows_ < temp.rows_ ? rows_ : temp.rows_;
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++)
        matrix_[i][j] = i >= temp.rows_ ? 0 : temp.matrix_[i][j];
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols < 1) throw std::out_of_range("Col out of range!");

  S21Matrix temp = std::move(*this);
  rows_ = temp.rows_;
  cols_ = cols;
  create_matrix();
  if (rows_ >= 1 && cols_ >= 1) {
    //    cols = cols_ < temp.cols_ ? cols_ : temp.cols_;
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++)
        matrix_[i][j] = j >= temp.cols_ ? 0 : temp.matrix_[i][j];
  }
}

int S21Matrix::GetRows() const noexcept { return rows_; }
int S21Matrix::GetCols() const noexcept { return cols_; }

// create && remove matrix
void S21Matrix::create_matrix() {
  if (rows_ == 0 || cols_ == 0) {
    matrix_ = nullptr;
  } else {
    matrix_ = new double *[rows_];
    int i;

    for (i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
    }
  }
}

void S21Matrix::remove_matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      if (matrix_[i] != nullptr) {
        delete[] matrix_[i];
      }
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

// other func
void S21Matrix::matrixcpu(const S21Matrix &other) const {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::Swap(int row1, int row2) {
  if (row1 != row2) {
    for (int i = 0; i < cols_; i++) {
      std::swap(matrix_[row1][i], matrix_[row2][i]);
    }
  }
}

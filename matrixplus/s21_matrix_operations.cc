#include "s21_matrix_oop.h"

// operations foo
bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool res = true;

  if (matrix_ == nullptr || other.matrix_ == nullptr) {
    throw std::invalid_argument("Invalid matrix. Matrix have NULL pointer!");
  }
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    res = false;
  }

  for (int i = 0; i < rows_ && res; i++) {
    for (int j = 0; j < cols_ && res; j++) {
      if (std::fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) {
        res = false;
      }
    }
  }

  return res;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_ || matrix_ == nullptr ||
      other.matrix_ == nullptr) {
    throw std::invalid_argument(
        "Invalid matrix. Matrix have different dimension or NULL pointer or "
        "they are not square!");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_ || matrix_ == nullptr ||
      other.matrix_ == nullptr) {
    throw std::invalid_argument(
        "Invalid matrix. Matrix have different dimension or NULL pointer or "
        "they are not square!");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (matrix_ == nullptr || other.matrix_ == nullptr || cols_ != other.rows_) {
    throw std::invalid_argument(
        "Invalid matrix. Matrix columns not equals "
        "other matrix rows or NULL pointer!");
  }

  S21Matrix result_matrix(rows_, other.cols_);

  for (int i = 0; i < result_matrix.rows_; i++) {
    for (int j = 0; j < result_matrix.cols_; j++) {
      result_matrix.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        result_matrix.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  *this = std::move(result_matrix);
}

void S21Matrix::MulNumber(const double num) {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] *= num;
      }
    }
  } else {
    throw std::invalid_argument("invalid matrix!");
  }
}

S21Matrix S21Matrix::Transpose() {
  if (matrix_ == nullptr) {
    throw std::invalid_argument("Invalid Matrix!");
  }

  S21Matrix result(cols_, rows_);

  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }

  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Invalid Matrix!");
  }

  S21Matrix res_matrix{rows_, cols_};

  for (int i = 0; i < res_matrix.rows_; i++) {
    for (int j = 0; j < res_matrix.rows_; j++) {
      S21Matrix minor = Minor(i, j);
      res_matrix(i, j) = minor.Determinant();

      if ((i + j) % 2 != 0) {
        res_matrix(i, j) *= -1;
      }
    }
  }

  return res_matrix;
}

// Эффективным методом вычисления определителя является метод Гаусса, основанный
// на том доказанном факте, что определитель треугольной матрицы (в которой все
// элементы выше или ниже главной диагонали равны нулю) равен произведению
// элементов на диагонали. Для вычисления определителя исходная матрица
// эквивалентными преобразованиями приводится к треугольному виду. После чего,
// остается лишь вычислить произведение элементов диагонали.
// https://pro-prof.com/forums/topic/gauss-determinant
double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Invalid matrix!");
  }

  double result = 1.0;
  S21Matrix tmp(*this);
  int size = rows_;

  for (int i = 0; i < size; ++i) {
    // выбираем опорный элемент
    int pivoting = i;
    for (int j = i + 1; j < size; ++j) {
      if (std::abs(tmp(j, i)) > std::abs(tmp(pivoting, i))) {
        pivoting = j;
      }
    }

    if (std::abs(tmp(pivoting, i)) < EPS) {
      return 0.0;  // TODO заменить на что-то
    }

    tmp.Swap(i, pivoting);

    result *= tmp(i, i);

    // меняем знак детерминанта если была перестановка строк
    if (i != pivoting) {
      result = -result;
    }

    // основа метода Гаусса, здесь происходит домножение на коэффицент и
    // вычитание из строк чтобы получить верхнетреуголную матрицу
    for (int j = i + 1; j < size; ++j) {
      double koef = tmp(j, i) / tmp(i, i);
      for (int k = i; k < size; ++k) {
        tmp(j, k) -= tmp(i, k) * koef;
      }
    }
  }

  return result;
}

S21Matrix S21Matrix::Minor(int skip_row, int skip_col) {
  int skip_i = 0;
  S21Matrix res_matrix(rows_ - 1, cols_ - 1);

  for (int i = 0; i < res_matrix.rows_; i++) {
    if (i == skip_row) {
      skip_i = 1;
    }

    int skip_j = 0;
    for (int j = 0; j < res_matrix.cols_; j++) {
      if (j == skip_col) {
        skip_j = 1;
      }

      res_matrix.matrix_[i][j] = matrix_[i + skip_i][j + skip_j];
    }
  }

  return res_matrix;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix not square");
  }

  double det = Determinant();

  if (std::abs(det) < EPS) {
    throw std::logic_error("Zero determinant");
  }

  S21Matrix res_matrix(rows_, cols_);
  S21Matrix tmp_matrix = CalcComplements();
  tmp_matrix = tmp_matrix.Transpose();
  res_matrix = tmp_matrix * (1 / det);

  return res_matrix;
}

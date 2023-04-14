#include "s21_matrix_oop.h"

void S21Matrix::InitMatrix() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 1 || cols_ < 1) {
    throw std::logic_error("Incorrect Matrix");
  }
  InitMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  InitMatrix();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  InitMatrix();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
    delete[] other.matrix_[i];
  }
  delete[] other.matrix_;
  other.cols_ = 0;
  other.rows_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() noexcept {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

void S21Matrix::set_cols(int cols) {
  if (cols <= 0)
    throw std::length_error(
        "It is not possible for the size of an array to be zero");

  if (cols != cols_) {
    for (int i = 0; i < rows_; ++i) {
      double* pi_tmp = new double[cols]();
      for (int j = 0; j < cols; ++j) {
        if (j < cols_) pi_tmp[j] = matrix_[i][j];
      }
      delete[] matrix_[i];
      matrix_[i] = pi_tmp;
    }
    cols_ = cols;
  }
}

void S21Matrix::set_rows(int rows) {
  if (rows <= 0)
    throw std::length_error(
        "It is not possible for the size of an array to be zero");
  if (rows_ != rows) {
    double** pi_tmp = new double*[rows];
    for (int i = 0; i < rows; ++i) {
      if (i < rows_)
        pi_tmp[i] = matrix_[i];
      else
        pi_tmp[i] = new double[cols_]();
    }
    for (int i = rows; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = pi_tmp;
    rows_ = rows;
  }
}

int S21Matrix::get_rows() const noexcept { return rows_; }

int S21Matrix::get_cols() const noexcept { return cols_; }

bool S21Matrix::CheckMatrix(const S21Matrix& other) const {
  return (other.matrix_ == nullptr && matrix_ == nullptr) ||
         other.matrix_ == nullptr;
}

bool S21Matrix::CheckMatrix() const { return matrix_ == nullptr; }

bool S21Matrix::CheckMatrixSize(const S21Matrix& other) const {
  return rows_ == other.rows_ && cols_ == other.cols_;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (CheckMatrixSize(other))
    for (int i = 0; i < rows_; ++i)
      for (int j = 0; j < cols_; ++j) {
        if (abs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) return false;
      }
  else
    return false;
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (CheckMatrix(other)) {
    throw std::logic_error("Incorrect Matrix");
  } else {
    if (CheckMatrixSize(other)) {
      for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++) matrix_[i][j] += other.matrix_[i][j];
    } else {
      throw std::logic_error("Error Calculate");
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (CheckMatrix(other)) {
    throw std::logic_error("Incorrect Matrix");
  } else {
    if (CheckMatrixSize(other)) {
      for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
    } else {
      throw std::logic_error("Error Calculate");
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (CheckMatrix()) {
    throw std::logic_error("Incorrect Matrix");
  } else {
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++) matrix_[i][j] *= num;
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (CheckMatrix(other)) {
    throw std::logic_error("Incorrect Matrix");
  } else {
    if (cols_ == other.rows_) {
      S21Matrix tmp(rows_, other.cols_);
      for (int i = 0; i < tmp.rows_; i++)
        for (int j = 0; j < tmp.cols_; j++) {
          tmp.matrix_[i][j] = 0;
          for (int m = 0; m < cols_; m++)
            tmp.matrix_[i][j] += matrix_[i][m] * other.matrix_[m][j];
        }
      *this = tmp;
    } else {
      throw std::logic_error("Error Calculate");
    }
  }
}

S21Matrix S21Matrix::Transpose() {
  if (CheckMatrix()) {
    throw std::logic_error("Incorrect Matrix");
  }
  S21Matrix tmp(cols_, rows_);
  for (int i = 0; i < tmp.rows_; ++i) {
    for (int j = 0; j < tmp.cols_; ++j) {
      tmp.matrix_[i][j] = matrix_[j][i];
    }
  }
  return tmp;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = 0;
  S21Matrix result;
  if (!CheckMatrix()) {
    det = Determinant();
    if (det != 0) {
      if (cols_ == 1) {
        result.set_rows(1);
        result.set_cols(1);
        result.matrix_[0][0] = 1.0 / matrix_[0][0];
      } else {
        S21Matrix alg, mult;
        alg = CalcComplements();
        mult = alg.Transpose();
        mult.MulNumber(1.0 / det);
        result = mult;
      }
    } else {
      throw std::logic_error("Incorrect Matrix InverseMatrix");
    }
  } else {
    throw std::logic_error("Incorrect Matrix");
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix result;
  if (CheckMatrix()) {
    throw std::logic_error("Incorrect Matrix");
  } else {
    if (cols_ == rows_) {
      result.set_cols(rows_);
      result.set_rows(cols_);
      if (cols_ == 1) {
        result.matrix_[0][0] = matrix_[0][0];
      } else if (cols_ == 2) {
        result.matrix_[0][0] = matrix_[1][1];
        result.matrix_[0][1] = -matrix_[1][0];
        result.matrix_[1][0] = -matrix_[0][1];
        result.matrix_[1][1] = matrix_[0][0];
      } else {
        for (int i = 0; i < result.cols_; i++) {
          for (int j = 0; j < result.cols_; j++) {
            result.matrix_[i][j] = GetSign(i + j) * DeterminantMinor(i, j);
          }
        }
      }
    } else {
      throw std::logic_error("Incorrect Matrix CalcComplements");
    }
  }
  return result;
}
int S21Matrix::GetSign(int i) { return ((i) % 2) == 0 ? 1 : -1; }
double S21Matrix::DeterminantMinor(int i_, int j_) {
  double out = 0;
  S21Matrix B(cols_ - 1, cols_ - 1);
  for (int i = 0; i < cols_; i++) {
    int im = i;
    if (im > i_) im--;
    for (int j = 0; j < cols_; j++) {
      int jm = j;
      if (jm > j_) jm--;
      if (i != i_ && j != j_) B.matrix_[im][jm] = matrix_[i][j];
    }
  }
  out = B.Determinant();
  return out;
}

void S21Matrix::Swap(S21Matrix& tmp, int i, int j) {
  for (int k = 0; k < tmp.cols_; k++) {
    double temp = tmp.matrix_[i][k];
    tmp.matrix_[i][k] = tmp.matrix_[j][k];
    tmp.matrix_[j][k] = temp;
  }
}

double S21Matrix::Determinant() {
  double det = 1;
  S21Matrix tmp(*this);
  for (int i = 0; i < tmp.cols_; i++) {
    int p = i;
    while (p < tmp.cols_ && tmp.matrix_[p][i] == 0) p++;

    if (p == tmp.cols_) return 0;

    if (p != i) {
      det *= -1;
      Swap(tmp, i, p);
    }
    det *= tmp.matrix_[i][i];

    for (int j = i + 1; j < tmp.cols_; j++) {
      double factor = tmp.matrix_[j][i] / tmp.matrix_[i][i];
      for (int k = i; k < tmp.cols_; k++)
        tmp.matrix_[j][k] -= factor * tmp.matrix_[i][k];
    }
  }
  det = llround(det * 1e7) / 1e7;

  return det;
}

S21Matrix& S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix& res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix& S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix& res(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this == &other) return *this;
  set_cols(other.cols_);
  set_rows(other.rows_);

  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] = other.matrix_[i][j];
  return *this;
}

double& S21Matrix::operator()(int rows, int cols) {
  if (rows >= rows_ || cols >= cols_ || cols < 0 || rows < 0)
    throw std::out_of_range("Invalid input, index exceeds valid range");
  return matrix_[rows][cols];
}

const double& S21Matrix::operator()(int rows, int cols) const {
  if (rows >= rows_ || cols >= cols_ || cols < 0 || rows < 0)
    throw std::out_of_range("Invalid input, index exceeds valid range");
  return matrix_[rows][cols];
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

S21Matrix operator*(const double num, S21Matrix& matrix) {
  S21Matrix res(matrix);
  res.MulNumber(num);
  return res;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

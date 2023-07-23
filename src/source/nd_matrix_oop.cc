#include "nd_matrix_oop.h"

void ndMatrix::InitMatrix() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

ndMatrix::ndMatrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

ndMatrix::ndMatrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 1 || cols_ < 1) {
    throw std::logic_error("Incorrect Matrix");
  }
  InitMatrix();
}

ndMatrix::ndMatrix(const ndMatrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  InitMatrix();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

ndMatrix::ndMatrix(ndMatrix&& other) {
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

ndMatrix::~ndMatrix() noexcept {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

void ndMatrix::set_cols(int cols) {
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

void ndMatrix::set_rows(int rows) {
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

int ndMatrix::get_rows() const noexcept { return rows_; }

int ndMatrix::get_cols() const noexcept { return cols_; }

bool ndMatrix::CheckMatrix(const ndMatrix& other) const {
  return (other.matrix_ == nullptr && matrix_ == nullptr) ||
         other.matrix_ == nullptr;
}

bool ndMatrix::CheckMatrix() const { return matrix_ == nullptr; }

bool ndMatrix::CheckMatrixSize(const ndMatrix& other) const {
  return rows_ == other.rows_ && cols_ == other.cols_;
}

bool ndMatrix::EqMatrix(const ndMatrix& other) const {
  if (CheckMatrixSize(other))
    for (int i = 0; i < rows_; ++i)
      for (int j = 0; j < cols_; ++j) {
        if (abs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) return false;
      }
  else
    return false;
  return true;
}

void ndMatrix::SumMatrix(const ndMatrix& other) {
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

void ndMatrix::SubMatrix(const ndMatrix& other) {
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

void ndMatrix::MulNumber(const double num) {
  if (CheckMatrix()) {
    throw std::logic_error("Incorrect Matrix");
  } else {
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++) matrix_[i][j] *= num;
  }
}

void ndMatrix::MulMatrix(const ndMatrix& other) {
  if (CheckMatrix(other)) {
    throw std::logic_error("Incorrect Matrix");
  } else {
    if (cols_ == other.rows_) {
      ndMatrix tmp(rows_, other.cols_);
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

ndMatrix ndMatrix::Transpose() {
  if (CheckMatrix()) {
    throw std::logic_error("Incorrect Matrix");
  }
  ndMatrix tmp(cols_, rows_);
  for (int i = 0; i < tmp.rows_; ++i) {
    for (int j = 0; j < tmp.cols_; ++j) {
      tmp.matrix_[i][j] = matrix_[j][i];
    }
  }
  return tmp;
}

ndMatrix ndMatrix::InverseMatrix() {
  double det = 0;
  ndMatrix result;
  if (!CheckMatrix()) {
    det = Determinant();
    if (det != 0) {
      if (cols_ == 1) {
        result.set_rows(1);
        result.set_cols(1);
        result.matrix_[0][0] = 1.0 / matrix_[0][0];
      } else {
        ndMatrix alg, mult;
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

ndMatrix ndMatrix::CalcComplements() {
  ndMatrix result;
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
int ndMatrix::GetSign(int i) { return ((i) % 2) == 0 ? 1 : -1; }
double ndMatrix::DeterminantMinor(int i_, int j_) {
  double out = 0;
  ndMatrix B(cols_ - 1, cols_ - 1);
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

void ndMatrix::Swap(ndMatrix& tmp, int i, int j) {
  for (int k = 0; k < tmp.cols_; k++) {
    double temp = tmp.matrix_[i][k];
    tmp.matrix_[i][k] = tmp.matrix_[j][k];
    tmp.matrix_[j][k] = temp;
  }
}

double ndMatrix::Determinant() {
  double det = 1;
  ndMatrix tmp(*this);
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

ndMatrix& ndMatrix::operator+(const ndMatrix& other) {
  ndMatrix& res(*this);
  res.SumMatrix(other);
  return res;
}

ndMatrix& ndMatrix::operator-(const ndMatrix& other) {
  ndMatrix& res(*this);
  res.SubMatrix(other);
  return res;
}

ndMatrix& ndMatrix::operator=(const ndMatrix& other) {
  if (this == &other) return *this;
  set_cols(other.cols_);
  set_rows(other.rows_);

  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] = other.matrix_[i][j];
  return *this;
}

double& ndMatrix::operator()(int rows, int cols) {
  if (rows >= rows_ || cols >= cols_ || cols < 0 || rows < 0)
    throw std::out_of_range("Invalid input, index exceeds valid range");
  return matrix_[rows][cols];
}

const double& ndMatrix::operator()(int rows, int cols) const {
  if (rows >= rows_ || cols >= cols_ || cols < 0 || rows < 0)
    throw std::out_of_range("Invalid input, index exceeds valid range");
  return matrix_[rows][cols];
}

ndMatrix ndMatrix::operator*(const ndMatrix& other) {
  ndMatrix res(*this);
  res.MulMatrix(other);
  return res;
}

ndMatrix ndMatrix::operator*(const double num) {
  ndMatrix res(*this);
  res.MulNumber(num);
  return res;
}

ndMatrix operator*(const double num, ndMatrix& matrix) {
  ndMatrix res(matrix);
  res.MulNumber(num);
  return res;
}

ndMatrix ndMatrix::operator*=(const ndMatrix& other) {
  MulMatrix(other);
  return *this;
}

ndMatrix ndMatrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

ndMatrix ndMatrix::operator+=(const ndMatrix& other) {
  SumMatrix(other);
  return *this;
}

ndMatrix ndMatrix::operator-=(const ndMatrix& other) {
  SubMatrix(other);
  return *this;
}

bool ndMatrix::operator==(const ndMatrix& other) { return EqMatrix(other); }

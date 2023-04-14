#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <iostream>
#include <cmath>

class S21Matrix {
public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix() noexcept;

  void set_cols(int cols);
  void set_rows(int rows);
  int get_cols() const noexcept;
  int get_rows() const noexcept;

  bool EqMatrix(const S21Matrix& other) const ;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  double Determinant();
  S21Matrix InverseMatrix();
  S21Matrix CalcComplements();

  S21Matrix& operator+(const S21Matrix& other);
  S21Matrix& operator-(const S21Matrix& other);
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);
  friend S21Matrix operator*(const double num, S21Matrix& matrix);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*=(const double num);
  double& operator()(int rows, int cols);
  const double& operator()(int rows, int cols) const;
  bool operator==(const S21Matrix& other);

private:
  int rows_, cols_;
  double **matrix_;
  void InitMatrix();
  bool CheckMatrix() const;
  bool CheckMatrix(const S21Matrix& other) const;
  bool CheckMatrixSize(const S21Matrix& other) const;
  void Swap(S21Matrix& tmp, int i, int j);
  double DeterminantMinor(int i_, int j_);
  int GetSign(int i);
};


#endif  // SRC_S21_MATRIX_OOP_H_
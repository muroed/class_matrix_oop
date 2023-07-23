#ifndef SRC_nd_MATRIX_OOP_H_
#define SRC_nd_MATRIX_OOP_H_

#include <iostream>
#include <cmath>

class ndMatrix {
public:
  ndMatrix();
  ndMatrix(int rows, int cols);
  ndMatrix(const ndMatrix& other);
  ndMatrix(ndMatrix&& other);
  ~ndMatrix() noexcept;

  void set_cols(int cols);
  void set_rows(int rows);
  int get_cols() const noexcept;
  int get_rows() const noexcept;

  bool EqMatrix(const ndMatrix& other) const ;
  void SumMatrix(const ndMatrix& other);
  void SubMatrix(const ndMatrix& other);
  void MulNumber(const double num);
  void MulMatrix(const ndMatrix& other);
  ndMatrix Transpose();
  double Determinant();
  ndMatrix InverseMatrix();
  ndMatrix CalcComplements();

  ndMatrix& operator+(const ndMatrix& other);
  ndMatrix& operator-(const ndMatrix& other);
  ndMatrix operator+=(const ndMatrix& other);
  ndMatrix operator-=(const ndMatrix& other);
  ndMatrix& operator=(const ndMatrix& other);
  ndMatrix operator*(const ndMatrix& other);
  ndMatrix operator*(const double num);
  friend ndMatrix operator*(const double num, ndMatrix& matrix);
  ndMatrix operator*=(const ndMatrix& other);
  ndMatrix operator*=(const double num);
  double& operator()(int rows, int cols);
  const double& operator()(int rows, int cols) const;
  bool operator==(const ndMatrix& other);

private:
  int rows_, cols_;
  double **matrix_;
  void InitMatrix();
  bool CheckMatrix() const;
  bool CheckMatrix(const ndMatrix& other) const;
  bool CheckMatrixSize(const ndMatrix& other) const;
  void Swap(ndMatrix& tmp, int i, int j);
  double DeterminantMinor(int i_, int j_);
  int GetSign(int i);
};


#endif  // SRC_nd_MATRIX_OOP_H_
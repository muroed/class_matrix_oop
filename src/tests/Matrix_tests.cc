#include <gtest/gtest.h>

#include "../source/nd_matrix_oop.h"

TEST(test_class, basic_constructor) {
  ndMatrix m;
  EXPECT_EQ(m.get_cols(), 0);
  EXPECT_EQ(m.get_rows(), 0);
  // EXPECT_NULL(m.matrix_);
}

TEST(test_class, rc_constructor) {
  ndMatrix m(34, 400);
  EXPECT_EQ(m.get_rows(), 34);
  EXPECT_EQ(m.get_cols(), 400);
}

TEST(test_class, operator_) {
  ndMatrix m(34, 400);
  const double al = 4;
  m(3, 3) = al;
  EXPECT_EQ(m(3, 3), 4);
}

TEST(test_class, assert_one) { ASSERT_ANY_THROW(ndMatrix m(-1, -1)); }

TEST(test_class, assert_two) {
  ndMatrix m(34, 40);
  ASSERT_ANY_THROW(m.set_rows(-1));
  ASSERT_ANY_THROW(m.set_cols(-1));
}

TEST(test_class, RowsColsConstructorTest) {
  ndMatrix m1(2, 2);
  EXPECT_EQ(2, m1.get_cols());
  EXPECT_EQ(2, m1.get_rows());
  for (int i = 0; i < m1.get_rows(); ++i)
    for (int j = 0; j < m1.get_cols(); ++j) EXPECT_DOUBLE_EQ(0, m1(i, j));
}

TEST(test_class, CopyConstructorTest) {
  ndMatrix m1(2, 2);
  m1(0, 1) = 2;
  ndMatrix m2(m1);
  EXPECT_EQ(2, m2.get_cols());
  EXPECT_EQ(2, m2.get_rows());
  for (int i = 0; i < m2.get_rows(); ++i)
    for (int j = 0; j < m2.get_cols(); ++j)
      if (i == 0 && j == 1)
        EXPECT_DOUBLE_EQ(2, m1(0, 1));
      else
        EXPECT_DOUBLE_EQ(0, m1(i, j));
}

TEST(test_class, DefaultConstructorTest) {
  ndMatrix m1;
  EXPECT_EQ(0, m1.get_cols());
  EXPECT_EQ(0, m1.get_rows());
  for (int i = 0; i < m1.get_rows(); ++i)
    for (int j = 0; j < m1.get_cols(); ++j) EXPECT_DOUBLE_EQ(0, m1(i, j));
}

TEST(test_class, MoveConstructor) {
  ndMatrix a(2, 2);
  ndMatrix c(2, 2);

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  c(0, 0) = 2;
  c(0, 1) = 4;
  c(1, 0) = 6;
  c(1, 1) = 8;

  ndMatrix b(std::move(a));

  EXPECT_TRUE(b.EqMatrix(c));
  EXPECT_EQ(a.get_rows(), 0);
  EXPECT_EQ(a.get_cols(), 0);
}

TEST(test_class, ParenthesesOperatorTest) {
  ndMatrix m1(2, 2);
  m1(0, 0) = 10;
  for (int i = 0; i < m1.get_rows(); ++i)
    for (int j = 0; j < m1.get_cols(); ++j)
      if (i == 0 && j == 0)
        EXPECT_DOUBLE_EQ(10, m1(0, 0));
      else
        EXPECT_DOUBLE_EQ(0, m1(i, j));

  ASSERT_ANY_THROW(m1(5, 5));
  ASSERT_ANY_THROW(m1(-5, -5));
}

TEST(test_class, set_rowsTest) {
  ndMatrix m1(3, 3);
  ndMatrix m2(3, 3);
  m1.set_rows(2);
  EXPECT_EQ(2, m1.get_rows());
  for (int i = 0; i < m1.get_rows(); ++i)
    for (int j = 0; j < m1.get_cols(); ++j) EXPECT_DOUBLE_EQ(0, m1(i, j));

  m2.set_rows(4);
  EXPECT_EQ(4, m2.get_rows());
  for (int i = 0; i < m2.get_rows(); ++i)
    for (int j = 0; j < m2.get_cols(); ++j) EXPECT_DOUBLE_EQ(0, m2(i, j));

  ASSERT_ANY_THROW(m1.set_rows(-1));
}

TEST(test_class, set_colsTest) {
  ndMatrix m1(3, 3);
  ndMatrix m2(3, 3);
  m1.set_cols(2);
  EXPECT_EQ(2, m1.get_cols());

  m2.set_cols(25);
  EXPECT_EQ(25, m2.get_cols());

  ASSERT_ANY_THROW(m1.set_cols(-1));
}

// TEST(test_class, constructor_throw_1) {
//   ndMatrix m1;
//   ASSERT_ANY_THROW(ndMatrix m2(std::move(m1)));
//   // m1.set_cols(2);
//   // EXPECT_EQ(2, m1.get_cols());

//   // m2.set_cols(25);
//   // EXPECT_EQ(25, m2.get_cols());

//   // ASSERT_ANY_THROW(m1.set_cols(-1));
// }

TEST(EqMatrix, EqTest) {
  ndMatrix m1(2, 2);
  ndMatrix m2(2, 2);
  m1(0, 0) = 2.4;
  m2(0, 0) = 2.4;
  m1(0, 1) = 4.8;
  m2(0, 1) = 4.8;
  m1(1, 0) = 7.2;
  m2(1, 0) = 7.2;
  m1(1, 1) = 9.6;
  m2(1, 1) = 9.6;

  EXPECT_TRUE(m1.EqMatrix(m2));
  m2(0, 1) = 10;
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(EqMatrix, EqTest_False) {
  ndMatrix m1(2, 3);
  ndMatrix m2(2, 2);

  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(EqMatrix, EqTest2) {
  ndMatrix matrix1{4, 5};
  ndMatrix matrix2{4, 5};

  matrix1(0, 0) = 561.395;
  matrix1(0, 1) = 356.219;
  matrix1(0, 2) = 356.219;
  matrix1(0, 3) = -952.484;
  matrix1(0, 4) = -506.042;

  matrix1(1, 0) = 370.469;
  matrix1(1, 1) = 356.219;
  matrix1(1, 2) = 356.219;
  matrix1(1, 3) = 441.733;
  matrix1(1, 4) = 919.346;

  matrix1(2, 0) = 113.190;
  matrix1(2, 1) = 356.219;
  matrix1(2, 2) = 356.219;
  matrix1(2, 3) = 577.491;
  matrix1(2, 4) = -770.006;

  matrix1(3, 0) = -629.533;
  matrix1(3, 1) = 356.219;
  matrix1(3, 2) = 356.219;
  matrix1(3, 3) = 370.425;
  matrix1(3, 4) = -226.376;

  matrix2(0, 0) = 561.395;
  matrix2(0, 1) = 356.219;
  matrix2(0, 2) = 356.219;
  matrix2(0, 3) = -952.484;
  matrix2(0, 4) = -506.042;

  matrix2(1, 0) = 370.469;
  matrix2(1, 1) = 356.219;
  matrix2(1, 2) = 356.219;
  matrix2(1, 3) = 441.733;
  matrix2(1, 4) = 919.346;

  matrix2(2, 0) = 113.190;
  matrix2(2, 1) = 356.219;
  matrix2(2, 2) = 356.219;
  matrix2(2, 3) = 577.491;
  matrix2(2, 4) = -770.006;

  matrix2(3, 0) = -629.533;
  matrix2(3, 1) = 356.219;
  matrix2(3, 2) = 356.219;
  matrix2(3, 3) = 370.425;
  matrix2(3, 4) = -226.376;

  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
  matrix2(3, 4) = 10;
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(SumMatrix, AddTest) {
  ndMatrix m1;
  ndMatrix m2;
  m1.set_cols(6);
  m2.set_cols(6);
  m1.set_rows(6);
  m2.set_rows(6);
  m1(0, 1) = 10;
  m2(0, 1) = 12;
  m1.SumMatrix(m2);
  EXPECT_DOUBLE_EQ(22, m1(0, 1));
  ndMatrix m3(10, 10);

  ASSERT_ANY_THROW(m1.SumMatrix(m3));
}

TEST(SumMatrix, SumMatrix_throw) {
  ndMatrix m1(2, 6);
  ndMatrix m2;

  ASSERT_ANY_THROW(m1.SumMatrix(m2));
}

TEST(SubMatrix, SubMatrix_throw) {
  ndMatrix m1(2, 6);
  ndMatrix m2;
  ndMatrix m3(6, 2);

  ASSERT_ANY_THROW(m1.SubMatrix(m2));
  ASSERT_ANY_THROW(m1.SubMatrix(m3));
}

TEST(SubMatrix, DivTest) {
  ndMatrix m1;
  ndMatrix m2;
  m1.set_cols(6);
  m2.set_cols(6);
  m1.set_rows(6);
  m2.set_rows(6);
  m1(0, 1) = 10;
  m2(0, 1) = 12;
  m1.SubMatrix(m2);
  ndMatrix m3(10, 10);
  EXPECT_DOUBLE_EQ(-2, m1(0, 1));

  ASSERT_ANY_THROW(m1.SumMatrix(m3));
}

TEST(MulNumber, MulNumberTest) {
  int number = 6;
  ndMatrix m1;
  m1.set_cols(6);
  m1.set_rows(6);
  m1(0, 1) = 10;
  m1.MulNumber(number);
  EXPECT_DOUBLE_EQ(60, m1(0, 1));
}

TEST(MulNumber, MulNumber_throw) {
  int number = 6;
  ndMatrix m1;
  ASSERT_ANY_THROW(m1.MulNumber(number));
}

TEST(MulMatrix, MulMatrix_throw) {
  ndMatrix m1;
  ndMatrix m2;
  ASSERT_ANY_THROW(m1.MulMatrix(m2));
}

TEST(MulMatrix, MulMatrixTest) {
  ndMatrix m1;
  ndMatrix m2;
  m1.set_cols(6);
  m2.set_rows(6);
  m2.set_cols(5);
  m1.set_rows(7);
  m1(0, 0) = 2;
  m1(0, 1) = 1;
  m1(1, 0) = -3;
  m1(1, 1) = 0;
  m1(2, 0) = 4;
  m1(2, 1) = -1;
  m2(0, 0) = 5;
  m2(0, 1) = -1;
  m2(0, 2) = 6;
  m2(1, 0) = -3;
  m2(1, 1) = 0;
  m2(1, 2) = 7;

  m1.MulMatrix(m2);
  EXPECT_DOUBLE_EQ(7, m1(0, 0));
  EXPECT_DOUBLE_EQ(3, m1(1, 1));
  EXPECT_DOUBLE_EQ(17, m1(2, 2));
}

TEST(Transpose, TransposeOne) {
  ndMatrix a(2, 2);
  ndMatrix b;
  ndMatrix c(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  c(0, 0) = 1;
  c(0, 1) = 3;
  c(1, 0) = 2;
  c(1, 1) = 4;

  b = a.Transpose();

  EXPECT_TRUE(b.EqMatrix(c));
}

TEST(Transpose, Transpose_throw) {
  ndMatrix a;
  ndMatrix b;

  ASSERT_ANY_THROW(b = a.Transpose());
}

TEST(InverseMatrix, InverseMatrix_throw) {
  ndMatrix a;
  ndMatrix b;

  ASSERT_ANY_THROW(b = a.InverseMatrix());
}

TEST(CalcComplements, CalcComplements_throw) {
  ndMatrix a;
  ndMatrix b;

  ASSERT_ANY_THROW(b = a.CalcComplements());
}

TEST(Transpose, TransposeTwo) {
  ndMatrix a(1, 1);
  ndMatrix b(1, 1);
  ndMatrix c(1, 1);

  a(0, 0) = 1;

  c(0, 0) = 1;

  b = a.Transpose();

  EXPECT_TRUE(b.EqMatrix(c));
}

TEST(CalcComplements, CalcComplementsOne) {
  ndMatrix a(2, 2);
  ndMatrix b;
  ndMatrix c(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  c(0, 0) = 4;
  c(0, 1) = -3;
  c(1, 0) = -2;
  c(1, 1) = 1;

  b = a.CalcComplements();
  // std::cout << c(0, 0) << "\n";
  // std::cout << c(0, 1) << "\n";
  // std::cout << c(1, 0) << "\n";
  // std::cout << c(1, 1) << "\n";
  EXPECT_TRUE(b.EqMatrix(c));
}

TEST(CalcComplements, CalcComplementsTwo) {
  ndMatrix a(1, 1);
  ndMatrix b(1, 1);
  ndMatrix c(1, 1);

  a(0, 0) = 1;

  c(0, 0) = 1;

  b = a.CalcComplements();

  EXPECT_TRUE(b.EqMatrix(c));
}

TEST(CalcComplements, CalcComplementsThree) {
  ndMatrix a(1, 2);

  EXPECT_ANY_THROW(a.CalcComplements());
}

TEST(Determinant, DeterminantOne) {
  ndMatrix a(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  double det = a.Determinant();

  EXPECT_DOUBLE_EQ(det, -2);
}

TEST(Determinant, DeterminantTwo) {
  ndMatrix a(3, 3);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 9;

  double det = a.Determinant();

  EXPECT_DOUBLE_EQ(det, 0);
}

TEST(Determinant, DeterminantThree) {
  ndMatrix a(3, 3);

  a(0, 0) = 10;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 9;

  double det = a.Determinant();

  EXPECT_DOUBLE_EQ(det, -27);
}

TEST(Determinant, DeterminantFour) {
  ndMatrix a(4, 4);

  a(0, 0) = 10;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(0, 3) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(1, 3) = 6;
  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 9;
  a(2, 3) = 9;
  a(3, 0) = 10;
  a(3, 1) = 11;
  a(3, 2) = 12;
  a(3, 3) = 13;

  double det = a.Determinant();

  EXPECT_DOUBLE_EQ(det, -27);
}

TEST(Determinant, DeterminantFive) {
  ndMatrix a(4, 4);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(0, 3) = 4;
  a(1, 0) = 5;
  a(1, 1) = 6;
  a(1, 2) = 7;
  a(1, 3) = 8;
  a(2, 0) = 9;
  a(2, 1) = 10;
  a(2, 2) = 11;
  a(2, 3) = 12;
  a(3, 0) = 13;
  a(3, 1) = 14;
  a(3, 2) = 15;
  a(3, 3) = 16;

  double det = a.Determinant();

  EXPECT_DOUBLE_EQ(det, 0);
}

TEST(InverseMatrix, InverseMatrixOne) {
  ndMatrix a(2, 2);
  ndMatrix b;
  ndMatrix c(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  c(0, 0) = -2;
  c(0, 1) = 1;
  c(1, 0) = 1.5;
  c(1, 1) = -0.5;

  b = a.InverseMatrix();
  EXPECT_TRUE(b.EqMatrix(c));
}

TEST(InverseMatrix, InverseMatrixTwo) {
  ndMatrix a(3, 3);
  ndMatrix b(3, 3);

  a(0, 0) = 10;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 9;

  b = a.InverseMatrix();

  EXPECT_DOUBLE_EQ(b(0, 0), 1. / 9);
  EXPECT_DOUBLE_EQ(b(0, 1), -2. / 9);
  EXPECT_DOUBLE_EQ(b(0, 2), 1. / 9);
  EXPECT_DOUBLE_EQ(b(1, 0), -2. / 9);
  EXPECT_DOUBLE_EQ(b(1, 1), -23. / 9);
  EXPECT_DOUBLE_EQ(b(1, 2), 16. / 9);
  EXPECT_DOUBLE_EQ(b(2, 0), 1. / 9);
  EXPECT_DOUBLE_EQ(b(2, 1), 22. / 9);
  EXPECT_DOUBLE_EQ(b(2, 2), -14. / 9);
}

TEST(InverseMatrix, InverseMatrixThree) {
  ndMatrix a(1, 1);
  ndMatrix b(1, 1);
  ndMatrix c(1, 1);

  a(0, 0) = 10;

  c(0, 0) = 1.0 / 10;

  b = a.InverseMatrix();

  EXPECT_TRUE(b.EqMatrix(c));
}

TEST(InverseMatrix, InverseMatrixThrow) {
  ndMatrix a(3, 3);
  ndMatrix b(3, 3);
  ndMatrix c(3, 3);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 9;

  EXPECT_ANY_THROW(a.InverseMatrix());
}

TEST(SumMatrix, test1) {
  ndMatrix a(2, 2);
  ndMatrix b(2, 2);
  ndMatrix c(2, 2);
  ndMatrix d;

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  c(0, 0) = 2;
  c(0, 1) = 4;
  c(1, 0) = 6;
  c(1, 1) = 8;

  d = a + b;

  EXPECT_TRUE(d.EqMatrix(c));
}

TEST(SubMatrix, test2) {
  ndMatrix a(2, 2);
  ndMatrix b(2, 2);
  ndMatrix c(2, 2);
  ndMatrix d;

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  c(0, 0) = 1;
  c(0, 1) = 2;
  c(1, 0) = 3;
  c(1, 1) = 4;

  d = a - b;

  EXPECT_TRUE(d.EqMatrix(c));
}

TEST(MulMatrix, test3) {
  ndMatrix a(2, 2);
  ndMatrix b(2, 2);
  ndMatrix c(2, 2);
  ndMatrix d;

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  c(0, 0) = 14;
  c(0, 1) = 20;
  c(1, 0) = 30;
  c(1, 1) = 44;

  d = a * b;

  EXPECT_TRUE(d.EqMatrix(c));
}

TEST(MulNumber, test4) {
  ndMatrix a(2, 2);
  ndMatrix b;
  ndMatrix c(2, 2);

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  c(0, 0) = 2.4;
  c(0, 1) = 4.8;
  c(1, 0) = 7.2;
  c(1, 1) = 9.6;

  b = a * 1.2;

  // a.PrintMatrix();
  // b.PrintMatrix();
  // c.PrintMatrix();
  EXPECT_TRUE(b.EqMatrix(c));
}

TEST(EqMatrix, test5) {
  ndMatrix a(2, 2);
  ndMatrix b(2, 2);

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  b(0, 0) = 2;
  b(0, 1) = 4;
  b(1, 0) = 6;
  b(1, 1) = 8;

  EXPECT_TRUE(a == b);
}
//
TEST(SumMatrix, test6) {
  ndMatrix a(2, 2);
  ndMatrix b(2, 2);
  ndMatrix c(2, 2);

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  c(0, 0) = 3;
  c(0, 1) = 6;
  c(1, 0) = 9;
  c(1, 1) = 12;

  a += b;

  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(SubMatrix, test7) {
  ndMatrix a(2, 2);
  ndMatrix b(2, 2);
  ndMatrix c(2, 2);

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  c(0, 0) = 1;
  c(0, 1) = 2;
  c(1, 0) = 3;
  c(1, 1) = 4;

  a -= b;

  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(MulMatrix, test8) {
  ndMatrix a(2, 2);
  ndMatrix b(2, 2);
  ndMatrix c(2, 2);

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  c(0, 0) = 14;
  c(0, 1) = 20;
  c(1, 0) = 30;
  c(1, 1) = 44;

  a *= b;

  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(MulNumber, test9) {
  ndMatrix a(2, 2);
  ndMatrix c(2, 2);

  a(0, 0) = 2;
  a(0, 1) = 6;
  a(1, 0) = 9;
  a(1, 1) = 8;

  c(0, 0) = 2.2;
  c(0, 1) = 6.6;
  c(1, 0) = 9.9;
  c(1, 1) = 8.8;

  a *= 1.1;

  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(Equal, test10) {
  ndMatrix a(2, 2);
  ndMatrix c(2, 2);

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  a = c;

  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(MulNumber, test11) {
  ndMatrix a(2, 2);
  ndMatrix b;
  ndMatrix c(2, 2);

  a(0, 0) = 2;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 8;

  c(0, 0) = 2.4;
  c(0, 1) = 4.8;
  c(1, 0) = 7.2;
  c(1, 1) = 9.6;

  b = 1.2 * a;

  EXPECT_TRUE(b.EqMatrix(c));
}

TEST(Determinant, DeterminantSix) {
  ndMatrix matrix1{5, 5};

  matrix1(0, 0) = 561.395;
  matrix1(0, 1) = 356.219;
  matrix1(0, 2) = 356.219;
  matrix1(0, 3) = -952.484;
  matrix1(0, 4) = -506.042;

  matrix1(1, 0) = 370.469;
  matrix1(1, 1) = 356.219;
  matrix1(1, 2) = 356.219;
  matrix1(1, 3) = 441.733;
  matrix1(1, 4) = 919.346;

  matrix1(2, 0) = 113.190;
  matrix1(2, 1) = 356.219;
  matrix1(2, 2) = 356.219;
  matrix1(2, 3) = 577.491;
  matrix1(2, 4) = -770.006;

  matrix1(3, 0) = -629.533;
  matrix1(3, 1) = 356.219;
  matrix1(3, 2) = 356.219;
  matrix1(3, 3) = 370.425;
  matrix1(3, 4) = -226.376;

  matrix1(4, 0) = 964.659;
  matrix1(4, 1) = 356.219;
  matrix1(4, 2) = 356.219;
  matrix1(4, 3) = 907.791;
  matrix1(4, 4) = 679.804;

  double det = matrix1.Determinant();
  EXPECT_NEAR(det, 0, 0.02);
}

void randm(ndMatrix &m) {
  for (int i = 0; i < m.get_rows(); i++)
    for (int j = 0; j < m.get_cols(); j++) m(i, j) = rand() % 10;
}

void printm(ndMatrix &m) {
  for (int i = 0; i < m.get_rows(); i++) {
    for (int j = 0; j < m.get_cols(); j++) std::cout << m(i, j) << " ";
    std::cout << std::endl;
  }
}

TEST(EqMatrix, EqMatrix_1) {
  ndMatrix josky, flex;
  for (int i = 0; i < josky.get_rows(); i++) {
    for (int j = 0; j < josky.get_cols(); j++) {
      josky(i, j) = 1;
      flex(i, j) = 1;
    }
  }
  EXPECT_TRUE(josky.EqMatrix(flex));
}

TEST(EqMatrix, EqMatrix_2) {
  ndMatrix josky(3, 3), flex(3, 3);
  josky(2, 2) = 1;
  EXPECT_FALSE(josky.EqMatrix(flex));
}

TEST(SumMatrix, SumMatrix_1) {
  ndMatrix josky(2, 2);
  josky(0, 0) = 2;
  josky(0, 1) = 4;
  josky(1, 0) = 6;
  josky(1, 1) = 8;
  ndMatrix flex = josky * 2;
  josky.SumMatrix(josky);
  EXPECT_TRUE(josky.EqMatrix(flex));
}

TEST(SumMatrix, SumMatrix_2) {
  ndMatrix josky(2, 3), flex(2, 2);

  EXPECT_THROW(josky.SumMatrix(flex);, std::logic_error);
}

TEST(SubMatrix, SubMatrix_1) {
  ndMatrix josky(2, 2), flex(2, 2);
  josky(0, 0) = 2;
  josky(0, 1) = 4;
  josky(1, 0) = 6;
  josky(1, 1) = 8;
  josky.SubMatrix(josky);
  EXPECT_TRUE(josky.EqMatrix(flex));
}

TEST(SubMatrix, SubMatrix_2) {
  ndMatrix josky(2, 2), flex(2, 2);
  josky(0, 0) = 2;
  josky(0, 1) = 4;
  josky(1, 0) = 6;
  josky(1, 1) = 8;
  flex.SubMatrix(josky);
  josky *= -1;
  EXPECT_TRUE(josky.EqMatrix(flex));
}

TEST(MulNumber, MulNumber_1) {
  ndMatrix josky(2, 2), flex(2, 2);
  josky(0, 0) = 2;
  josky(0, 1) = 4;
  josky(1, 0) = 6;
  josky(1, 1) = 8;
  flex = josky;
  josky.MulNumber(2);
  flex += flex;
  EXPECT_TRUE(josky.EqMatrix(flex));
}

TEST(MulNumber, MulNumber_2) {
  ndMatrix josky(2, 2), flex(2, 2);
  josky(0, 0) = 2;
  josky(0, 1) = 4;
  josky(1, 0) = 6;
  josky(1, 1) = 8;
  josky.MulNumber(0);
  EXPECT_TRUE(josky.EqMatrix(flex));
}

TEST(MulMatrix, MulMatrix_1) {
  ndMatrix josky(2, 3), flex(3, 2);
  double count = 1;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      josky(i, j) = count;
      flex(j, i) = count;
      count++;
    }
  }
  josky.MulMatrix(flex);
  ndMatrix res(2, 2);
  res(0, 0) = 14;
  res(0, 1) = 32;
  res(1, 0) = 32;
  res(1, 1) = 77;
  EXPECT_TRUE(josky.EqMatrix(res));
}

TEST(MulMatrix, MulMatrix_2) {
  ndMatrix josky(2, 3), flex(4, 2);
  double count = 1;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      josky(i, j) = count;
      flex(j, i) = count;
      count++;
    }
  }
  EXPECT_THROW(josky.MulMatrix(flex), std::logic_error);
}

TEST(Transpose, Transpose_1) {
  ndMatrix josky(2, 3), flex(3, 2);
  double count = 1;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      josky(i, j) = count;
      flex(j, i) = count;
      count++;
    }
  }
  josky = josky.Transpose();
  EXPECT_TRUE(josky.EqMatrix(flex));
}

TEST(Transpose, Transpose_2) {
  ndMatrix josky(2, 3), flex(3, 2);
  double count = 1;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      josky(i, j) = count;
      flex(j, i) = count;
      count++;
    }
  }
  flex = flex.Transpose();
  EXPECT_TRUE(josky.EqMatrix(flex));
}

TEST(CalcComplements, CalcComplements_1) {
  ndMatrix josky(2, 2), flex(2, 2);
  int count = 1;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      josky(i, j) = count;
      count++;
    }
  }
  josky = josky.CalcComplements();
  flex(0, 0) = 4;
  flex(0, 1) = -3;
  flex(1, 0) = -2;
  flex(1, 1) = 1;
  EXPECT_TRUE(josky.EqMatrix(flex));
}

TEST(Determinant, Determinant_1) {
  ndMatrix josky(3, 3);
  int count = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      josky(i, j) = count;
      count++;
    }
  }
  EXPECT_DOUBLE_EQ(0, josky.Determinant());
}

TEST(Determinant, Determinant_2) {
  ndMatrix josky(3, 3);
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      josky(i, j) = count;
      count += i + j;
    }
    count *= 2;
  }
  EXPECT_DOUBLE_EQ(-12, josky.Determinant());
}

TEST(InverseMatrix, Inverse_1) {
  ndMatrix josky(2, 2), flex(2, 2);
  int count = 1;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      josky(i, j) = count;
      count++;
    }
  }
  josky = josky.InverseMatrix();
  flex(0, 0) = -2;
  flex(0, 1) = 1;
  flex(1, 0) = 1.5;
  flex(1, 1) = -0.5;
  EXPECT_TRUE(josky.EqMatrix(flex));
}

TEST(InverseMatrix, Inverse_2) {
  ndMatrix josky(2, 2), flex(2, 2);
  josky(0, 0) = 1;
  josky(0, 1) = 1;
  josky(1, 0) = 3;
  josky(1, 1) = 2;
  josky = josky.InverseMatrix();
  flex(0, 0) = -2;
  flex(0, 1) = 1;
  flex(1, 0) = 3;
  flex(1, 1) = -1;
  EXPECT_TRUE(josky.EqMatrix(flex));
}

TEST(test_class, get_t1) {
  ndMatrix m1(2, 2);
  m1(1, 1) = 123.456;
  EXPECT_EQ(m1.get_cols(), 2);
  EXPECT_EQ(m1.get_rows(), 2);
  EXPECT_DOUBLE_EQ(m1(1, 1), 123.456);
}

TEST(test_class, set_t1) {
  ndMatrix m(2, 2);
  m(1, 1) = 123.456;
  m.set_cols(3);
  m(1, 2) = 999.999;
  EXPECT_EQ(m.get_cols(), 3);
  EXPECT_DOUBLE_EQ(m(1, 1), 123.456);
  EXPECT_DOUBLE_EQ(m(1, 2), 999.999);
}

TEST(test_class, set_t2) {
  ndMatrix m1(2, 2);
  m1(1, 0) = 123.456;
  m1.set_rows(3);
  m1(2, 0) = m1(1, 0);
  EXPECT_EQ(m1.get_rows(), 3);
  EXPECT_EQ(m1.get_cols(), 2);
  EXPECT_DOUBLE_EQ(m1(1, 0), m1(2, 0));
}

TEST(test_class, constructor_t1) {
  ndMatrix m1;
  EXPECT_EQ(m1.get_cols(), 0);
  EXPECT_EQ(m1.get_rows(), 0);

  ndMatrix m2(5, 5);
  m2(1, 1) = 123.456;
  EXPECT_EQ(m2.get_cols(), 5);
  EXPECT_EQ(m2.get_rows(), 5);

  ndMatrix m3(m2);
  EXPECT_EQ(m2 == m3, true);

  ndMatrix m4(std::move(m3));
  EXPECT_EQ(m3.get_cols(), 0);
  EXPECT_EQ(m3.get_rows(), 0);
  EXPECT_EQ(m4.get_rows(), 5);
  EXPECT_EQ(m4.get_cols(), 5);
  EXPECT_EQ(m4(1, 1), m2(1, 1));
}

TEST(test_class, eq) {
  ndMatrix m1(123, 123);
  ndMatrix m2(m1);

  EXPECT_EQ(m1.EqMatrix(m2), true);
}

TEST(SumMatrix, summat) {
  ndMatrix m1(3, 3);
  ndMatrix m2(3, 3);

  m1(0, 0) = 1;
  m1(0, 2) = 2;
  m1(2, 0) = 3;

  m2.SumMatrix(m1);

  EXPECT_EQ(m2(0, 0), 1);
  EXPECT_EQ(m2(0, 2), 2);
  EXPECT_EQ(m2(2, 0), 3);
}

TEST(SubMatrix, submat) {
  ndMatrix m1(3, 3);
  ndMatrix m2(3, 3);

  m1(0, 0) = 1;
  m1(0, 2) = 2;
  m1(2, 0) = 3;

  m2.SubMatrix(m1);

  EXPECT_EQ(m2(0, 0), -1);
  EXPECT_EQ(m2(0, 2), -2);
  EXPECT_EQ(m2(2, 0), -3);
}

TEST(MulNumber, mulnum) {
  ndMatrix m2(3, 3);

  m2(0, 0) = 1.3;
  m2(0, 2) = 2.1;
  m2(2, 0) = 3.3;

  m2.MulNumber(0.412);

  EXPECT_EQ(m2(0, 0), 1.3 * 0.412);
  EXPECT_EQ(m2(0, 2), 2.1 * 0.412);
  EXPECT_EQ(m2(2, 0), 3.3 * 0.412);
}

TEST(MulMatrix, mulmat) {
  ndMatrix m1(2, 1);
  ndMatrix m2(1, 2);

  m1(0, 0) = 32;
  m1(1, 0) = 12;

  m2(0, 0) = 2;
  m2(0, 1) = 3;

  m1.MulMatrix(m2);

  EXPECT_DOUBLE_EQ(m1(0, 0), 32 * 2);
  EXPECT_DOUBLE_EQ(m1(1, 1), 12 * 3);
}

TEST(Transpose, transpose) {
  int rows = 2;
  int cols = 3;

  ndMatrix m(rows, cols);
  ndMatrix res(cols, rows);
  int c = 1;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m(i, j) = c;
      res(j, i) = c;
      c++;
    }
  }

  m = m.Transpose();

  ASSERT_TRUE(m == res);
}

TEST(func7, calccal) {
  ndMatrix m(3, 12);
  EXPECT_ANY_THROW(m.CalcComplements());
}

TEST(CalcComplements, calcalc) {
  int rows = 3;
  int cols = 3;

  ndMatrix given(rows, cols);
  ndMatrix expected(rows, cols);

  given(0, 0) = 1.0;
  given(0, 1) = 2.0;
  given(0, 2) = 3.0;
  given(1, 0) = 0.0;
  given(1, 1) = 4.0;
  given(1, 2) = 2.0;
  given(2, 0) = 5.0;
  given(2, 1) = 2.0;
  given(2, 2) = 1.0;

  expected(0, 0) = 0.0;
  expected(0, 1) = 10.0;
  expected(0, 2) = -20.0;
  expected(1, 0) = 4.0;
  expected(1, 1) = -14.0;
  expected(1, 2) = 8.0;
  expected(2, 0) = -8.0;
  expected(2, 1) = -2.0;
  expected(2, 2) = 4.0;

  ndMatrix res = given.CalcComplements();

  ASSERT_TRUE(res == expected);
}

TEST(Determinant, det) {
  ndMatrix m(5, 5);

  for (uint32_t i = 0; i < 5; i++)
    for (uint32_t j = 0; j < 5; j++) m(i, j) = j;

  ASSERT_NEAR(0, m.Determinant(), 1e-06);
}

TEST(Determinant, det1) {
  int size = 5;
  ndMatrix m(size, size);

  m(0, 1) = 6;
  m(0, 2) = -2;
  m(0, 3) = -1;
  m(0, 4) = 5;
  m(1, 3) = -9;
  m(1, 4) = -7;
  m(2, 1) = 15;
  m(2, 2) = 35;
  m(3, 1) = -1;
  m(3, 2) = -11;
  m(3, 3) = -2;
  m(3, 4) = 1;
  m(4, 0) = -2;
  m(4, 1) = -2;
  m(4, 2) = 3;
  m(4, 4) = -2;

  double res = m.Determinant();
  ASSERT_NEAR(res, 2480, 1e-6);
}

TEST(Determinant, det2) {
  int size = 3;
  ndMatrix m(size, size);

  m(0, 0) = 2;
  m(0, 1) = 3;
  m(0, 2) = 1;
  m(1, 0) = 7;
  m(1, 1) = 4;
  m(1, 2) = 1;
  m(2, 0) = 9;
  m(2, 1) = -2;
  m(2, 2) = 1;

  double res = m.Determinant();
  ASSERT_NEAR(res, -32, 1e-6);
}

TEST(InverseMatrix, inverse) {
  int size = 3;
  ndMatrix given(size, size);
  ndMatrix expected(size, size);

  expected(0, 0) = 44300.0 / 367429.0;
  expected(0, 1) = -236300.0 / 367429.0;
  expected(0, 2) = 200360.0 / 367429.0;
  expected(1, 0) = 20600.0 / 367429.0;
  expected(1, 1) = 56000.0 / 367429.0;
  expected(1, 2) = -156483.0 / 367429.0;
  expected(2, 0) = 30900.0 / 367429.0;
  expected(2, 1) = 84000.0 / 367429.0;
  expected(2, 2) = -51010.0 / 367429.0;

  given(0, 0) = 2.8;
  given(0, 1) = 1.3;
  given(0, 2) = 7.01;
  given(1, 0) = -1.03;
  given(1, 1) = -2.3;
  given(1, 2) = 3.01;
  given(2, 0) = 0;
  given(2, 1) = -3;
  given(2, 2) = 2;

  ASSERT_TRUE(given.InverseMatrix() == expected);
}

TEST(InverseMatrix, iverse1) {
  int size = 3;
  ndMatrix given(size, size);
  ndMatrix expected(size, size);
  expected(0, 0) = 1.0;
  expected(0, 1) = -1.0;
  expected(0, 2) = 1.0;
  expected(1, 0) = -38.0;
  expected(1, 1) = 41.0;
  expected(1, 2) = -34.0;
  expected(2, 0) = 27.0;
  expected(2, 1) = -29.0;
  expected(2, 2) = 24.0;

  given(0, 0) = 2.0;
  given(0, 1) = 5.0;
  given(0, 2) = 7.0;
  given(1, 0) = 6.0;
  given(1, 1) = 3.0;
  given(1, 2) = 4.0;
  given(2, 0) = 5.0;
  given(2, 1) = -2.0;
  given(2, 2) = -3.0;
  ASSERT_TRUE(given.InverseMatrix() == expected);
}

TEST(test_class, first) {
  ndMatrix m;
  EXPECT_EQ(m.get_cols(), 0);
  EXPECT_EQ(m.get_rows(), 0);
}

TEST(test_class, second) {
  ndMatrix m(11, 11);
  EXPECT_EQ(m.get_cols(), 11);
  EXPECT_EQ(m.get_rows(), 11);
  EXPECT_EQ(m(10, 10), 0);
}

TEST(test_class, mul) {
  ndMatrix m1(3, 3);
  ndMatrix m2(3, 3);

  for (int i = 0; i < m1.get_rows(); ++i)
    for (int j = 0; j < m1.get_cols(); ++j) {
      m1(i, j) = (i + 1) * j + 1;
      m2(i, j) = (i + 1) * j + 1;
    }

  m1.MulMatrix(m2);
  EXPECT_EQ(3, m1.get_cols());
  EXPECT_EQ(3, m1.get_rows());
  for (int i = 0; i < m1.get_rows(); ++i)
    for (int j = 0; j < m1.get_cols(); ++j)
      if (j == 0)
        EXPECT_DOUBLE_EQ(6 + 3 * i, m1(i, j));
      else if (j == 1)
        EXPECT_DOUBLE_EQ(20 + 11 * i, m1(i, j));
      else
        EXPECT_DOUBLE_EQ(34 + 19 * i, m1(i, j));

  ndMatrix m3(3, 1);
  ASSERT_ANY_THROW(m3.MulMatrix(m2));

  for (int i = 0; i < m3.get_rows(); ++i) m3(i, 0) = 2;
  m2.MulMatrix(m3);
  EXPECT_EQ(1, m2.get_cols());
  EXPECT_EQ(3, m2.get_rows());
  for (int i = 0; i < m2.get_rows(); ++i)
    EXPECT_DOUBLE_EQ(12 + 6 * i, m2(i, 0));
}

TEST(test_class, third) {
  ndMatrix m1(123, 123);

  ndMatrix m2(m1);

  EXPECT_EQ(m1.get_cols(), m2.get_cols());
  EXPECT_EQ(m1.get_rows(), m2.get_rows());
}

TEST(test_class, fourth) {
  ndMatrix m1(123, 123);

  ndMatrix m2(std::move(m1));

  EXPECT_EQ(m1.get_cols(), 0);
  EXPECT_EQ(m1.get_rows(), 0);
  EXPECT_EQ(m2.get_cols(), 123);
  EXPECT_EQ(m2.get_rows(), 123);
}

TEST(leaks, gg) {
  int rows = 3;
  int cols = 3;
  ndMatrix given(rows, cols);
  ndMatrix expected(rows, cols);

  given(0, 0) = 1.0;
  given(0, 1) = 2.0;
  given(0, 2) = 3.0;
  given(1, 0) = 4.0;
  given(1, 1) = 5.0;
  given(1, 2) = 6.0;
  given(2, 0) = 7.0;
  given(2, 1) = 8.0;
  given(2, 2) = 9.0;
  given.set_rows(4);

  given.set_rows(2);
  given.set_cols(2);

  expected(0, 0) = 10.0;
  expected(0, 1) = 11.0;
  expected(0, 2) = 12.0;
  expected(1, 0) = 13.0;
  expected(1, 1) = 14.0;
  expected(1, 2) = 15.0;
  expected(2, 0) = 16.0;
  expected(2, 1) = 17.0;
  expected(2, 2) = 18.0;
  expected.set_cols(4);

  expected.set_cols(2);
  expected.set_rows(2);

  ndMatrix oper_Sum = given + expected;
  ndMatrix oper_Sub = given - expected;
  ndMatrix oper_MulNM = 10 * given;
  ndMatrix oper_MulMN = given * 10;
  ndMatrix oper_MulM = given * expected;
  ndMatrix Sum(2, 2);
  Sum += given;
  ndMatrix Sub(2, 2);
  Sub -= given;
  ndMatrix MulN(2, 2);
  MulN *= 10;
  ndMatrix MulM(2, 2);
  MulM *= given;
  ndMatrix func_sum(2, 2);
  func_sum.SumMatrix(given);
  ndMatrix func_sub(2, 2);
  func_sub.SubMatrix(given);
  ndMatrix func_muln(2, 2);
  func_muln.MulNumber(10);
  ndMatrix func_mulm(2, 2);
  func_mulm.MulMatrix(given);
  ndMatrix func_trans(2, 2);
  func_trans = given.Transpose();
  ndMatrix func_inverse(2, 2);
  func_inverse = given.InverseMatrix();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
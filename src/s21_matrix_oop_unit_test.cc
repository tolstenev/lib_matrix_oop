#include <gtest/gtest.h>

#include <iostream>

#include "s21_matrix_oop.h"

TEST(AccessorMutator, GetRowsColsSuccess) {
  S21Matrix matrix(3, 2);

  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 2);
}

TEST(Constructors, ParameterizedSuccess) {
  S21Matrix matrix(3, 4);

  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 4);
}

TEST(Constructors, ParameterizedRowsFail) {
  EXPECT_ANY_THROW(S21Matrix matrix(0, 1));
}

TEST(Constructors, ParameterizedColsFail) {
  EXPECT_ANY_THROW(S21Matrix matrix(1, 0));
}

TEST(Constructors, DefaultSuccess) {
  S21Matrix matrix;

  EXPECT_GE(matrix.GetRows(), 0);
  EXPECT_GE(matrix.GetCols(), 0);
}

TEST(Constructors, CopySuccess) {
  S21Matrix matrix_1(2, 1);
  S21Matrix matrix_2(matrix_1);

  EXPECT_EQ(matrix_2.GetRows(), 2);
  EXPECT_EQ(matrix_2.GetCols(), 1);
  EXPECT_EQ(matrix_2.EqMatrix(matrix_1), true);
}

TEST(Constructors, MoveSuccess) {
  S21Matrix matrix_1(2, 1);
  S21Matrix matrix_2(std::move(matrix_1));

  EXPECT_EQ(matrix_2.GetRows(), 2);
  EXPECT_EQ(matrix_2.GetCols(), 1);
  EXPECT_EQ(matrix_1.GetRows(), 0);
  EXPECT_EQ(matrix_1.GetCols(), 0);
}

TEST(Other, IndexingSuccess) {
  S21Matrix matrix_1(2, 2);

  EXPECT_NO_THROW(matrix_1(1, 1));
  EXPECT_NO_THROW(matrix_1(1, 1) = 21.0);
  EXPECT_DOUBLE_EQ(matrix_1(1, 1), 21.0);
}

TEST(Other, IndexingException) {
  S21Matrix matrix_1(2, 2);

  ASSERT_ANY_THROW(matrix_1(3, 3));
}

TEST(Comparing, EqMatrixTrue) {
  S21Matrix matrix_1(3, 2);
  S21Matrix matrix_2(3, 2);

  matrix_1(0, 0) = 1.0;
  matrix_1(0, 1) = 2.0;
  matrix_1(1, 0) = 3.0;
  matrix_1(1, 1) = 4.0;
  matrix_1(2, 0) = 5.0;
  matrix_1(2, 1) = 6.0;

  matrix_2(0, 0) = 1.0;
  matrix_2(0, 1) = 2.0;
  matrix_2(1, 0) = 3.0;
  matrix_2(1, 1) = 4.0;
  matrix_2(2, 0) = 5.0;
  matrix_2(2, 1) = 6.0;

  EXPECT_EQ(matrix_1.EqMatrix(matrix_2), true);
}

TEST(Comparing, EqMatrixFalse1) {
  S21Matrix matrix_1(3, 2);
  S21Matrix matrix_2(3, 2);

  matrix_2(0, 0) = 21.00001;
  matrix_2(0, 1) = 2.0;
  matrix_2(1, 0) = 3.0;
  matrix_2(1, 1) = 4.0;
  matrix_2(2, 0) = 5.0;
  matrix_2(2, 1) = 6.0;

  EXPECT_EQ(matrix_1.EqMatrix(matrix_2), false);
}

TEST(Comparing, EqMatrixFalse2) {
  S21Matrix matrix_1(2, 1);
  matrix_1(0, 0) = 1.0;
  matrix_1(1, 0) = 2.0;
  S21Matrix matrix_2(1, 2);
  matrix_2(0, 0) = 1.0;
  matrix_2(0, 1) = 2.0;

  EXPECT_EQ(matrix_1.EqMatrix(matrix_2), false);
}

TEST(Calculations, SumMatrixSuccess) {
  S21Matrix matrix_1(2, 2);
  matrix_1(0, 0) = 1.0;
  matrix_1(0, 1) = 2.0;
  matrix_1(1, 0) = 3.0;
  matrix_1(1, 1) = 4.0;
  S21Matrix matrix_2(2, 2);
  matrix_2(0, 0) = 1.0;
  matrix_2(0, 1) = 2.0;
  matrix_2(1, 0) = 3.0;
  matrix_2(1, 1) = 4.0;

  matrix_1.SumMatrix(matrix_2);

  EXPECT_DOUBLE_EQ(matrix_1(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(matrix_1(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix_1(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix_1(1, 1), 8.0);
}

TEST(Calculations, SumMatrixException) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(1, 1);

  EXPECT_ANY_THROW(matrix_1.SumMatrix(matrix_2));
}

TEST(Calculations, SubMatrixSuccess) {
  S21Matrix matrix_1(2, 2);
  matrix_1(0, 0) = 1.0;
  matrix_1(0, 1) = 2.0;
  matrix_1(1, 0) = 3.0;
  matrix_1(1, 1) = 4.0;
  S21Matrix matrix_2(2, 2);
  matrix_2(0, 0) = 1.0;
  matrix_2(0, 1) = 2.0;
  matrix_2(1, 0) = 3.0;
  matrix_2(1, 1) = 4.0;

  matrix_1.SubMatrix(matrix_2);

  EXPECT_DOUBLE_EQ(matrix_1(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix_1(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(matrix_1(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix_1(1, 1), 0.0);
}

TEST(Calculations, SubMatrixException) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(1, 1);

  EXPECT_ANY_THROW(matrix_1.SubMatrix(matrix_2));
}

TEST(Calculations, MulNumberSuccess) {
  S21Matrix matrix_1(2, 2);
  matrix_1(0, 0) = 1.0;
  matrix_1(0, 1) = 2.0;
  matrix_1(1, 0) = 3.0;
  matrix_1(1, 1) = 4.0;

  matrix_1.MulNumber(2.0);

  EXPECT_DOUBLE_EQ(matrix_1(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(matrix_1(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix_1(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix_1(1, 1), 8.0);
}

TEST(Calculations, MulMatrixSuccess) {
  S21Matrix matrix_1(3, 1);
  matrix_1(0, 0) = 0.5;
  matrix_1(1, 0) = -42;
  matrix_1(2, 0) = 21;
  S21Matrix matrix_2(1, 3);
  matrix_2(0, 0) = 4.8;
  matrix_2(0, 1) = 15.16;
  matrix_2(0, 2) = 23.42;

  matrix_1.MulMatrix(matrix_2);

  S21Matrix result(3, 3);
  EXPECT_DOUBLE_EQ(matrix_1(0, 0), 2.4);
  EXPECT_DOUBLE_EQ(matrix_1(0, 1), 7.58);
  EXPECT_DOUBLE_EQ(matrix_1(0, 2), 11.71);
  EXPECT_DOUBLE_EQ(matrix_1(1, 0), -201.6);
  EXPECT_DOUBLE_EQ(matrix_1(1, 1), -636.72);
  EXPECT_DOUBLE_EQ(matrix_1(1, 2), -983.64);
  EXPECT_DOUBLE_EQ(matrix_1(2, 0), 100.8);
  EXPECT_DOUBLE_EQ(matrix_1(2, 1), 318.36);
  EXPECT_DOUBLE_EQ(matrix_1(2, 2), 491.82);
}

TEST(Calculations, MulMatrixException) {
  S21Matrix matrix_1(2, 1);
  matrix_1(0, 0) = 21;
  matrix_1(1, 0) = -42;
  S21Matrix matrix_2(1, 1);
  matrix_2(0, 0) = 21;

  EXPECT_ANY_THROW(matrix_1.MulMatrix(matrix_2));
}

TEST(Overloads, EqMatrixSuccess) {
  S21Matrix matrix_1(3, 2);
  matrix_1(0, 0) = 1.0;
  matrix_1(0, 1) = 2.0;
  matrix_1(1, 0) = 3.0;
  matrix_1(1, 1) = 4.0;
  S21Matrix matrix_2(3, 2);
  matrix_2(0, 0) = 1.0;
  matrix_2(0, 1) = 2.0;
  matrix_2(1, 0) = 3.0;
  matrix_2(1, 1) = 4.0;

  EXPECT_EQ(matrix_1 == matrix_2, true);
}

TEST(Overloads, Comparing_EqMatrixFail) {
  S21Matrix matrix_1(2, 1);
  S21Matrix matrix_2(1, 1);

  EXPECT_EQ(matrix_1 == matrix_2, false);
}

TEST(Overloads, SumMatrixSuccess) {
  S21Matrix matrix_1(2, 2);
  matrix_1(0, 0) = 1.0;
  matrix_1(0, 1) = 2.0;
  matrix_1(1, 0) = 3.0;
  matrix_1(1, 1) = 4.0;
  S21Matrix matrix_2(2, 2);
  matrix_2(0, 0) = 1.0;
  matrix_2(0, 1) = 2.0;
  matrix_2(1, 0) = 3.0;
  matrix_2(1, 1) = 4.0;
  S21Matrix result(2, 2);
  result(0, 0) = 0.0;
  result(0, 1) = 0.0;
  result(1, 0) = 0.0;
  result(1, 1) = 0.0;

  result = matrix_1 + matrix_2;

  EXPECT_DOUBLE_EQ(result(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 8.0);
}

TEST(Overloads, SubMatrixSuccess) {
  S21Matrix matrix_1(2, 2);
  matrix_1(0, 0) = 2.0;
  matrix_1(0, 1) = 4.0;
  matrix_1(1, 0) = 6.0;
  matrix_1(1, 1) = 8.0;
  S21Matrix matrix_2(2, 2);
  matrix_2(0, 0) = 1.0;
  matrix_2(0, 1) = 2.0;
  matrix_2(1, 0) = 3.0;
  matrix_2(1, 1) = 4.0;
  S21Matrix result(2, 2);
  result(0, 0) = 0.0;
  result(0, 1) = 0.0;
  result(1, 0) = 0.0;
  result(1, 1) = 0.0;

  result = matrix_1 - matrix_2;

  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

TEST(Overloads, MulNumberSuccess) {
  S21Matrix matrix_1(2, 2);
  matrix_1(0, 0) = 1.0;
  matrix_1(0, 1) = 2.0;
  matrix_1(1, 0) = 3.0;
  matrix_1(1, 1) = 4.0;
  S21Matrix result(2, 2);
  result(0, 0) = 0.0;
  result(0, 1) = 0.0;
  result(1, 0) = 0.0;
  result(1, 1) = 0.0;

  result = matrix_1 * 2.0;

  EXPECT_DOUBLE_EQ(result(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 8.0);
}

TEST(Overloads, MulMatrixSuccess) {
  S21Matrix matrix_1(1, 2);
  matrix_1(0, 0) = 4;
  matrix_1(0, 1) = 8;
  S21Matrix matrix_2(2, 1);
  matrix_2(0, 0) = 15;
  matrix_2(1, 0) = 16;
  S21Matrix result(1, 1);

  result = matrix_1 * matrix_2;

  EXPECT_DOUBLE_EQ(result(0, 0), 188.0);
}

TEST(AssignmentCalculations, SumMatrixSuccess) {
  S21Matrix matrix_1(2, 2);
  matrix_1(0, 0) = 1.0;
  matrix_1(0, 1) = 2.0;
  matrix_1(1, 0) = 3.0;
  matrix_1(1, 1) = 4.0;
  S21Matrix matrix_2(2, 2);
  matrix_2(0, 0) = 1.0;
  matrix_2(0, 1) = 2.0;
  matrix_2(1, 0) = 3.0;
  matrix_2(1, 1) = 4.0;

  matrix_1 += matrix_2;

  EXPECT_DOUBLE_EQ(matrix_1(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(matrix_1(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix_1(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix_1(1, 1), 8.0);
}

TEST(AssignmentCalculations, SubMatrixSuccess) {
  S21Matrix matrix_1(2, 2);
  matrix_1(0, 0) = 2.0;
  matrix_1(0, 1) = 4.0;
  matrix_1(1, 0) = 6.0;
  matrix_1(1, 1) = 8.0;
  S21Matrix matrix_2(2, 2);
  matrix_2(0, 0) = 1.0;
  matrix_2(0, 1) = 2.0;
  matrix_2(1, 0) = 3.0;
  matrix_2(1, 1) = 4.0;

  matrix_1 -= matrix_2;

  EXPECT_DOUBLE_EQ(matrix_1(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix_1(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix_1(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix_1(1, 1), 4.0);
}

TEST(AssignmentCalculations, MulNumberSuccess) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  matrix *= 2.0;

  EXPECT_DOUBLE_EQ(matrix(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 8.0);
}

TEST(AssignmentCalculations, MulMatrixSuccess) {
  S21Matrix matrix_1(1, 2);
  matrix_1(0, 0) = 4;
  matrix_1(0, 1) = 8;
  S21Matrix matrix_2(2, 1);
  matrix_2(0, 0) = 15;
  matrix_2(1, 0) = 16;

  matrix_1 *= matrix_2;

  EXPECT_DOUBLE_EQ(matrix_1(0, 0), 188.0);
}

TEST(Special, TransposeSuccess) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;
  S21Matrix result = matrix.Transpose();

  EXPECT_EQ(result.GetRows(), 3);
  EXPECT_EQ(result.GetCols(), 2);
  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(result(2, 0), 3.0);
  EXPECT_DOUBLE_EQ(result(2, 1), 6.0);
}

TEST(Special, DeterminantSuccess1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 23.42;
  double result = 0.0;

  result = matrix.Determinant();

  EXPECT_DOUBLE_EQ(result, 23.42);
}

TEST(Special, DeterminantSuccess2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 4.0;
  matrix(0, 1) = 8.0;
  matrix(1, 0) = 15.0;
  matrix(1, 1) = 16.0;
  double result = 0.0;

  result = matrix.Determinant();

  EXPECT_DOUBLE_EQ(result, -56.0);
}

TEST(Special, DeterminantSuccess3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 0.123;
  matrix(0, 1) = 5.21;
  matrix(0, 2) = 9.515;
  matrix(1, 0) = 4.815;
  matrix(1, 1) = 42.0;
  matrix(1, 2) = 23.42;
  matrix(2, 0) = 0.99;
  matrix(2, 1) = 710;
  matrix(2, 2) = 21.0;
  double result = 0.0;

  result = matrix.Determinant();

  EXPECT_DOUBLE_EQ(result, 29790.027318);
}

TEST(Special, DeterminantFail) {
  S21Matrix matrix(1, 2);
  EXPECT_ANY_THROW(matrix.Determinant());
}

TEST(Special, CalcComplementsSuccess) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 0.0;
  matrix(1, 1) = 4.0;
  matrix(1, 2) = 2.0;
  matrix(2, 0) = 5.0;
  matrix(2, 1) = 2.0;
  matrix(2, 2) = 1.0;

  S21Matrix result = matrix.CalcComplements();

  EXPECT_DOUBLE_EQ(result(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 10.0);
  EXPECT_DOUBLE_EQ(result(0, 2), -20.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 1), -14.0);
  EXPECT_DOUBLE_EQ(result(1, 2), 8.0);
  EXPECT_DOUBLE_EQ(result(2, 0), -8.0);
  EXPECT_DOUBLE_EQ(result(2, 1), -2.0);
  EXPECT_DOUBLE_EQ(result(2, 2), 4.0);
}

TEST(Special, CalcComplementsFail1) {
  S21Matrix matrix(2, 1);

  EXPECT_ANY_THROW(matrix.CalcComplements());
}

TEST(Special, CalcComplementsFail2) {
  S21Matrix matrix(1, 1);

  EXPECT_ANY_THROW(matrix.CalcComplements());
}

TEST(Special, InverseMatrixSuccess) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 5.0;
  matrix(0, 2) = 7.0;
  matrix(1, 0) = 6.0;
  matrix(1, 1) = 3.0;
  matrix(1, 2) = 4.0;
  matrix(2, 0) = 5.0;
  matrix(2, 1) = -2.0;
  matrix(2, 2) = -3.0;

  S21Matrix result = matrix.InverseMatrix();

  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), -1.0);
  EXPECT_DOUBLE_EQ(result(0, 2), 1.0);
  EXPECT_DOUBLE_EQ(result(1, 0), -38.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 41.0);
  EXPECT_DOUBLE_EQ(result(1, 2), -34.0);
  EXPECT_DOUBLE_EQ(result(2, 0), 27.0);
  EXPECT_DOUBLE_EQ(result(2, 1), -29.0);
  EXPECT_DOUBLE_EQ(result(2, 2), 24.0);
}

TEST(Special, InverseMatrixFail) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 0.0;
  matrix(0, 1) = 0.0;
  matrix(0, 2) = 0.0;
  matrix(1, 0) = 0.0;
  matrix(1, 1) = 0.0;
  matrix(1, 2) = 0.0;
  matrix(2, 0) = 0.0;
  matrix(2, 1) = 0.0;
  matrix(2, 2) = 0.0;

  EXPECT_ANY_THROW(matrix.InverseMatrix());
}

TEST(AccessorMutator, SetRowSuccess1) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  matrix.SetRows(1);

  EXPECT_EQ(matrix.GetRows(), 1);
  EXPECT_EQ(matrix.GetCols(), 2);
}

TEST(AccessorMutator, SetRowSuccess2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  matrix.SetRows(3);

  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 2);
  EXPECT_DOUBLE_EQ(matrix(2, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix(2, 1), 0.0);
}

TEST(AccessorMutator, SetColSuccess1) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  matrix.SetCols(1);

  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 1);
}

TEST(AccessorMutator, SetColSuccess2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  matrix.SetCols(3);

  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 3);
  EXPECT_DOUBLE_EQ(matrix(0, 2), 0.0);
  EXPECT_DOUBLE_EQ(matrix(1, 2), 0.0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
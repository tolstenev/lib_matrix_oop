#include <gtest/gtest.h>

#include <iostream>

#include "s21_matrix_oop.h"

TEST(Constructors, ParameterizedSuccess) {
  S21Matrix m(3, 4);
  EXPECT_EQ(m.GetRows(), 3);
  EXPECT_EQ(m.GetCols(), 4);
}

TEST(Calculations, OverloadMulMatrixSuccess) {
S21Matrix matrix_1(1, 2);
matrix_1(0, 0) = 4;
matrix_1(0, 1) = 8;
S21Matrix matrix_2(2, 1);
matrix_2(0, 0) = 15;
matrix_2(1, 0) = 16;
S21Matrix result(1, 1);

result = matrix_1 * matrix_2;

EXPECT_DOUBLE_EQ(result.GetVal(0, 0), 188.0);
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
  EXPECT_DOUBLE_EQ(matrix_1.GetVal(0, 0), 2.4);
  EXPECT_DOUBLE_EQ(matrix_1.GetVal(0, 1), 7.58);
  EXPECT_DOUBLE_EQ(matrix_1.GetVal(0, 2), 11.71);
  EXPECT_DOUBLE_EQ(matrix_1.GetVal(1, 0), -201.6);
  EXPECT_DOUBLE_EQ(matrix_1.GetVal(1, 1), -636.72);
  EXPECT_DOUBLE_EQ(matrix_1.GetVal(1, 2), -983.64);
  EXPECT_DOUBLE_EQ(matrix_1.GetVal(2, 0), 100.8);
  EXPECT_DOUBLE_EQ(matrix_1.GetVal(2, 1), 318.36);
  EXPECT_DOUBLE_EQ(matrix_1.GetVal(2, 2), 491.82);
}

TEST(Calculations, MulMatrixException) {
S21Matrix matrix_1(2, 1);
matrix_1(0, 0) = 21;
matrix_1(1, 0) = -42;
S21Matrix matrix_2(1, 1);
matrix_2(0, 0) = 21;

EXPECT_ANY_THROW(matrix_1.MulMatrix(matrix_2));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
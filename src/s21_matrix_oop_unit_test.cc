#include <gtest/gtest.h>

#include <iostream>

#include "s21_matrix_oop.h"

TEST(Constructors, ParameterizedSuccess) {
  S21Matrix m(3, 4);
  EXPECT_EQ(m.GetRows(), 3);
  EXPECT_EQ(m.GetCols(), 4);
}

// TEST(Сalculations, MartixMultiplicationSuccess) {
//   S21Matrix m1(3, 1);
//   S21Matrix m2(1, 3);
//   m1.FillByOrder();
//   m2.FillByOrder();
//   EXPECT_EQ(m.GetRows(), 3);
//   EXPECT_EQ(m.GetCols(), 4);
// }

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
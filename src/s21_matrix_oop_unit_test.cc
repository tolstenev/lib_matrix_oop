#include <gtest/gtest.h>
#include <iostream>
#include "s21_matrix_oop.h"

TEST(Constructors, ParameterizedSuccess) {
	S21Matrix m(3, 4);
	EXPECT_EQ(m.GetRows(), 3);
	EXPECT_EQ(m.GetCols(), 4);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
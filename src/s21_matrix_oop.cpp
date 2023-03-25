/*
 * Copyright (с) 2023 Student of School 21:
 * Gleb Tolstenev
 *
 * yonnarge@student.21-school.ru
 */

#include "s21_matrix_oop.h"

/**
 * @brief Default constructor
 */
S21Matrix::S21Matrix() { S21Matrix(3, 3); }

/**
 * @brief Parameterized constructor
 * @param rows - number of rows
 * @param cols - number of colomns
 */
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
	rows_ = rows;
	cols_ = cols;
	p_ = new double*[rows_]();

	for (int i = 0; i < rows_; ++i)
		p_[i] = new double[cols_]();
}

/**
 * @brief Copy constructor
 * @param m - the matrix to be copied
 */
S21Matrix::S21Matrix(const S21Matrix& m) : S21Matrix(m.rows_, m.cols_) {
	p_ = new double*[rows_]();

	for (int i = 0; i < rows_; ++i)
		p_[i] = new double[cols_]();

	for (int i = 0; i < rows_; ++i)
		for (int j = 0; j < cols_; ++j)
	    p_[i] = m.p_[i];
}

/**
 * @brief Destructor
 */
S21Matrix::~S21Matrix() {
  if (p_) {
		for (int i = 0; i < rows_; ++i)
			delete [] p_[i];
    delete [] p_;
  }
}

/**
 * @brief Fills the matrix with numbers in order from 1 to rows * cols)
 */
void S21Matrix::fill_by_order() {
  int k = 0;
	for (int i = 0; i < rows_; ++i)
		for (int j = 0; j < cols_; ++j)
			p_[i][j] = ++k;
}

/**
 * @brief Print matrix
 */
void S21Matrix::print_matrix() {
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j)
			std::cout << p_[i][j] << '\t';
		std::cout << std::endl;
	}
}

/**
 * @brief Check the current work
 */
int main() {
  int x, y = 1;

  while (x != 0 || y != 0) {
    std::cin >> x;
    std::cin >> y;
    S21Matrix m1(x, y);
    m1.fill_by_order();
    m1.print_matrix();
	}
  return 0;
}

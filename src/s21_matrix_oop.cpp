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
S21Matrix::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  p_ = new double[rows_ * cols_]();
}

/**
 * @brief Constructor
 * @param rows - number of rows
 * @param cols - number of colomns
 */
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  p_ = new double[rows_ * cols_]();
}

/**
 * @brief Destructor
 */
S21Matrix::~S21Matrix() {
  if (p_) {
    delete[] p_;
  }
}

/**
 * @brief Fills the matrix with numbers in order from 0 to (rows * cols) - 1
 */
void S21Matrix::fill_by_order() {
  int k = 0;
  for (int i = 0; i < rows_ * cols_; ++i) p_[i] = ++k;
}

/**
 * @brief Print matrix
 */
void S21Matrix::print_matrix() {
  for (int i = 0; i < rows_ * cols_; ++i)
    ((i + 1) % rows_) ? std::cout << p_[i] << '\t'
                      : std::cout << p_[i] << std::endl;
}

/**
 * @brief Check the current work
 */
int main() {
  S21Matrix m1(5, 5);

  m1.fill_by_order();
  m1.print_matrix();

  return 0;
}

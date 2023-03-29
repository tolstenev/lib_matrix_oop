/*
 * Copyright 2023 Gleb Tolstenev
 * yonnarge@student.21-school.ru
 *
 * s21_matrix_oop.cpp is the source code file for s21_matrix_oop library
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "s21_matrix_oop.h"

/**
 * @brief Default constructor
 */
S21Matrix::S21Matrix() : rows_(3), cols_(3), elements_(NewArrayOfElements()) {}

/**
 * @brief Parameterized constructor
 * @param rows - number of rows
 * @param cols - number of colomns
 */
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  elements_ = NewArrayOfElements();
}

/**
 * @brief Copy constructor
 * @param other - the matrix to be copied
 */
S21Matrix::S21Matrix(const S21Matrix &other) : rows_(other.rows_), cols_(other.cols_) {
  elements_ = NewArrayOfElements();
  CopyArrayOfElements(other);
}

void S21Matrix::CopyArrayOfElements(const S21Matrix &other) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      elements_[i][j] = other.elements_[i][j];
    }
  }
}

/**
 * @brief Destructor
 */
S21Matrix::~S21Matrix() { DeleteArrayOfElements(); }

/**
 * @brief Fills the matrix with numbers in order from 1 to rows * cols)
 */
void S21Matrix::FillByOrder() {
  int k = 0;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      elements_[i][j] = ++k;
    }
  }
}

/**
 * @brief Fills the matrix with numbers by 1
 */
void S21Matrix::FillWithOne() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      elements_[i][j] = 1;
    }
  }
}

/**
 * @brief Print matrix
 */
void S21Matrix::Print() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      std::cout << elements_[i][j] << '\t';
    }
    std::cout << std::endl;
  }
}

/**
 * @brief Allocate memory for matrix elements
 */
double **S21Matrix::NewArrayOfElements() const {
  auto elements = new double *[rows_]();
  for (int i = 0; i < rows_; ++i) {
    elements[i] = new double[cols_]();
  }
  return elements;
}

/**
 * @brief Allocate memory for matrix elements
 */
void S21Matrix::DeleteArrayOfElements() {
  if (elements_) {
    for (int i = 0; i < rows_; ++i) {
      delete[] elements_[i];
    }
    delete elements_;
  }
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {  // TODO: Add self-assignment properly
  DeleteArrayOfElements();
  NewArrayOfElements();
  CopyArrayOfElements(other);
  return *this;
}

/**
 * @brief Check the current work
 */
int main() {
  S21Matrix m1(3, 3);
  m1.FillByOrder();
  std::cout << "m1" << std::endl;
  m1.Print();
  std::cout << std::endl;

  S21Matrix m2(m1);
  std::cout << "m2" << std::endl;
  m2.Print();
  std::cout << std::endl;

	m2.FillWithOne();
	std::cout << "m2" << std::endl;
	m2.Print();
	std::cout << std::endl;

	m1 = m2;
	std::cout << "m1" << std::endl;
	m1.Print();
	std::cout << std::endl;

  return 0;
}

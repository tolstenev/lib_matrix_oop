/*
 * Copyright 2023 Gleb Tolstenev
 * yonnarge@student.21-school.ru
 *
 * s21_matrix_oop.cc is the source code file for s21_matrix_oop library
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
 * @brief Constructor for exception
 * @param error_code - the numeric code of error
 */
S21MatrixException::S21MatrixException(int error_code) {
  error_code_ = error_code;
}

/**
 * @brief Copy constructor for exception
 * @param other
 */
S21MatrixException::S21MatrixException(
    const S21MatrixException &other) noexcept {
  error_code_ = other.error_code_;
}

/**
 * @brief Default constructor
 */
S21Matrix::S21Matrix() : rows_(3), cols_(3), matrix_(NewArrayOfElements()) {}

/**
 * @brief Parameterized constructor
 * @param rows - number of rows
 * @param cols - number of colomns
 */
S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1) {
    throw S21MatrixException(INCORRECT_ROWS);
  } else if (cols < 1) {
    throw S21MatrixException(INCORRECT_COLS);
  } else {
    rows_ = rows;
    cols_ = cols;
    matrix_ = NewArrayOfElements();
  }
}

/**
 * @brief Copy constructor
 * @param other - reference to the matrix that will be copied
 */
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = NewArrayOfElements();
  CopyArrayOfElements(other);
}

/**
 * @brief Copy elements of matrix other
 * @param other - reference to the matrix whose elements will be copied
 */
void S21Matrix::CopyArrayOfElements(const S21Matrix &other) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

/**
 * @brief Move constructor
 * @param other
 */
S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
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
      matrix_[i][j] = ++k;
    }
  }
}

/**
 * @brief Fills the matrix with numbers by 1
 */
void S21Matrix::FillWithOne() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = 1;
    }
  }
}

/**
 * @brief Print matrix
 */
void S21Matrix::Print() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      std::cout << matrix_[i][j] << '\t';
    }
    std::cout << std::endl;
  }
}

/**
 * @brief Allocate memory for matrix elements
 * @return Pointer to the allocated memory
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
  if (matrix_) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete matrix_;
  }
}

/**
 * @brief Overload of '=' for matrices
 * @param other - the matrix that will be assigned
 * @return reference to the new matrix
 */
S21Matrix &S21Matrix::operator=(
    const S21Matrix &other) {  // TODO: Add self-assignment properly
  DeleteArrayOfElements();
  NewArrayOfElements();
  CopyArrayOfElements(other);
  return *this;
}

/**
 * @brief Get the string to identifying exception
 */
const char *S21MatrixException::what() const noexcept {
  const char *comment;
  if (error_code_ == INCORRECT_ROWS)
    comment = comment_low_rows_;
  else if (error_code_ == INCORRECT_COLS)
    comment = comment_low_cols_;
  else if (error_code_ == DIFF_SIZE)
    comment = comment_diff_size_;
  else
    comment = "Undefiend error";
  return comment;
}

/**
 * @brief Compare the current matrix size with other
 * @param other - the matrix to be compared with
 */
void S21Matrix::HaveSameSize(const S21Matrix &other) {
	if (this->GetRows() != other.GetRows() || this->GetCols() != other.GetCols())
		throw S21MatrixException(DIFF_SIZE);
}

/**
 * @brief Add other matrix to current
 * @param other - the matrix that will be added
 */
void S21Matrix::SumMatrix(const S21Matrix& other) {
	this->HaveSameSize(other);

	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
		}
	}
}

/**
 * @brief Overload of '+' for matrices
 * @param other - the matrix that will be added
 * @return Matrix with result of addition
 */
S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
	S21Matrix result(*this);
	result.SumMatrix(other);
	return result;
}

/**
 * @brief Check the current work
 */
int main() {
  try {
    S21Matrix m1(3, 3);
    m1.FillByOrder();
    std::cout << "m1" << std::endl;
    m1.Print();
    std::cout << std::endl;

		S21Matrix m2(3, 3);
		m2.FillByOrder();
		std::cout << "m2" << std::endl;
		m2.Print();
		std::cout << std::endl;

		std::cout << "sum m1 and m2" << std::endl;
		m1.SumMatrix(m2);
		m1.Print();
		std::cout << std::endl;
		std::cout << std::endl;


		S21Matrix m3(3, 3);
		m3.FillByOrder();
		std::cout << "m3" << std::endl;
		m3.Print();
		std::cout << std::endl;

		S21Matrix m4(3, 3);
		m4.FillByOrder();
		std::cout << "m4" << std::endl;
		m4.Print();
		std::cout << std::endl;

		S21Matrix res(3, 3);
		res = m3 + m4;
		res.Print();
		std::cout << std::endl;

//		std::cout << "sum m3 and m4" << std::endl;
//		m3.SumMatrix(m4);
//		m3.Print();
	}

  catch (std::exception &ex) {
    std::cout << "Exception Caught: " << ex.what() << std::endl;
  }

  return 0;
}

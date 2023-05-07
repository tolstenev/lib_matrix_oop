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

/* Constructors and destructors ---------------------------------------------*/

/**
 * @brief Default constructor
 */
S21Matrix::S21Matrix()
    : rows_(3), cols_(3), matrix_(NewArrayOfElements(3, 3)) {}

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
    matrix_ = NewArrayOfElements(rows, cols);
  }
}

/**
 * @brief Copy constructor
 * @param other - reference to the matrix that will be copied
 */
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = NewArrayOfElements(other.rows_, other.cols_);
  CopyArrayOfElements(other);
}

/**
 * @brief Move constructor
 * @param other
 */
S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

/**
 * @brief Destructor
 */
S21Matrix::~S21Matrix() { DeleteArrayOfElements(); }

/* Memory management functions ----------------------------------------*/

/**
 * @brief Allocate memory for matrix elements
 * @return Pointer to the allocated memory
 */
double **S21Matrix::NewArrayOfElements(int rows, int cols) const {
  auto elements = new double *[rows]();
  for (int i = 0; i < rows; ++i) {
    elements[i] = new double[cols]();
  }
  return elements;
}

/**
 * @brief Copy elements from other matrix
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

/* Overloads ---------------------------------------------------------*/

/**
 * @brief Overload of '=' for matrices
 * @param other - the matrix that will be assigned
 * @return reference to the new matrix
 */
S21Matrix &S21Matrix::operator=(
    const S21Matrix &other) {  // TODO: Add self-assignment properly
  DeleteArrayOfElements();
  NewArrayOfElements(other.rows_, other.cols_);
  CopyArrayOfElements(other);
  return *this;
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
 * @brief Overload of '-' for matrices
 * @param other - the matrix that will be subtract
 * @return Matrix with result of subtraction
 */
S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

/**
 * @brief Overload of '*' for matrices that will be multiply by a number 'num'
 * @param num - the number by which the matrix will be multiplied
 * @return Matrix with result of multiplication
 */
S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

/**
 * @brief Overload of '*' for matrices
 * @param other - the matrix that will be multiplied
 * @return Matrix with result of multiplication
 */
S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

/**
 * Overload of '()' for indexation by matrix elements (row, column)
 * @param row - index of row
 * @param col - index of column
 * @return The element of matrix with idexes (row, col)
 */
double &S21Matrix::operator()(int row, int col) {
  if (!(0 < row || row <= rows_) || !(0 < col || col <= cols_))
    throw S21MatrixException(OUTSIDE_INDEX);
  return matrix_[row][col];
}

//bool operator==(const S21Matrix& other) const;

//S21Matrix& operator+=(const S21Matrix& other);

//S21Matrix& operator-=(const S21Matrix& other);

//S21Matrix& operator*=(const double num);

//S21Matrix& operator*=(const S21Matrix& other);

/* Core methods --------------------------------------------------------*/

/**
 * Checks matrix for equality with each other
 * @param other - the matrix that will be compared
 * @return true - martices is equal;
 *         false - martices is different.
 */
bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool is_equal = true;
  if (rows_ != other.rows_ && cols_ != other.cols_) {
    is_equal = false;
  } else {
    for (int i = 0; (i < rows_) && is_equal; ++i) {
      for (int j = 0; (j < cols_) && is_equal; ++j) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) {
          is_equal = false;
        }
      }
    }
  }
  return is_equal;
}

/**
 * @brief Add other matrix to current
 * @param other - the matrix that will be added
 */
void S21Matrix::SumMatrix(const S21Matrix &other) {
  CheckSizesFor(SUM, other);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

/**
 * @brief Subtract other matrix from current
 * @param other - the matrix that will be subtract
 */
void S21Matrix::SubMatrix(const S21Matrix &other) {
  CheckSizesFor(SUB, other);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

/**
 * @brief Multiplies the matrix by a number 'num'
 * @param num - the number by which the matrix will be multiplied
 */
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

/**
 * @brief Multiplies a matrix by the other one
 * @param other - the matrix that will be multiplied
 */
void S21Matrix::MulMatrix(const S21Matrix &other) {
  CheckSizesFor(MUL_MATRIX, other);

  double **tmp = NewArrayOfElements(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        tmp[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  DeleteArrayOfElements();
  cols_ = other.cols_;
  matrix_ = tmp;
}

//S21Matrix S21Matrix::Transpose() {}

//S21Matrix S21Matrix::CalcComplements() {}

//double S21Matrix::Determinant() {}

//S21Matrix S21Matrix::InverseMatrix() {}

/* Help methods ---------------------------------------------------------*/

/**
 * @brief Compare the current matrix size with other for different operation
 * @param type_of_operation - numeric code of operation described in enum
 * 'types_of_operation' (SUM = 1, SUB = 2, etc.)
 * @param other - the matrix to be compared with
 */
void S21Matrix::CheckSizesFor(int type_of_operation,
                              const S21Matrix &other) const {
  if (this->GetRows() != other.GetRows() ||
      this->GetCols() != other.GetCols()) {
    if (type_of_operation == SUM) throw S21MatrixException(DIFF_SIZE_SUM);
    if (type_of_operation == SUB) throw S21MatrixException(DIFF_SIZE_SUB);
  }
  if (this->GetRows() != other.GetCols() ||
      this->GetCols() != other.GetRows()) {
    if (type_of_operation == MUL_MATRIX)
      throw S21MatrixException(DIFF_SIZE_MUL_MATRIX);
  }
}

/* Additional methods -----------------------------------------------------*/

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

/*

int main() {
  try {
    S21Matrix matrix_1(1, 2);
    matrix_1(0, 0) = 4;
    matrix_1(0, 1) = 8;
    std::cout << "matrix_1" << std::endl;
    matrix_1.Print();
    std::cout << std::endl;

    S21Matrix matrix_2(2, 1);
    matrix_2(0, 0) = 15;
    matrix_2(1, 0) = 16;
    std::cout << "matrix_2" << std::endl;
    matrix_2.Print();
    std::cout << std::endl;


    std::cout << std::endl;
  }

  catch (std::exception &ex) {
    std::cout << "Exception Caught: " << ex.what() << std::endl;
  }

  return 0;
}
*/
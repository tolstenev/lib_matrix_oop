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
    throw std::invalid_argument("The number of rows is lower than 1");
  } else if (cols < 1) {
    throw std::invalid_argument("The number of columns is lower than 1");
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
 * @brief Delete allocated memory for matrix elements
 */
void S21Matrix::DeleteArrayOfElements() {
  if (matrix_) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
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
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = NewArrayOfElements(other.rows_, other.cols_);
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
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
    throw std::out_of_range(
        "Attempt to access to element of matrix by index outside of the range");
  return matrix_[row][col];
}

/**
 * Checks for matrices equality
 * @param other - the matrix that will be compared
 * @return true - martices is equal;
 *         false - martices is different.
 */
bool S21Matrix::operator==(const S21Matrix &other) {
  return this->EqMatrix(other);
}

/**
 * Addition assignment
 * @param other - the matrix that will be added
 * @return reference to the added matrix
 */
S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

/**
 * Difference assignment
 * @param other - the matrix that will be subtract
 * @return reference to the subtracted matrix
 */
S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

/**
 * Multiplication by number assignment
 * @param num - the number by which the matrix will be multiplied
 * @return reference to the multiplied matrix
 */
S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

/**
 * Multiplication by matrix assignment
 * @param other - the matrix that will be multiplied
 * @return reference to the multiplied matrix
 */
S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

/* Core methods --------------------------------------------------------*/

/**
 * Checks matrix for equality with each other
 * @param other - the matrix that will be compared
 * @return true - martices is equal;
 *         false - martices is different.
 */
bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool is_equal = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
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

/**
 * @brief Creates a new transposed matrix from the current one and returns it
 * @return transposed matrix
 */
S21Matrix S21Matrix::Transpose() {
  S21Matrix tmp(cols_, rows_);
  for (int i = 0; i < tmp.rows_; ++i) {
    for (int j = 0; j < tmp.cols_; ++j) {
      tmp.matrix_[i][j] = matrix_[j][i];
    }
  }
  return tmp;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_)
    throw std::logic_error(
        "Attempt to calculate complements for non-square "
        "matrix");
  if (rows_ < 2)
    throw std::logic_error(
        "Attempt to calculate complements for matrix with one element");
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < result.rows_; ++i) {
    for (int j = 0; j < result.cols_; ++j) {
      result.matrix_[i][j] = CalcOneComplement(*this, i, j);
    }
  }
  return result;
}

double S21Matrix::CalcOneComplement(const S21Matrix &src, int row_skip,
                                    int col_skip) {
  double sign = ((row_skip + col_skip) % 2) ? -1 : 1;
  return (sign * CalcMinor(src, row_skip, col_skip));
}

double S21Matrix::CalcMinor(const S21Matrix &src, int row_skip, int col_skip) {
  S21Matrix matrix_for_minor(src.rows_ - 1, src.cols_ - 1);
  matrix_for_minor.FillForMinor(src, row_skip, col_skip);
  return matrix_for_minor.CalcDeterminant();
}

double S21Matrix::Determinant() {
  if (rows_ != cols_)
    throw std::logic_error(
        "Attempt to calculate determinant for non-square "
        "matrix");
  return CalcDeterminant();
}

double S21Matrix::CalcDeterminant() {
  double result = 0.0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    double sign = 1.0;
    S21Matrix matrix_for_minor(rows_ - 1, cols_ - 1);
    for (int j = 0; j < rows_; ++j) {
      matrix_for_minor.FillForMinor(*this, 0, j);
      result += sign * matrix_[0][j] * matrix_for_minor.CalcDeterminant();
      sign *= -1.0;
    }
  }
  return result;
}

void S21Matrix::FillForMinor(const S21Matrix &src, int row_skip, int col_skip) {
  int i_minor = 0;
  int j_minor = 0;
  for (int i_src = 0; i_src < src.rows_; ++i_src) {
    if (i_src == row_skip) continue;
    j_minor = 0;
    for (int j_src = 0; j_src < src.cols_; ++j_src) {
      if (j_src == col_skip) continue;
      matrix_[i_minor][j_minor] = src.matrix_[i_src][j_src];
      ++j_minor;
    }
    ++i_minor;
  }
}

S21Matrix S21Matrix::InverseMatrix() {
  S21Matrix result(rows_, cols_);
  double det = this->Determinant();
  if (det == 0.0)
    throw std::logic_error(
        "Impossible find inverse matrix. Determinant equals "
        "zero");

  result = this->CalcComplements().Transpose();
  result.MulNumber(1.0 / det);
  return result;
}

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
    if (type_of_operation == SUM)
      throw std::logic_error(
          "The addition was rejected. Matrices have different sizes");
    if (type_of_operation == SUB)
      throw std::logic_error(
          "The subtraction was rejected. Matrices have different sizes");
  }
  if (this->GetRows() != other.GetCols() ||
      this->GetCols() != other.GetRows()) {
    if (type_of_operation == MUL_MATRIX)
      throw std::logic_error(
          "The multiplication of matrices was rejected. Matrices have "
          "different sizes");
  }
}

/* Additional methods -----------------------------------------------------*/

/**
 * @brief Fills the matrix with numbers in order from 1 to rows * cols)
 */
void S21Matrix::FillByOrder() {
  double k = 0.0;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = ++k;
    }
  }
}

/**
 * @brief Fills the matrix with even numbers (2.0, 4.0, 6.0...)
 */
void S21Matrix::FillByEven() {
  double k = 0.0;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = ++k * 2.0;
    }
  }
}

/**
 * @brief Fills the matrix with numbers by 0
 */
void S21Matrix::FillWithZero() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = 0.0;
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

    std::cout << "result" << std::endl;
    result.Print();
    std::cout << std::endl;

  }

  catch (std::exception &ex) {
    std::cout << "Exception Caught: " << ex.what() << std::endl;
  }

  return 0;
}
*/

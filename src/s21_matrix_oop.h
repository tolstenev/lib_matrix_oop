/*
 * Copyright 2023 Gleb Tolstenev
 * yonnarge@student.21-school.ru
 *
 * s21_matrix_oop.h is the header file for s21_matrix_oop library
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

#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <math.h>

#include <cstring>
#include <iostream>

#define EPS 1e-07

/**
 * @brief Numeric error codes for exceptions
 */
enum types_of_operation {
  MOCK_OF_TYPE_OPERATION = 0,
  SUM = 1,
  SUB = 2,
  MUL_MATRIX = 3,
  NUMBER_OF_OPERATIONS  // To get amount of elements of enum
};

/**
 * @brief Implementation of the matrix
 */
class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 private:
  /* Memory management functions -----------------------------------------*/
  double** NewArrayOfElements(int rows, int cols) const;
  void DeleteArrayOfElements();
  void CopyArrayOfElements(const S21Matrix& other);

 public:
  /* Constructors and destructors ----------------------------------------*/
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  /* Overloads -----------------------------------------------------------*/
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;
  S21Matrix operator*(const S21Matrix& other) const;
  double& operator()(int row, int col);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  S21Matrix& operator*=(const S21Matrix& other);

  /* Core methods --------------------------------------------------------*/
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  /* Accessors and mutators ----------------------------------------------*/
  int GetRows() const;
  int GetCols() const;
  double GetVal(int row, int col) const;
  void SetRows(int new_rows);
  void SetCols(int new_cols);
  void SetRowsOrCols(bool isItRow, int value);

  /* Additional methods for testing --------------------------------------*/
  void FillByOrder();
  void FillByEven();
  void FillWithZero();
  //  void Print();

 private:
  /* Help methods --------------------------------------------------------*/
  void CheckSizesFor(int type_of_operation, const S21Matrix& other) const;
  double CalcDeterminant();
  void FillForMinor(const S21Matrix& src, int row_skip, int col_skip);
  double CalcOneComplement(const S21Matrix& src, int row_skip, int col_skip);
  double CalcMinor(const S21Matrix& src, int row_skip, int col_skip);
};

#endif  // SRC_S21_MATRIX_OOP_H_

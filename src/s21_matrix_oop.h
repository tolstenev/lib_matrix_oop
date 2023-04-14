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

#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <cstring>
#include <exception>
#include <iostream>

/**
 * @brief Numeric error codes for exceptions
 */
enum error_codes {
  OK = 0,
  INCORRECT_ROWS = 1,
  INCORRECT_COLS = 2,
  DIFF_SIZE = 3,
};

/**
 * @brief Implementation of the matrix
 */
class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

	S21Matrix& operator=(const S21Matrix& other);
	S21Matrix operator+(const S21Matrix& other) const;

	void SumMatrix(const S21Matrix& other);

  double** NewArrayOfElements() const;
  void DeleteArrayOfElements();
  void CopyArrayOfElements(const S21Matrix& other);

	void HaveSameSize(const S21Matrix &other);

  int GetRows() const { return rows_; }
  int GetCols() const { return cols_; }

  void FillByOrder();
  void FillWithOne();
  void Print();
};

/**
 * @brief Handling exception class
 */
class S21MatrixException : public std::exception {
 private:
  int error_code_;
  const char* comment_low_rows_ = "The number of rows is lower than 1";
  const char* comment_low_cols_ = "The number of columns is lower than 1";
  const char* comment_diff_size_ =
      "The operation cannot be called for matrices of different sizes";

 public:
  explicit S21MatrixException(int error_code);
  S21MatrixException(const S21MatrixException& other) noexcept;

  const char* what() const noexcept override;
};

#endif

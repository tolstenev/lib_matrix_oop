/*
 * Copyright 2023 Gleb Tolstenev
 * yonnarge@student.21-school.ru
 *
 * s21_matrix_exception.h is support header file for s21_matrix_oop library
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

#ifndef SRC_S21_MATRIX_EXCEPTION_H_
#define SRC_S21_MATRIX_EXCEPTION_H_

#include <exception>

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
 * @brief Handling exception class
 */
class S21MatrixException : public std::exception {
 private:
  int error_code_;
  const char* error_comments_[4] = {
      "Undefined error",
      /* 1 (INCORRECT_ROWS) */
      "The number of rows is lower than 1",
      /* 2 INCORRECT_COLS */
      "The number of columns is lower than 1",
      /* 3 DIFF_SIZE */
      "The operation was rejected. Matrices have different sizes"};

 public:
  explicit S21MatrixException(int error_code);
  S21MatrixException(const S21MatrixException& other) noexcept;

  const char* what() const noexcept override;
};

#endif  // SRC_S21_MATRIX_EXCEPTION_H_

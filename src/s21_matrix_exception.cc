/*
 * Copyright 2023 Gleb Tolstenev
 * yonnarge@student.21-school.ru
 *
 * s21_matrix_oop.cc is the support source code file for s21_matrix_oop library
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

#include "s21_matrix_exception.h"

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


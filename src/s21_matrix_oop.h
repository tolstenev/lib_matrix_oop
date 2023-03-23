/*
 * Copyright (с) 2023 Student of School 21:
 * Gleb Tolstenev
 *
 * yonnarge@student.21-school.ru
 */

#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double *p_;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  ~S21Matrix();

  void fill_by_order();
  void print_matrix();
};

#endif

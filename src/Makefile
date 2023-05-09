#
#  Copyright 2023 Gleb Tolstenev
#  yonnarge@student.21-school.ru
#
#  Makefile for s21_matrix_oop library
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#

# Available make targets:
#  - s21_matrix_oop.a: create the static library
#  - test:             build and run the unit test of the library and show results
#  - check:            check source files by 'cppcheck', 'clang-format', and looking for memory leaks by 'leaks'
#  - check_valgrind:   check memory leaks by 'valgrind'
#  - gcov_report:      make test of the library and generate gcov report
#  - open:             generate gcov report and open it
#  - lint:             fix code style with clang-format
#  - clean:            remove generated files without s21_matrix_oop.a
#  - fclean:           remove all generated files
#  - re:               remove all generated files and recompile library

LIB_NAME	:= s21_matrix_oop.a
HEADERS		:= s21_matrix_oop.h

CC			:= gcc
CPP_FLAGS	:= -lstdc++ -std=c++17 -pedantic -Wall -Werror -Wextra
GTEST_FLAGS	:= -lgtest
SRCS		:= s21_matrix_oop.cc
OBJS		:= $(SRCS:.cc=.o)
TEST		:= test
TEST_NAME	:= s21_matrix_oop_unit_test
SRC_TEST	:= $(TEST_NAME).cc
REPORT		:= GcovReport
GCOV_FLAGS	:= -fprofile-arcs -ftest-coverage


.PHONY: all test check check_valgrind lint clean fclean re

all: s21_matrix_oop.a

info:
		@echo "Available make targets:"
		@echo "  s21_matrix_oop.a: create the static library"
		@echo "  test:             build and run the unit test of the library and show results"
		@echo "  check:            check source files by 'cppcheck', 'clang-format', and looking for memory leaks by 'leaks'"
		@echo "  check_valgrind:   check memory leaks by 'valgrind'"
		@echo "  gcov_report:      make test of the library and generate gcov report"
		@echo "  open:             generate gcov report and open it"
		@echo "  lint:             fix code style with clang-format"
		@echo "  clean:            remove generated files without s21_matrix_oop.a"
		@echo "  fclean:           remove all generated files"
		@echo "  re:               remove all generated files and recompile library"

s21_matrix_oop.a: $(OBJS)
		@clear
		ar rcs $(LIB_NAME) $(OBJS)

%.o: %.cc $(HEADERS)
		$(CC) $(CPP_FLAGS) -c $< -o $@

test: $(SRC_TEST) $(LIB_NAME)
		@clear
		$(CC) $(CPP_FLAGS) $(GTEST_FLAGS) $(SRC_TEST) $(LIB_NAME) -o $(TEST_NAME).out
		./$(TEST_NAME).out

gcov_report: $(LIB_NAME)
		@clear
		$(CC) $(CPP_FLAGS) $(GTEST_FLAGS) $(GCOV_FLAGS) $(SRC_TEST) $(SRCS) -o $(REPORT)
		./$(REPORT)
		lcov -t "$(REPORT)" -o $(REPORT).info -c -d .
		genhtml -o report $(REPORT).info
		rm -rf ./*.gcno ./*.gcda ./$(REPORT).*
		@echo Code coverage report generated. To view the report via web-browser, enter the command \"open ./report/index.html\"

open: gcov_report
		@clear
		open ./report/index.html

lint: $(SRCS) $(HEADERS) $(SRC_TEST)
		clang-format -i $(SRCS) $(HEADERS) $(SRC_TEST)

check: $(LIB_NAME)
		@clear
		@echo ---------------------CPPCHECK---------------------
		cppcheck --language=c++ --enable=all --suppress=missingIncludeSystem . $(HEADERS) $(SRCS) $(SRC_TEST)
		@echo -------------------CLANG-FORMAT-------------------
		clang-format -n $(SRCS) $(HEADERS) $(SRC_TEST)
		@echo -------------------MEMORY_LEAKS-------------------
		$(CC) $(CPP_FLAGS) $(GTEST_FLAGS) -g $(SRC_TEST) $(LIB_NAME) -o $(TEST_NAME).out
		CK_FORK=no leaks --atExit -- ./$(TEST_NAME).out

check_valgrind: $(LIB_NAME)
		@clear
		@echo -------------------MEMORY_LEAKS-------------------
		$(CC) $(CPP_FLAGS) $(GTEST_FLAGS) -g $(SRC_TEST) $(LIB_NAME) -o $(TEST_NAME).out
		CK_FORK=no valgrind --leak-check=full -s ./$(TEST_NAME).out

clean:
		rm -rf $(OBJS) $(TEST).out $(TEST_NAME).out *.gcda *.gcno $(TEST_NAME).out.dSYM report $(REPORT)
		@clear

fclean: clean
		rm -rf $(LIB_NAME)
		@clear

re:
		$(MAKE) fclean
		$(MAKE) $(LIB_NAME)

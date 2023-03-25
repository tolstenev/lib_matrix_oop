#
# Copyright (с) 2023 Student of School 21:
# Gleb Tolstenev
#
# yonnarge@student.21-school.ru
#

# Makefile for s21_matrix_oop.a

# Make targets:
#   - s21_matrix_oop.a:	create the static library
#   - test:				run unit test of library and show results
#   - check:            check source files by 'cppcheck', 'clang-format', and looking for memory leaks by 'leaks'
#   - clean:			remove generated files without s21_matrix_oop.a
#   - fclean:			remove all generated files
#   - re:				remove all generated files and recompile library

NAME	:= s21_matrix_oop.a
HEADER	:= s21_matrix_oop.h

CC		:= gcc
CFLAGS	:= -lstdc++ -std=c++17 -pedantic -Wall -Werror -Wextra
SRCS	:= s21_matrix_oop.cpp
OBJS	:= $(SRCS:.cpp=.o)
TEST	:= test

.PHONY: all test check check_valgrind clean fclean re

all: s21_matrix_oop.a

info:
		@echo "Available make targets:"
		@echo "  s21_matrix_oop.a: create the static library"
		@echo "  test:             run unit test of library and show results"
		@echo "  check:            check source files by 'cppcheck', 'clang-format', and looking for memory leaks by 'leaks'"
		@echo "  clean:            remove generated files without s21_matrix_oop.a"
		@echo "  fclean:           remove all generated files"
		@echo "  re:               remove all generated files and recompile library"

s21_matrix_oop.a: $(OBJS)
		@clear
		ar rcs $(NAME) $(OBJS)

%.o: %.cpp $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

test: $(NAME)
		@clear
		$(CC) $(CFLAGS) $(SRCS) $(NAME) -o $(TEST).out
		./$(TEST).out

lint: $(NAME)
		clang-format -i $(SRCS) $(HEADER)

check: $(NAME)
		@clear
		@echo ---------------------CPPCHECK---------------------
		cppcheck --language=c++ --enable=all --suppress=missingIncludeSystem . $(HEADER) $(SRCS)
		@echo -------------------CLANG-FORMAT-------------------
		clang-format -n $(SRCS) $(HEADER)
		@echo -------------------MEMORY_LEAKS-------------------
		$(CC) $(CFLAGS) -g $(SRCS) $(NAME) -o $(TEST).out
		CK_FORK=no leaks --atExit -- ./$(TEST).out

check_valgrind: $(NAME)
		@clear
		@echo -------------------MEMORY_LEAKS-------------------
		$(CC) -g $(SRC_TEST) $(NAME) $(CHECK_FLAGS) -o $(TEST)
		CK_FORK=no valgrind --leak-check=full -s ./$(TEST)

clean:
		rm -rf $(OBJS) ./$(TEST).out
		@clear

fclean: clean
		rm -rf $(NAME)
		@clear

re:
		$(MAKE) fclean
		$(MAKE) $(NAME)

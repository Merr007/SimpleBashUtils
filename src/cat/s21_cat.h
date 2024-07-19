#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
  bool num_nonblank;
  bool print_end_of_line;
  bool num_all;
  bool squeeze;
  bool print_tabs;
  bool print_non_printable;
} my_flags;

bool print_file(char *file, my_flags flags);
void print_sym(char sym, my_flags flags);
bool read_flags(int argc, char **argv, my_flags *flags);
void read_no_args(int input_src);

#endif

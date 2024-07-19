#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 10000

typedef struct {
  int regex_flags;
  int files_count;
  int e_counter;
  bool get_line_regex;
  bool invert;
  bool count_match;
  bool print_match_files;
  bool print_num_of_line;
  bool print_match_no_filename;
  bool supress_errors;
  bool regexp_from_file;
  bool print_only_match;
} my_flags;

bool read_flags(int argc, char **argv, my_flags *flags, char *pattern);
void grep_execute(int argc, char **argv, my_flags *flags, char *pattern);
bool get_from_file(char *full_pattern, char *pattern, my_flags flags);
void grep_files(my_flags flags, regex_t regex, char *filename);
void get_from_console(char *pattern, my_flags flags);
void print_usage();

#endif

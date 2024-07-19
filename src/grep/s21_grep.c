#include "s21_grep.h"

int main(int argc, char **argv) {
  bool err_flag = false;
  char pattern[BUFFER_SIZE] = {0};
  my_flags flags;
  memset(&flags, 0, sizeof(flags));
  err_flag = read_flags(argc, argv, &flags, pattern);
  if (argc >= 3 && !err_flag) {
    grep_execute(argc, argv, &flags, pattern);
  } else {
    print_usage();
  }

  return 0;
}

bool read_flags(int argc, char **argv, my_flags *flags, char *pattern) {
  bool err_flag = false;
  int curr_flag = 0;
  const char *opts = "e:ivclnhsf:o";
  while ((curr_flag = getopt(argc, argv, opts)) != -1) {
    if (curr_flag == 'e') {
      flags->regex_flags |= REG_EXTENDED;
      flags->get_line_regex = true;
      flags->e_counter++;
      get_from_console(pattern, *flags);
    } else if (curr_flag == 'i') {
      flags->regex_flags |= REG_ICASE;
    } else if (curr_flag == 'v') {
      flags->invert = true;
    } else if (curr_flag == 'c') {
      flags->count_match = true;
    } else if (curr_flag == 'l') {
      flags->print_match_files = true;
    } else if (curr_flag == 'n') {
      flags->print_num_of_line = true;
    } else if (curr_flag == 'h') {
      flags->print_match_no_filename = true;
    } else if (curr_flag == 's') {
      flags->supress_errors = true;
    } else if (curr_flag == 'f') {
      flags->regexp_from_file = true;
      flags->regex_flags |= REG_EXTENDED;
      snprintf(pattern, BUFFER_SIZE, "%s", optarg);
    } else if (curr_flag == 'o') {
      flags->print_only_match = true;
    } else {
      err_flag = true;
      if (!flags->supress_errors) {
        fprintf(stderr, "s21_grep: invalid option -- %c", curr_flag);
      }
    }
  }
  return err_flag;
}

void print_usage() {
  fprintf(stderr,
          "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
          "[-C[num]]\n");
  fprintf(stderr,
          "\t[-e pattern] [-f file] [--binary-files=value] [--color=when]\n");
  fprintf(stderr,
          "\t[--context[=num]] [--directories=action] [--label] "
          "[--line-buffered]\n");
  fprintf(stderr, "\t[--null] [pattern] [file ...]\n");
}

void get_from_console(char *pattern, my_flags flags) {
  if (flags.e_counter > 1) strcat(pattern, "|");
  strcat(pattern, optarg);
}

void grep_execute(int argc, char **argv, my_flags *flags, char *pattern) {
  char full_pattern[BUFFER_SIZE] = {0};
  bool read_err = false;
  regex_t regex;

  if (!flags->regexp_from_file && !flags->get_line_regex) {
    snprintf(full_pattern, BUFFER_SIZE, "%s", argv[optind++]);
  }

  if (flags->regexp_from_file) {
    read_err = get_from_file(full_pattern, pattern, *flags);
  }

  if (!flags->regexp_from_file && flags->get_line_regex) {
    snprintf(full_pattern, BUFFER_SIZE, "%s", pattern);
  }

  regcomp(&regex, full_pattern, flags->regex_flags);
  if (!read_err) {
    flags->files_count = argc - optind;
    for (int i = optind; i < argc; i++) {
      grep_files(*flags, regex, argv[i]);
    }
  }
  regfree(&regex);
}

bool get_from_file(char *full_pattern, char *pattern, my_flags flags) {
  FILE *fp = fopen(pattern, "r");
  bool err_flag = false;
  int index = 0;

  if (fp != NULL) {
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
      if (ch == 13 || ch == 10) {
        full_pattern[index++] = '|';
      } else {
        full_pattern[index++] = ch;
      }
    }

    if (full_pattern[index - 1] == '|') {
      full_pattern[index - 1] = '\0';
    }
    fclose(fp);
  } else {
    err_flag = true;
    if (!flags.supress_errors) {
      fprintf(stderr, "s21_grep: %s: No such file or directory\n", pattern);
    }
  }
  return err_flag;
}

void grep_files(my_flags flags, regex_t regex, char *filename) {
  FILE *fp = fopen(filename, "r");

  if (fp != NULL) {
    char *line = NULL;
    size_t len = 0;
    int line_matches = 0, num_of_line = 1;
    regmatch_t pmatch[1];

    if (flags.count_match && flags.files_count > 1 &&
        !flags.print_match_no_filename)
      printf("%s:", filename);

    while (getline(&line, &len, fp) != -1) {
      int match = 0, stat = regexec(&regex, line, 1, pmatch, 0);

      if (stat == 0 && !flags.invert) match = 1;
      if (stat == REG_NOMATCH && flags.invert) match = 1;
      if ((match && flags.files_count > 1 && !flags.print_match_no_filename &&
           !flags.print_match_files) &&
          !(flags.count_match && flags.invert)) {
        printf("%s:", filename);
      }
      if (match && !flags.print_match_files && !flags.count_match &&
          flags.print_num_of_line)
        printf("%d:", num_of_line);
      if (match && !flags.print_match_files && !flags.count_match &&
          !flags.print_only_match) {
        printf("%s", line);
        if (line[strlen(line) - 1] != '\n') {
          printf("\n");
        }
      }

      if (flags.print_only_match && match && !flags.invert) {
        for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) {
          printf("%c", line[i]);
        }
        printf("\n");
      } else if (flags.print_only_match && match && flags.invert) {
        printf("%s", line);
        if (line[strlen(line) - 1] != '\n') {
          printf("\n");
        }
      }
      line_matches += match;
      num_of_line++;
    }
    if (flags.print_match_files && line_matches > 0) printf("%s\n", filename);
    if (flags.count_match) printf("%d\n", line_matches);
    if (fp) fclose(fp);
    if (line) free(line);

  } else {
    if (!flags.supress_errors) {
      fprintf(stderr, "s21_grep: %s: No such file or directory\n", filename);
    }
  }
}

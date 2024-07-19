#include "s21_cat.h"

int main(int argc, char **argv) {
  int err_flag = 0;
  if (argc == 1) {
    read_no_args(STDIN_FILENO);
  } else {
    my_flags flags = {false};
    err_flag = read_flags(argc, argv, &flags);
    if (flags.num_nonblank) flags.num_all = false;
    for (int i = optind; !err_flag && i < argc; i++) {
      if (!print_file(argv[i], flags)) {
        printf("s21_cat: %s: No such file or directory\n", argv[i]);
        break;
      }
    }
  }

  return err_flag;
}

void read_no_args(int input_src) {
  char buffer[4096];
  int bytes;
  while ((bytes = read(input_src, buffer, sizeof(buffer))) > 0) {
    printf("%.*s", bytes, buffer);
  }
}

bool read_flags(int argc, char **argv, my_flags *flags) {
  int err_flag = 0, curr_flag = 0;
  const char *short_opts = "beEnstTv";
  const struct option long_opts[] = {{"number-nonblank", 0, NULL, 'b'},
                                     {"number", 0, NULL, 'n'},
                                     {"squeeze-blank", 0, NULL, 's'},
                                     {NULL, 0, NULL, 0}};
  while ((curr_flag = getopt_long(argc, argv, short_opts, long_opts, NULL)) !=
         -1) {
    if (curr_flag == 'b') {
      flags->num_nonblank = true;
    }
    if (curr_flag == 'n') {
      flags->num_all = true;
    }
    if (curr_flag == 's') {
      flags->squeeze = true;
    }
    if (curr_flag == 'v') {
      flags->print_non_printable = true;
    }
    if (curr_flag == 'e') {
      flags->print_non_printable = true;
      flags->print_end_of_line = true;
    }
    if (curr_flag == 'E') {
      flags->print_end_of_line = true;
    }
    if (curr_flag == 't') {
      flags->print_non_printable = true;
      flags->print_tabs = true;
    }
    if (curr_flag == 'T') {
      flags->print_tabs = true;
    }
    if (curr_flag == '?') {
      err_flag = -1;
      printf("usage: s21_cat [-beEnstTv] [file ...]\n");
      break;
    }
  }
  return err_flag;
}

bool print_file(char *file, my_flags flags) {
  bool isValid = true;
  FILE *fp = fopen(file, "r");
  if (fp != NULL) {
    int sym;
    while ((sym = fgetc(fp)) != EOF) {
      print_sym(sym, flags);
    }
    if (fp != NULL) {
      fclose(fp);
    }

  } else {
    isValid = false;
  }
  return isValid;
}

void print_sym(char sym, my_flags flags) {
  static int last = '\n';
  static int line_num = 0;
  static bool is_squeezable = false;
  if (!(flags.squeeze && last == '\n' && sym == '\n' && is_squeezable)) {
    is_squeezable = last == '\n' && sym == '\n' ? true : false;

    if ((flags.num_all || (flags.num_nonblank && sym != '\n')) &&
        last == '\n') {
      line_num++;
      printf("%6d\t", line_num);
    }

    if (flags.print_end_of_line && sym == '\n') {
      printf("$");
    }

    if (flags.print_tabs && sym == '\t') {
      printf("^");
      sym += 64;
    }

    if (flags.print_non_printable) {
      if (sym < 32 && sym != 10 && sym != 9) {
        printf("^");
        sym += 64;
      }

      if (sym == 127) {
        printf("^");
        sym = '?';
      }

      if ((unsigned char)sym > 127) {
        printf("M-");
        sym -= 128;
      }
    }
    printf("%c", sym);
  }
  last = sym;
}

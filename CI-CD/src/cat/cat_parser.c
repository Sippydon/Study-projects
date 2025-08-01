#include "cat_flags.h"

//#include "cat_parser.h"
#include "getopt.h"
#include "string.h"

int parser(int argc, char *argv[], struct Flags *flags) {
  int c = 0;

  struct option long_options[] = {{"number-nonblank", 1, 0, 0},
                                  {"number", 1, 0, 0},
                                  {"squeeze-blank", 1, 0, 0}};

  while (c != -1) {
    int opt_index = 0;
    c = getopt_long(argc, argv, "beEnstT", long_options, &opt_index);

    if (c == 0) {
      if (!strcmp(long_options[opt_index].name, "number-nonblank")) {
        flags->gnuB = 1;
      } else if (!strcmp(long_options[opt_index].name, "number")) {
        flags->gnuN = 1;
      } else if (!strcmp(long_options[opt_index].name, "squeeze-blank")) {
        flags->gnuS = 1;
      } else {
      }
    } else if (c == 'b') {
      flags->b = 1;
    } else if (c == 'e') {
      flags->e = 1;
    } else if (c == 'E') {
      flags->gnuE = 1;
    } else if (c == 'n') {
      flags->n = 1;
    } else if (c == 's') {
      flags->s = 1;
    } else if (c == 't') {
      flags->t = 1;
    } else if (c == 'T') {
      flags->gnuT = 1;
    } else {
      flags->error = 1;
    }
  }

  return optind;
}

#include "flags.h"

//#include "grep_parser.h"
#include "getopt.h"
#include "string.h"

int parser(int argc, char *argv[], struct Flags *flags) {
  int c;
  int firstUseE = 1;

  while ((c = getopt(argc, argv, "e:ivclnhsof:")) != -1) {
    opterr = 0;
    if (c == 'e') {
      flags->e = 1;
      if (firstUseE) {
        firstUseE = 0;
        strcat(flags->pattern, optarg);
      } else {
        strcat(flags->pattern, "|");
        strcat(flags->pattern, optarg);
      }
    } else if (c == 'i') {
      flags->i = 1;
    } else if (c == 'v') {
      flags->v = 1;
    } else if (c == 'c') {
      flags->c = 1;
    } else if (c == 'l') {
      flags->l = 1;
    } else if (c == 'n') {
      flags->n = 1;
    } else if (c == 'h') {
      flags->h = 1;
    } else if (c == 's') {
      flags->s = 1;
    } else if (c == 'f') {
      flags->f = 1;
      flags->file_name = optarg;
    } else if (c == 'o') {
      flags->o = 1;
    } else if (c == '?') {
      flags->err = 1;
    }
  }

  if (flags->e == 0 && flags->f == 0 && flags->err == 0) {
    flags->pattern = argv[optind];
    optind++;
  }

  return optind;
}
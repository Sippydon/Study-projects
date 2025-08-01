//
// Created by Sippy Dong on 10/29/22.
//

#include "cat_flags.h"
//#include "cat_parser.h"
#include "stdio.h"

void flagsHandler(char *, struct Flags, struct Counters *);
void bFlagHandler(char, struct Counters *);
void eFlagHandler(char, struct Counters *, struct Flags);
void gnuEFlagHandler(char, struct Counters *, struct Flags);
void nFlagHandler(char, struct Counters *);
void sFlagHandler(char, struct Counters *);
void tFlagCounter(char *, struct Counters *, struct Flags);
void gnuTFlagCounter(char *, struct Counters *);

void mainHandler(int argc, char *argv[]) {
  char c;
  int file_pos;
  int non_blank_counter;
  FILE *file;
  struct Flags flags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  file_pos = parser(argc, argv, &flags);
  while (file_pos != argc) {
    if ((file = fopen(argv[file_pos], "r")) == NULL) {
      printf("%s: %s: No such file or directory\n", argv[0], argv[file_pos]);
    } else {
      struct Counters counters = {0, 1, -1, 0};
      while ((c = fgetc(file)) != EOF) {
        flagsHandler(&c, flags, &counters);
        if (counters.skip_line <= 1) {
          printf("%c", c);
        }
        counters.previous_char = c;
      }
    }
    fclose(file);
    file_pos++;
  }
}

void flagsHandler(char *c, struct Flags flags, struct Counters *counters) {
  if (flags.b == 1 || flags.gnuB == 1) {
    bFlagHandler(*c, counters);
  }

  if (flags.s == 1 || flags.gnuS == 1) {
    sFlagHandler(*c, counters);
  }

  if ((flags.n == 1 || flags.gnuN == 1) && (flags.b == 0 && flags.gnuB == 0)) {
    nFlagHandler(*c, counters);
  }

  if (flags.e == 1) {
    eFlagHandler(*c, counters, flags);
  } else if (flags.gnuE == 1) {
    gnuEFlagHandler(*c, counters, flags);
  }

  if (flags.t == 1) {
    tFlagCounter(c, counters, flags);
  } else if (flags.gnuT == 1) {
    gnuTFlagCounter(c, counters);
  }
}

void bFlagHandler(char c, struct Counters *counters) {
  if ((counters->previous_char == '\n' || counters->previous_char == -1) &&
      (c != '\n')) {
    printf("%6d\t", counters->line_counter);
    counters->line_counter += 1;
  }
}

void eFlagHandler(char c, struct Counters *counters, struct Flags flags) {
  if (c == '\n' && counters->skip_line <= 1) {
    printf("$");
  } else if ((c / 32) < 1 && (flags.t == 0 && flags.gnuT == 0) && (c != 10) &&
             (c != 9)) {
    printf("^");
  } else if ((c / 32) < 1 && (flags.gnuT == 1) && c != 9 && c != 10) {
    printf("^");
  }
}

void gnuEFlagHandler(char c, struct Counters *counters, struct Flags flags) {
  if (c == 10) {
    printf("$");
  }
}

void nFlagHandler(char c, struct Counters *counters) {
  if ((counters->previous_char == '\n' || counters->previous_char == -1) &&
      counters->skip_line <= 1) {
    printf("%6d\t", counters->line_counter);
    counters->line_counter += 1;
  }
}

void sFlagHandler(char c, struct Counters *counters) {
  if (counters->previous_char == '\n' && c == '\n') {
    counters->skip_line += 1;
  }
  if (counters->skip_line >= 1 && c != '\n') {
    counters->skip_line = 0;
  }
}

void tFlagCounter(char *c, struct Counters *counters, struct Flags flags) {
  if (*c == 9) {
    printf("^");
    *c = 'I';
  } else if ((*c / 32) < 1 && (flags.e == 0 && flags.gnuE == 0) && *c != 10) {
    printf("^");
  } else if ((*c / 32) < 1 && (flags.e == 1 || flags.gnuE == 1) && *c != 9 &&
             *c != 10) {
    printf("^");
  }
}

void gnuTFlagCounter(char *c, struct Counters *counters) {
  if (*c == 9) {
    printf("^");
    *c = 'I';
  }
}
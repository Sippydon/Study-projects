//
// Created by Sippy Dong on 10/29/22.
//

#ifndef CAT_GREP_CAT_FLAGS_H
#define CAT_GREP_CAT_FLAGS_H

struct Flags {
  int b;
  int gnuB;
  int e;
  int gnuE;
  int n;
  int gnuN;
  int s;
  int gnuS;
  int t;
  int gnuT;
  int V;
  int error;
};

struct Counters {
  int non_blanc_counter;
  int line_counter;
  char previous_char;
  int skip_line;
};

int parser(int argc, char *argv[], struct Flags *flags);

#endif // CAT_GREP_CAT_FLAGS_H

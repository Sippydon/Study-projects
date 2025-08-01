//
// Created by Sippy Dong on 11/15/22.
//

#ifndef CAT_GREP_FLAGS_H
#define CAT_GREP_FLAGS_H
struct Flags {
  int e;
  char *pattern;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  char *file_name;
  int o;
  int err;
};

int parser(int, char **, struct Flags *);
int flagHandler(int argc, char *argv[], struct Flags flags, int option_index);

#endif // CAT_GREP_FLAGS_H

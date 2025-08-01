#include "flags.h"
#include "grep_func.h"
#include "grep_parser.h"
#include "stdio.h"

int main(int argc, char *argv[]) {
  char tmp[2048];
  struct Flags flags = {0, tmp, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int option_index;

  option_index = parser(argc, argv, &flags);
  if (flags.err == 0) {
    flagHandler(argc, argv, flags, option_index);
  }

  return 0;
}
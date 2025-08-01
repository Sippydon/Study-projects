#ifndef SRC_POLISH_H_
#define SRC_POLISH_H_
#include <ctype.h>
#include <string.h>

#include "stack.h"

#define is_operator(ch)                                             \
  (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^' || \
   ch == '(' || ch == ')')
#define is_operators(ch)                                            \
  (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^' || \
   ch == '(' || ch == 'o' || ch == 's' || ch == 'a' || ch == 'c' || \
   ch == 't' || ch == 'q' || ch == 'l' || ch == 'g' || ch == 'm' || ch == 'n')

#define is_prefix_f(ch)                                             \
  (ch == '~' || ch == 'o' || ch == 's' || ch == 'a' || ch == 'c' || \
   ch == 't' || ch == 'q' || ch == 'l' || ch == 'g' || ch == 'n')

#define is_binar_f(ch) \
  (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^' || ch == 'm')

int reverse_polish(char *src, char *dst);
int reduce_infix(char *src, char *dst);
int check_brackets(char *src);
int set_prior(char ch);
int set_associative(char ch);
int parse_digs(char *src, char *dst, int *i, int *j);
void is_unary(char *src, int i);
int insertArgX(char *dst, int j, double *argX);
int isValid(char *str);

#endif

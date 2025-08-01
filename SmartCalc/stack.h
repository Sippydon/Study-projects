#ifndef STACK_H_
#define STACK_H_
#include <stdio.h>
#include <stdlib.h>

#include "polish.h"

typedef struct node {
  char ch;
  int priority;
  int associative;  // 1 - left // 0 - rigth
  struct node *next;
} Stack_o;

typedef struct noden {
  double value;
  struct noden *next;
} Stack_n;

Stack_o *push_o(char c, Stack_o *root);
char pop_o(Stack_o **root);

Stack_n *push_n(double input, Stack_n *root);
double pop_n(Stack_n **root);

#endif

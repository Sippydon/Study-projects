#include "stack.h"

Stack_o *push_o(char c, Stack_o *root) {
  Stack_o *tmp = malloc(sizeof(Stack_o));
  tmp->priority = set_prior(c);
  tmp->associative = set_associative(c);
  tmp->ch = c;
  tmp->next = root;
  return tmp;
}

char pop_o(Stack_o **root) {
  Stack_o *tmp = *root;
  char c;
  if (*root == NULL) {
    c = '\0';
  } else {
    c = tmp->ch;
    *root = tmp->next;
    free(tmp);
  }
  return c;
}

Stack_n *push_n(double input, Stack_n *root) {
  Stack_n *tmp = malloc(sizeof(Stack_n));

  tmp->value = input;
  tmp->next = root;
  return tmp;
}

double pop_n(Stack_n **root) {
  Stack_n *tmp = *root;
  double output;
  if (*root == NULL) {
    output = 0;
  } else {
    output = tmp->value;
    *root = tmp->next;
    free(tmp);
  }
  return output;
}

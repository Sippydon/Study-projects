#include "polish.h"

#include "stack.h"

int reverse_polish(char *tsrc, char *dst) {
  Stack_o *opers = NULL;
  char src[512];
  int j = 0;
  int flag = check_brackets(tsrc) && reduce_infix(tsrc, src);
  if (flag) {
    for (int i = 0; src[i] != '\0' && i < 256 && flag;) {
      if (src[i] == '.' || isdigit(src[i])) flag = parse_digs(src, dst, &i, &j);
      if (src[i] == 'x') {
        dst[j++] = src[i++];
        dst[j++] = ' ';
      }

      if (is_prefix_f(src[i])) opers = push_o(src[i++], opers);

      if (src[i] == '(') opers = push_o(src[i++], opers);

      if (src[i] == ')') {
        while (opers != NULL && opers->ch != '(') {
          dst[j++] = pop_o(&opers);
          dst[j++] = ' ';
        }
        if (opers != NULL)
          pop_o(&opers);
        else
          flag = 0;
        i++;
      }
      if (is_binar_f(src[i])) {
        while (opers != NULL &&
               (is_prefix_f(opers->ch) ||
                (set_prior(src[i]) <= opers->priority) ||
                (opers->associative && set_prior(src[i]) == opers->priority))) {
          dst[j++] = pop_o(&opers);
          dst[j++] = ' ';
        }
        opers = push_o(src[i++], opers);
      }
      if (src[i] == ' ') i++;
    }
    while (opers != NULL) {
      dst[j++] = pop_o(&opers);
      dst[j++] = ' ';
    }
    dst[--j] = '\0';
  } else
    dst = NULL;

  return flag;
}

int reduce_infix(char *src, char *dst) {
  int error = 1;
  int i = 0, j = 0;
  for (; src[j] != '\0' && error; j++) {
    if (!strncmp(src + j, "sin(", 4)) {
      dst[i++] = 's';
      dst[i++] = ' ';
      j += 2;
    } else if (!strncmp(src + j, "cos(", 4)) {
      dst[i++] = 'c';
      dst[i++] = ' ';
      j += 2;
    } else if (!strncmp(src + j, "tan(", 4)) {
      dst[i++] = 't';
      dst[i++] = ' ';
      j += 2;
    } else if (!strncmp(src + j, "atan(", 5)) {
      dst[i++] = 'a';
      dst[i++] = ' ';
      j += 3;
    } else if (!strncmp(src + j, "acos(", 5)) {
      dst[i++] = 'o';
      dst[i++] = ' ';
      j += 3;
    } else if (!strncmp(src + j, "asin(", 5)) {
      dst[i++] = 'n';
      dst[i++] = ' ';
      j += 3;
    } else if (!strncmp(src + j, "sqrt(", 5)) {
      dst[i++] = 'q';
      dst[i++] = ' ';
      j += 3;
    } else if (!strncmp(src + j, "log(", 4)) {
      dst[i++] = 'g';
      dst[i++] = ' ';
      j += 2;
    } else if (!strncmp(src + j, "ln(", 3)) {
      dst[i++] = 'l';
      dst[i++] = ' ';
      j++;
    } else if (!strncmp(src + j, "mod", 3)) {
      dst[i++] = 'm';
      dst[i++] = ' ';
      j += 2;
    } else if (is_operator(src[j]) || src[j] == 'x') {
      dst[i] = src[j];
      is_unary(dst, i);
      i++;
      dst[i++] = ' ';

    } else if (isdigit(src[j]) || src[j] == '.') {
      error = parse_digs(src, dst, &j, &i);
      j--;
    } else if (src[j] == ' ')
      continue;
    else
      error = 0;
  }
  i--;
  dst[i] = '\0';

  return error;
}

int check_brackets(char *src) {
  int count = 0;
  for (int i = 0; src[i] != '\0'; i++) {
    if (src[i] == '(')
      count++;
    else if (src[i] == ')')
      count--;
  }
  return !count;
}

int set_prior(char ch) {
  int priority = -1;
  switch (ch) {
    case '^':
      priority = 3;
      break;
    case 's':
    case 'c':
    case 't':
    case 'q':
    case 'l':
    case 'o':
    case 'n':
    case 'a':
    case 'g':
    case '~':
      priority = 4;
      break;
    case '*':
    case 'm':
    case '/':
      priority = 2;
      break;
    case '-':
    case '+':
      priority = 1;
      break;
    default:
      break;
  }
  return priority;
}

int set_associative(char ch) {  // 1 - left // 0 - rigth
  int associative = -1;
  switch (ch) {
    case '*':
    case '/':
    case '+':
    case '-':
    case 'm':
      associative = 0;
      break;
    case '^':
      associative = 1;
      break;
    default:
      break;
  }
  return associative;
}

int parse_digs(char *src, char *dst, int *i, int *j) {
  int temp_i = *i;
  int temp_j = *j;
  int error = 1;
  int dot_count = 0;
  while ((isdigit(src[temp_i]) || src[temp_i] == '.') && error) {
    if (src[temp_i] == '.') dot_count++;
    if (dot_count > 1) error = 0;
    dst[temp_j++] = src[temp_i++];
  }
  dst[temp_j++] = ' ';
  *i = temp_i;
  *j = temp_j;
  return error;
}

void is_unary(char *src, int i) {
  if (src[i] == '-' || src[i] == '+') {
    int temp_i = i;
    char change = (src[i] == '-') ? '~' : ' ';
    if (!i)
      src[temp_i] = change;
    else {
      i ? i-- : 0;
      for (; i > 0 && src[i] == ' ';) i--;
      if (is_binar_f(src[i]) || src[i] == '(') src[temp_i] = change;
    }
  }
}

int isValid(char *str) {
  char tsrc[512];
  int flag = check_brackets(str) && reduce_infix(str, tsrc);
  return flag;
}

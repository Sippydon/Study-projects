#include "calculate.h"

int SmartCalc(char *inputStr, double *result, double *argX) {
  char RpnStr[512];
  double valueX = 0;
  if (argX != NULL) valueX = *argX;
  int flag = 0;
  flag = reverse_polish(inputStr, RpnStr);
  if (flag) flag = calculate(RpnStr, result, valueX);
  return flag;
}

int calculate(char *src, double *result, double valX) {
  int flag = 1;
  Stack_n *nums = NULL;

  for (int i = 0; src[i] != '\0'; i++) {
    if (isdigit(src[i]) || src[i] == '.') {
      char num_buf[25] = "";
      int j = 0;
      parse_digs(src, num_buf, &i, &j);
      nums = push_n(atof(num_buf), nums);
    } else if (is_binar_f(src[i]) || is_prefix_f(src[i]))
      flag = calc_func(src[i], &nums);
    else if (src[i] == 'x') {
      nums = push_n(valX, nums);
    }
  }
  *result = pop_n(&nums);

  return flag;
}

int calc_func(char ch, Stack_n **nums) {
  int flag = 1;
  double bin_res, a, b;

  if (is_binar_f(ch)) {
    if (*nums != NULL) {
      a = pop_n(nums);
      if (*nums != NULL)
        b = pop_n(nums);
      else
        flag = 0;
    } else
      flag = 0;

    if (flag) {
      switch (ch) {
        case '+':
          bin_res = a + b;
          break;
        case '-':
          bin_res = b - a;
          break;
        case '*':
          bin_res = b * a;
          break;
        case '/':
          bin_res = b / a;
          break;
        case '^':
          bin_res = pow(b, a);
          break;
        case 'm':
          bin_res = fmod(b, a);
          break;
      }
    }
  } else {
    if (*nums != NULL)
      a = pop_n(nums);
    else
      flag = 0;

    if (flag) {
      switch (ch) {
        case 's':
          bin_res = sin(a);
          break;
        case 'c':
          bin_res = cos(a);
          break;
        case 't':
          bin_res = tan(a);
          break;
        case 'a':
          bin_res = atan(a);
          break;
        case 'o':
          bin_res = acos(a);
          break;
        case 'n':
          bin_res = asin(a);
          break;
        case 'q':
          bin_res = sqrt(a);
          break;
        case 'g':
          bin_res = log10(a);
          break;
        case 'l':
          bin_res = log(a);
          break;
        case '~':
          bin_res = -1 * a;
          break;
      }
    }
  }
  if (flag) *nums = push_n(bin_res, *nums);

  return flag;
}

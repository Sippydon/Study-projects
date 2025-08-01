#ifndef CALCULATE_H_
#define CALCULATE_H_

#include <math.h>

#include "polish.h"
#include "stack.h"

int calculate(char *src, double *result, double valX);

int calc_func(char ch, Stack_n **nums);

int SmartCalc(char *inputStr, double *result, double *argX);

#endif

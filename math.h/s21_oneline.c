#include "s21_math.h"

int s21_is_nan(double x) { return x != x; }

int s21_is_inf(double x) { return (x == S21_INF) - (x == -S21_INF); }

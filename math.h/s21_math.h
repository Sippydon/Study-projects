#ifndef SRC_s21_MATH_H_
#define SRC_s21_MATH_H_

#include <float.h>
#include <stdio.h>

#define S21_PI 3.14159265358979323846
#define S21_PI_2 1.57079632679489661923
#define S21_PI_4 0.785398163397448309616
#define S21_LOG2E 1.44269504088896340736
#define S21_LOG10E 0.434294481903251827651

#define S21_LN2 0.693147180559945309417
#define S21_LN10 2.30258509299404568402

#define S21_SQRT2 1.41421356237309504880

#define S21_EPS 1e-16
#define S21_E 2.71828182845904523536
#define S21_MAX_DOUBLE 1.7976931348623158e+308
#define S21_MAX_INT 2147483647
#define S21_INF 1.0 / 0.0
#define S21_NAN 0.0 / 0.0

int s21_is_nan(double x);
int s21_is_inf(double x);

int s21_abs(int x);
long double s21_sin(double x);
long double s21_cos(double x);
long double s21_tan(double x);
long double s21_ceil(double x);
long double s21_floor(double x);
long double s21_atan(double x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_fmod(double x, double y);
long double s21_exp(double x);
long double s21_log(double x);
long double s21_sqrt(double x);
long double s21_pow(double base, double exp1);
long double s21_fabs(double x);

#endif  // SRC_s21_MATH_H_

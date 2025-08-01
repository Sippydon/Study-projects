#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define TOLERANCY 0.000001

#include "s21_math.h"

/*
will need now
int: от –32768 до 32767 (при 2 байтах) или от −2 147 483 648 до 2 147 483 647
(при 4 байтах) float: от -3.4E+38 до -3.4E-38 И от +3.4E+38 до +3.4E-38 double:
от -1.7E-308 до -1.7E+308 И от +1.7E-308 до +1.7E+308
*/

static const int abs_primes[10] = {0,  -0,     1,     -1,        -21,
                                   21, -10000, 10000, INT32_MAX, INT32_MIN};

static const double inf_primes[2] = {S21_INF, -S21_INF};

static const double neg_nums_primes[8] = {
    -0.5, -1, -21, -21.0001, -10000, -123456.12345, -0.99999, -0.0001};

static const double pos_nums_primes[8] = {
    0, 1, 21, 21.0001, 10000, 123456.12345, 0.99999, 0.0001};

START_TEST(abs_test1) {  // дополнено
  ck_assert_int_eq(s21_abs(abs_primes[_i]), abs(abs_primes[_i]));
}
END_TEST

START_TEST(ceil_test1) {  // дополнено
  ck_assert_ldouble_eq_tol(s21_ceil(neg_nums_primes[_i]),
                           ceil(neg_nums_primes[_i]), TOLERANCY);
}
END_TEST

START_TEST(ceil_test2) {  // дополнено
  ck_assert_ldouble_eq_tol(s21_ceil(pos_nums_primes[_i]),
                           ceil(pos_nums_primes[_i]), TOLERANCY);
}
END_TEST

START_TEST(ceil_test3) {  // дополнено
  ck_assert_ldouble_eq(s21_ceil(inf_primes[_i]), ceil(inf_primes[_i]));
}
END_TEST

START_TEST(ceil_test_nan) {  // дополнено
  ck_assert_double_nan(s21_ceil(S21_NAN));
}
END_TEST

START_TEST(fabs_test1) {  // дополнено
  ck_assert_ldouble_eq_tol(s21_fabs(pos_nums_primes[_i]),
                           fabs(pos_nums_primes[_i]), TOLERANCY);
}
END_TEST

START_TEST(fabs_test2) {  // дополнено
  ck_assert_ldouble_eq_tol(s21_fabs(neg_nums_primes[_i]),
                           fabs(neg_nums_primes[_i]), TOLERANCY);
}
END_TEST

START_TEST(fabs_test_nan) {  // дополнено
  ck_assert_ldouble_nan(s21_fabs(S21_NAN));
}
END_TEST

START_TEST(fabs_test_inf) {  // дополнено
  ck_assert_ldouble_eq(s21_fabs(inf_primes[_i]), fabs(inf_primes[_i]));
}
END_TEST

START_TEST(floor_test1) {
  ck_assert_ldouble_eq_tol(s21_floor(pos_nums_primes[_i]),
                           floor(pos_nums_primes[_i]), TOLERANCY);
}
END_TEST

START_TEST(floor_test2) {
  ck_assert_ldouble_eq_tol(s21_floor(neg_nums_primes[_i]),
                           floor(neg_nums_primes[_i]), TOLERANCY);
}
END_TEST

START_TEST(floor_test_nan) {  // дополнено
  ck_assert_ldouble_nan(s21_floor(S21_NAN));
}
END_TEST

START_TEST(floor_test_inf) {  // дополнено
  ck_assert_ldouble_eq(s21_floor(inf_primes[_i]), floor(inf_primes[_i]));
}
END_TEST

START_TEST(exp_test_1) {  // дополнено
  for (double k = -21; k < 21; k += 1) {
    double a = s21_exp(k);
    double b = exp(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(exp_test_2) {  // дополнено
  for (double k = -8; k < 8; k += 0.123) {
    double a = s21_exp(k);
    double b = exp(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(exp_test_3) {  // дополнено
  for (double k = -3; k < 3; k += 0.00088) {
    double a = s21_exp(k);
    double b = exp(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(exp_test_nan_inf) {  // дополнено
  ck_assert_double_nan(s21_exp(S21_NAN));
  ck_assert_double_eq(exp(S21_INF), s21_exp(S21_INF));
  ck_assert_double_eq(exp(-S21_INF), s21_exp(-S21_INF));
  ck_assert_double_eq(exp(S21_MAX_DOUBLE / 2), s21_exp(S21_MAX_DOUBLE / 2));
}
END_TEST

START_TEST(fmod_test_1) {
  ck_assert_double_eq(fmod(0, -1), s21_fmod(0, -1));
  ck_assert_double_eq(fmod(0, 1), s21_fmod(0, 1));
  ck_assert_double_eq(fmod(-1, -S21_INF), s21_fmod(-1, -S21_INF));
  ck_assert_double_eq(fmod(0, S21_INF), s21_fmod(0, S21_INF));
}

END_TEST
START_TEST(fmod_test_2) {
  for (double a = -1500; a < 1500; a += 123) {
    for (double b = -12; b < 12; b += 1.25) {
      ck_assert_double_eq(fmod(a, b), s21_fmod(a, b));
      ck_assert_double_eq(fmod(b, a), s21_fmod(b, a));
    }
  }
}
END_TEST

START_TEST(fmod_test_nan_inf) {
  ck_assert_double_nan(s21_fmod(1, 0));
  ck_assert_double_nan(s21_fmod(-11, 0));
  ck_assert_double_nan(s21_fmod(89, 0));
  ck_assert_double_nan(s21_fmod(S21_INF, -1));
  ck_assert_double_nan(s21_fmod(0, S21_NAN));
  ck_assert_double_nan(s21_fmod(S21_NAN, S21_NAN));
  ck_assert_double_nan(s21_fmod(S21_NAN, S21_INF));
  ck_assert_double_nan(s21_fmod(S21_INF, S21_NAN));
  ck_assert_double_nan(s21_fmod(S21_NAN, -S21_INF));
  ck_assert_double_nan(s21_fmod(S21_NAN, -S21_NAN));
  ck_assert_double_nan(s21_fmod(-S21_INF, S21_NAN));
}
END_TEST

START_TEST(log_test_1) {
  for (double k = 1; k < 1000; k += 13.2) {
    double a = s21_log(k);
    double b = log(k);
    ck_assert_double_eq_tol(a, b, TOLERANCY);
  }
}
END_TEST

START_TEST(log_test_2) {
  for (double k = 0.1; k < 4; k += 0.24) {
    double a = s21_log(k);
    double b = log(k);
    ck_assert_double_eq_tol(a, b, TOLERANCY);
  }
}
END_TEST

START_TEST(log_test_3) {
  for (double k = 0.000005; k < 1; k *= 5) {
    double a = s21_log(k);
    double b = log(k);
    ck_assert_double_eq_tol(a, b, TOLERANCY);
  }
}
END_TEST

START_TEST(log_test_neg) {
  ck_assert_ldouble_nan(s21_log(neg_nums_primes[_i]));
}
END_TEST

START_TEST(log_test_nan) { ck_assert_ldouble_nan(s21_log(S21_NAN)); }
END_TEST

START_TEST(log_test_inf) {
  ck_assert_ldouble_infinite(s21_log(inf_primes[0]));
  ck_assert_ldouble_nan(s21_log(inf_primes[1]));
}
END_TEST

START_TEST(log_test_5) { ck_assert_double_eq(log(S21_E), s21_log(S21_E)); }
END_TEST

START_TEST(pow_test_1) {
  for (double k = -15; k <= 15; k += 1.7) {
    for (double g = -5; g < 5; g += 1) {
      long double a = s21_pow(k, g);
      long double b = pow(k, g);
      if ((!s21_is_nan(a) && !isnan(b)) && !(a == S21_INF && b == S21_INF) &&
          !(a == -S21_INF && b == -S21_INF)) {
        ck_assert_double_eq_tol(a, b, TOLERANCY);
      }
      a = s21_pow(g, k);
      b = pow(g, k);
      if ((!s21_is_nan(a) && !isnan(b)) && !(a == S21_INF && b == S21_INF) &&
          !(a == -S21_INF && b == -S21_INF)) {
        ck_assert_double_eq_tol(a, b, TOLERANCY);
      }
    }
  }
}
END_TEST

START_TEST(pow_test_2) {
  for (double k = -0.1; k <= 1; k += 1.1) {
    for (double g = -2.55; g < 2; g += 1.1111) {
      long double a = s21_pow(k, g);
      long double b = pow(k, g);
      if ((!s21_is_nan(a) && !isnan(b)) && !(a == S21_INF && b == S21_INF) &&
          !(a == -S21_INF && b == -S21_INF)) {
        ck_assert_double_eq_tol(a, b, TOLERANCY);
      }
      a = s21_pow(g, k);
      b = pow(g, k);
      if ((!s21_is_nan(a) && !isnan(b)) && !(a == S21_INF && b == S21_INF) &&
          !(a == -S21_INF && b == -S21_INF)) {
        ck_assert_double_eq_tol(a, b, TOLERANCY);
      }
    }
  }
}
END_TEST

START_TEST(pow_test_exeptions) {
  ck_assert_double_eq(pow(1, 0), s21_pow(1, 0));
  ck_assert_double_eq(pow(-1, 3), s21_pow(-1, 3));
  ck_assert_double_eq(pow(-1, 4), s21_pow(-1, 4));
  ck_assert_double_eq(pow(0, 0), s21_pow(0, 0));
  ck_assert_double_eq(pow(0, -1), s21_pow(0, -1));
  ck_assert_double_eq(pow(0, 1), s21_pow(0, 1));
  ck_assert_double_eq(pow(S21_INF, 0), s21_pow(S21_INF, 0));
  ck_assert_double_eq(pow(S21_INF, -1), s21_pow(S21_INF, -1));
  ck_assert_double_eq(pow(-1, -S21_INF), s21_pow(-1, -S21_INF));
  ck_assert_double_eq(pow(0, S21_INF), s21_pow(0, S21_INF));
  ck_assert_double_nan(s21_pow(0, S21_NAN));
  ck_assert_double_eq(pow(NAN, 0), s21_pow(S21_NAN, 0));
  ck_assert_double_nan(s21_pow(S21_NAN, S21_NAN));
  ck_assert_double_eq(pow(S21_INF, S21_INF), s21_pow(S21_INF, S21_INF));
  ck_assert_double_eq(pow(S21_INF, -S21_INF), s21_pow(S21_INF, -S21_INF));
  ck_assert_double_eq(pow(-S21_INF, S21_INF), s21_pow(-S21_INF, S21_INF));
  ck_assert_double_eq(pow(-S21_INF, -S21_INF), s21_pow(-S21_INF, -S21_INF));
  ck_assert_double_eq(pow(1, -S21_INF), s21_pow(1, -S21_INF));
  ck_assert_double_eq(pow(1, NAN), s21_pow(1, S21_NAN));
  ck_assert_double_nan(s21_pow(S21_NAN, S21_INF));
  ck_assert_double_nan(s21_pow(S21_INF, S21_NAN));
  ck_assert_double_nan(s21_pow(S21_NAN, -S21_INF));
  ck_assert_double_nan(s21_pow(-S21_INF, S21_NAN));
  ck_assert_double_eq(pow(2, S21_INF), s21_pow(2, S21_INF));
  ck_assert_double_eq(pow(0.5, S21_INF), s21_pow(0.5, S21_INF));
  ck_assert_double_eq(pow(-2, S21_INF), s21_pow(-2, S21_INF));
  ck_assert_double_eq(pow(2, -S21_INF), s21_pow(2, -S21_INF));
  ck_assert_double_eq(pow(0.5, -S21_INF), s21_pow(0.5, -S21_INF));
  ck_assert_double_eq(pow(-2, -S21_INF), s21_pow(-2, -S21_INF));
  ck_assert_double_eq(pow(-S21_INF, -121), s21_pow(-S21_INF, -121));
  ck_assert_double_eq(pow(-S21_INF, 121), s21_pow(-S21_INF, 121));
  ck_assert_double_eq(pow(-S21_INF, 120), s21_pow(-S21_INF, 120));
  ck_assert_double_eq(pow(S21_INF, 120), s21_pow(S21_INF, 120));
}
END_TEST

START_TEST(sqrt_test_1) {
  ck_assert_double_eq_tol(s21_sqrt(pos_nums_primes[_i]),
                          sqrt(pos_nums_primes[_i]), TOLERANCY);
}
END_TEST

START_TEST(sqrt_test_neg) {
  ck_assert_ldouble_nan(s21_sqrt(neg_nums_primes[_i]));
}
END_TEST

START_TEST(sqrt_test_nan) {  // дополнено
  ck_assert_ldouble_nan(s21_sqrt(S21_NAN));
}
END_TEST
START_TEST(sqrt_test_inf) {  // дополнено
  ck_assert_ldouble_nan(s21_sqrt(-S21_INF));
  ck_assert_ldouble_eq(s21_sqrt(S21_INF), sqrt(S21_INF));
}
END_TEST

START_TEST(sin_test_NAN) {
  ck_assert_ldouble_nan(s21_sin(S21_INF));
  ck_assert_ldouble_nan(s21_sin(-S21_INF));
  ck_assert_ldouble_nan(s21_sin(S21_NAN));
}
END_TEST

START_TEST(sin_test_TOL_1) {
  ck_assert_ldouble_eq_tol(sin(S21_PI), s21_sin(S21_PI), 1e-6);
  ck_assert_ldouble_eq_tol(sin(-121), s21_sin(-121), 1e-6);
  ck_assert_ldouble_eq_tol(sin(121.121), s21_sin(121.121), 1e-6);
}
END_TEST

START_TEST(sin_test_TOL_2) {
  /*
  ck_assert_ldouble_eq_tol(sin(S21_MAX_DOUBLE), s21_sin(S21_MAX_DOUBLE), 1e-6);
  ck_assert_ldouble_eq_tol(sin(-S21_MAX_DOUBLE - 1.), s21_sin(-S21_MAX_DOUBLE
  - 1.), 1e-6); ck_assert_ldouble_eq_tol(sin(S21_MAX_INT), s21_sin(S21_MAX_INT),
  1e-6); ck_assert_ldouble_eq_tol(sin(-S21_MAX_INT - 1), s21_sin(-S21_MAX_INT -
  1), 1e-6); ck_assert_ldouble_eq_tol(sin(9999999999999999.),
  s21_sin(9999999999999999.), 1e-6);
  ck_assert_ldouble_eq_tol(sin(-9999999999999999.), s21_sin(-9999999999999999.),
  1e-6);
  */
  ck_assert_ldouble_eq_tol(sin(9999999999.999999), s21_sin(9999999999.999999),
                           1e-6);
  ck_assert_ldouble_eq_tol(sin(-9999999999.999999), s21_sin(-9999999999.999999),
                           1e-6);
}
END_TEST

START_TEST(sin_test_TABL_1) {
  ck_assert_ldouble_eq_tol(sin(0), s21_sin(0), 1e-6);
  ck_assert_ldouble_eq_tol(sin(0.), s21_sin(0.), 1e-6);
  ck_assert_ldouble_eq_tol(sin(S21_PI / 6), s21_sin(S21_PI / 6), 1e-6);
  ck_assert_ldouble_eq_tol(sin(S21_PI_4), s21_sin(S21_PI_4), 1e-6);
  ck_assert_ldouble_eq_tol(sin(S21_PI / 3), s21_sin(S21_PI / 3), 1e-6);
  ck_assert_ldouble_eq_tol(sin(S21_PI_2), s21_sin(S21_PI_2), 1e-6);
  ck_assert_ldouble_eq_tol(sin(2 * S21_PI), s21_sin(2 * S21_PI), 1e-6);
  ck_assert_ldouble_eq_tol(sin(2 * S21_PI - S21_EPS),
                           s21_sin(2 * S21_PI - S21_EPS), 1e-6);
}
END_TEST

START_TEST(sin_test_TABL_2) {
  ck_assert_ldouble_eq_tol(sin(-S21_PI / 6), s21_sin(-S21_PI / 6), 1e-6);
  ck_assert_ldouble_eq_tol(sin(-S21_PI / 4), s21_sin(-S21_PI / 4), 1e-6);
  ck_assert_ldouble_eq_tol(sin(-S21_PI / 3), s21_sin(-S21_PI / 3), 1e-6);
  ck_assert_ldouble_eq_tol(sin(-S21_PI / 2), s21_sin(-S21_PI / 2), 1e-6);
  ck_assert_ldouble_eq_tol(sin(-2 * S21_PI), s21_sin(-2 * S21_PI), 1e-6);
  ck_assert_ldouble_eq_tol(sin(-2 * S21_PI - S21_EPS),
                           s21_sin(-2 * S21_PI - S21_EPS), 1e-6);
}
END_TEST

START_TEST(asin_test_NAN) {
  ck_assert_ldouble_nan(s21_asin(S21_INF));
  ck_assert_ldouble_nan(s21_asin(-S21_INF));
  ck_assert_ldouble_nan(s21_asin(S21_NAN));

  ck_assert_ldouble_nan(s21_asin(S21_MAX_DOUBLE));
  ck_assert_ldouble_nan(s21_asin(-S21_MAX_DOUBLE - 1.));

  ck_assert_ldouble_nan(s21_asin(S21_MAX_INT));
  ck_assert_ldouble_nan(s21_asin(-S21_MAX_INT - 1));
}
END_TEST

START_TEST(asin_test_TOL) {
  ck_assert_ldouble_nan(s21_asin(S21_PI));
  ck_assert_ldouble_nan(s21_asin(-121));
  ck_assert_ldouble_nan(s21_asin(121.121));
}
END_TEST

START_TEST(asin_test_TABL) {
  ck_assert_ldouble_eq_tol(asin(1.), s21_asin(1.), 1e-6);
  ck_assert_ldouble_eq_tol(asin(s21_sqrt(3) / 2.), s21_asin(s21_sqrt(3) / 2.),
                           1e-6);
  ck_assert_ldouble_eq_tol(asin(s21_sqrt(2) / 2), s21_asin(sqrt(2) / 2), 1e-6);

  ck_assert_ldouble_eq_tol(asin(-1.), s21_asin(-1.), 1e-6);
  ck_assert_ldouble_eq_tol(asin(-s21_sqrt(3) / 2.), s21_asin(-s21_sqrt(3) / 2.),
                           1e-6);
  ck_assert_ldouble_eq_tol(asin(-s21_sqrt(2) / 2), s21_asin(-s21_sqrt(2) / 2),
                           1e-6);

  ck_assert_ldouble_eq_tol(asin(0), s21_asin(0), 1e-6);
}
END_TEST

START_TEST(cos_test_NAN) {
  ck_assert_ldouble_nan(s21_cos(S21_INF));
  ck_assert_ldouble_nan(s21_cos(-S21_INF));
  ck_assert_ldouble_nan(s21_cos(S21_NAN));
}
END_TEST

START_TEST(cos_test_TOL_1) {
  ck_assert_ldouble_eq_tol(cos(S21_PI), s21_cos(S21_PI), 1e-6);
  ck_assert_ldouble_eq_tol(cos(-121), s21_cos(-121), 1e-6);
  ck_assert_ldouble_eq_tol(cos(121.121), s21_cos(121.121), 1e-6);
}
END_TEST

START_TEST(cos_test_TOL_2) {
  /*
  ck_assert_ldouble_eq_tol(cos(S21_MAX_DOUBLE),       s21_cos(S21_MAX_DOUBLE),
  1e-6); ck_assert_ldouble_eq_tol(cos(-S21_MAX_DOUBLE - 1.),
  s21_cos(-S21_MAX_DOUBLE - 1.), 1e-6);
  ck_assert_ldouble_eq_tol(cos(S21_MAX_INT),          s21_cos(S21_MAX_INT),
  1e-6); ck_assert_ldouble_eq_tol(cos(-S21_MAX_INT - 1), s21_cos(-S21_MAX_INT -
  1), 1e-6); ck_assert_ldouble_eq_tol(cos(9999999999999999.),
  s21_cos(9999999999999999.), 1e-6);
  ck_assert_ldouble_eq_tol(cos(-9999999999999999.), s21_cos(-9999999999999999.),
  1e-6);
  */
  ck_assert_ldouble_eq_tol(cos(9999999999.999999), s21_cos(9999999999.999999),
                           1e-6);
  ck_assert_ldouble_eq_tol(cos(-9999999999.999999), s21_cos(-9999999999.999999),
                           1e-6);
}
END_TEST

START_TEST(cos_test_TABL_1) {
  ck_assert_ldouble_eq_tol(cos(0), s21_cos(0), 1e-6);
  ck_assert_ldouble_eq_tol(cos(0.), s21_cos(0.), 1e-6);
  ck_assert_ldouble_eq_tol(cos(S21_PI / 6), s21_cos(S21_PI / 6), 1e-6);
  ck_assert_ldouble_eq_tol(cos(S21_PI_4), s21_cos(S21_PI_4), 1e-6);
  ck_assert_ldouble_eq_tol(cos(S21_PI / 3), s21_cos(S21_PI / 3), 1e-6);
  ck_assert_ldouble_eq_tol(cos(S21_PI_2), s21_cos(S21_PI_2), 1e-6);
  ck_assert_ldouble_eq_tol(cos(2 * S21_PI), s21_cos(2 * S21_PI), 1e-6);
  ck_assert_ldouble_eq_tol(cos(2 * S21_PI - S21_EPS),
                           s21_cos(2 * S21_PI - S21_EPS), 1e-6);
}
END_TEST

START_TEST(cos_test_TABL_2) {
  ck_assert_ldouble_eq_tol(cos(-S21_PI / 6), s21_cos(-S21_PI / 6), 1e-6);
  ck_assert_ldouble_eq_tol(cos(-S21_PI_4), s21_cos(-S21_PI_4), 1e-6);
  ck_assert_ldouble_eq_tol(cos(-S21_PI / 3), s21_cos(-S21_PI / 3), 1e-6);
  ck_assert_ldouble_eq_tol(cos(-S21_PI_2), s21_cos(-S21_PI_2), 1e-6);
  ck_assert_ldouble_eq_tol(cos(-2 * S21_PI), s21_cos(-2 * S21_PI), 1e-6);
  ck_assert_ldouble_eq_tol(cos(-2 * S21_PI - S21_EPS),
                           s21_cos(-2 * S21_PI - S21_EPS), 1e-6);
}
END_TEST

START_TEST(acos_test_NAN) {
  ck_assert_ldouble_nan(s21_acos(S21_INF));
  ck_assert_ldouble_nan(s21_acos(-S21_INF));
  ck_assert_ldouble_nan(s21_acos(S21_NAN));

  ck_assert_ldouble_nan(s21_acos(S21_MAX_DOUBLE));
  ck_assert_ldouble_nan(s21_acos(-S21_MAX_DOUBLE - 1.));

  ck_assert_ldouble_nan(s21_acos(S21_MAX_INT));
  ck_assert_ldouble_nan(s21_acos(-S21_MAX_INT - 1));
}
END_TEST

START_TEST(acos_test_TOL) {
  ck_assert_ldouble_nan(s21_acos(S21_PI));
  ck_assert_ldouble_nan(s21_acos(-121));
  ck_assert_ldouble_nan(s21_acos(121.121));
}
END_TEST

START_TEST(acos_test_TABL) {
  ck_assert_ldouble_eq_tol(acos(1.), s21_acos(1.), 1e-6);
  ck_assert_ldouble_eq_tol(acos(s21_sqrt(3) / 2.), s21_acos(s21_sqrt(3) / 2.),
                           1e-6);
  ck_assert_ldouble_eq_tol(acos(s21_sqrt(2) / 2), s21_acos(s21_sqrt(2) / 2),
                           1e-6);

  ck_assert_ldouble_eq_tol(acos(-1.), s21_acos(-1.), 1e-6);
  ck_assert_ldouble_eq_tol(acos(-s21_sqrt(3) / 2.), s21_acos(-s21_sqrt(3) / 2.),
                           1e-6);
  ck_assert_ldouble_eq_tol(acos(-s21_sqrt(2) / 2), s21_acos(-s21_sqrt(2) / 2),
                           1e-6);

  ck_assert_ldouble_eq_tol(acos(0), s21_acos(0), 1e-6);
}
END_TEST

START_TEST(tan_test_NAN) {
  ck_assert_ldouble_nan(s21_tan(S21_INF));
  ck_assert_ldouble_nan(s21_tan(-S21_INF));
  ck_assert_ldouble_nan(s21_tan(S21_NAN));
  ck_assert_ldouble_ne(tan(2 * S21_PI), s21_tan(2 * S21_PI));
}
END_TEST

START_TEST(tan_test_TOL_1) {
  ck_assert_ldouble_eq_tol(tan(S21_PI), s21_tan(S21_PI), 1e-6);
  ck_assert_ldouble_eq_tol(tan(-121), s21_tan(-121), 1e-6);
  ck_assert_ldouble_eq_tol(tan(121.121), s21_tan(121.121), 1e-6);
}
END_TEST

START_TEST(tan_test_TOL_2) {
  /*
  ck_assert_ldouble_eq_tol(tan(S21_MAX_DOUBLE),       s21_tan(S21_MAX_DOUBLE),
  1e-6); ck_assert_ldouble_eq_tol(tan(-S21_MAX_DOUBLE - 1.),
  s21_tan(-S21_MAX_DOUBLE - 1.), 1e-6);
  ck_assert_ldouble_eq_tol(tan(S21_MAX_INT),          s21_tan(S21_MAX_INT),
  1e-6); ck_assert_ldouble_eq_tol(tan(-S21_MAX_INT - 1), s21_tan(-S21_MAX_INT -
  1), 1e-6); ck_assert_ldouble_eq_tol(tan(9999999999999999.),
  s21_tan(9999999999999999.), 1e-6);
  ck_assert_ldouble_eq_tol(tan(-9999999999999999.), s21_tan(-9999999999999999.),
  1e-6);
  */
  ck_assert_ldouble_eq_tol(tan(9999999999.999999), s21_tan(9999999999.999999),
                           1e-6);
  ck_assert_ldouble_eq_tol(tan(-9999999999.999999), s21_tan(-9999999999.999999),
                           1e-6);
}
END_TEST

START_TEST(tan_test_TABL_1) {
  ck_assert_ldouble_eq_tol(tan(0), s21_tan(0), 1e-6);
  ck_assert_ldouble_eq_tol(tan(0.), s21_tan(0.), 1e-6);
  ck_assert_ldouble_eq_tol(tan(S21_PI / 6), s21_tan(S21_PI / 6), 1e-6);
  ck_assert_ldouble_eq_tol(tan(S21_PI_4), s21_tan(S21_PI_4), 1e-6);
  ck_assert_ldouble_eq_tol(tan(S21_PI / 3), s21_tan(S21_PI / 3), 1e-6);
  ck_assert_ldouble_eq_tol(tan(S21_PI_2), s21_tan(S21_PI_2), 1e-6);
  ck_assert_ldouble_eq_tol(tan(2 * S21_PI - S21_EPS),
                           s21_tan(2 * S21_PI - S21_EPS), 1e-6);

  ck_assert_ldouble_eq_tol(tan(3 * S21_PI / 2), s21_tan(3 * S21_PI / 2), 1e-6);
}
END_TEST

START_TEST(tan_test_TABL_2) {
  ck_assert_ldouble_eq_tol(tan(-S21_PI / 6), s21_tan(-S21_PI / 6), 1e-6);
  ck_assert_ldouble_eq_tol(tan(-S21_PI_4), s21_tan(-S21_PI_4), 1e-6);
  ck_assert_ldouble_eq_tol(tan(-S21_PI / 3), s21_tan(-S21_PI / 3), 1e-6);
  ck_assert_ldouble_eq_tol(tan(-S21_PI_2), s21_tan(-S21_PI_2), 1e-6);
  ck_assert_ldouble_eq_tol(tan(-2 * S21_PI), s21_tan(-2 * S21_PI), 1e-6);
  ck_assert_ldouble_eq_tol(tan(-2 * S21_PI - S21_EPS),
                           s21_tan(-2 * S21_PI - S21_EPS), 1e-6);
  ck_assert_ldouble_eq_tol(tan(-3 * S21_PI / 2), s21_tan(-3 * S21_PI / 2),
                           1e-6);
}
END_TEST

START_TEST(atan_test_NAN) {
  ck_assert_ldouble_eq_tol(s21_atan(S21_INF), atan(S21_INF), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(-S21_INF), atan(-S21_INF), 1e-6);
  ck_assert_ldouble_nan(s21_atan(S21_NAN));
}
END_TEST

START_TEST(atan_test_TOL) {
  ck_assert_ldouble_eq_tol(atan(S21_PI), s21_atan(S21_PI), 1e-6);
  ck_assert_ldouble_eq_tol(atan(-1221), s21_atan(-1221), 1e-6);
  ck_assert_ldouble_eq_tol(atan(121.1221), s21_atan(121.1221), 1e-6);

  ck_assert_ldouble_eq_tol(atan(9999999999.999999), s21_atan(9999999999.999999),
                           1e-6);
  ck_assert_ldouble_eq_tol(atan(-9999999999.999999),
                           s21_atan(-9999999999.999999), 1e-6);
  ck_assert_ldouble_eq_tol(atan(S21_PI / 2), s21_atan(S21_PI / 2), 1e-6);
  ck_assert_ldouble_eq_tol(atan(-S21_PI / 2), s21_atan(-S21_PI / 2), 1e-6);

  /*
  long double test12 = S21_MAX_DOUBLE;
  ck_assert_ldouble_eq_tol(atan(test12), s21_atan(test12), 1e-6);
  long double test13 = -S21_MAX_DOUBLE - 1.;
  ck_assert_ldouble_eq_tol(atan(test13), s21_atan(test13), 1e-6);
  long double test14 = S21_MAX_INT;
  ck_assert_ldouble_eq_tol(atan(test14), s21_atan(test14), 1e-6);
  long double test15 = -S21_MAX_INT - 1;
  ck_assert_ldouble_eq_tol(atan(test15), s21_atan(test15), 1e-6);
  */
}
END_TEST

START_TEST(atan_test_TABL) {
  ck_assert_ldouble_eq_tol(atan(0), s21_atan(0), 1e-6);
  ck_assert_ldouble_eq_tol(atan(0.), s21_atan(0.), 1e-6);

  ck_assert_ldouble_eq_tol(atan(s21_sqrt(3)), s21_atan(s21_sqrt(3)), 1e-6);
  ck_assert_ldouble_eq_tol(atan(1), s21_atan(1), 1e-6);
  ck_assert_ldouble_eq_tol(atan(s21_sqrt(3) / 3), s21_atan(s21_sqrt(3) / 3),
                           1e-6);

  ck_assert_ldouble_eq_tol(atan(-s21_sqrt(3)), s21_atan(-s21_sqrt(3)), 1e-6);
  ck_assert_ldouble_eq_tol(atan(-1), s21_atan(-1), 1e-6);
  ck_assert_ldouble_eq_tol(atan(-s21_sqrt(3) / 3), s21_atan(-s21_sqrt(3) / 3),
                           1e-6);
}
END_TEST

Suite *suit_test_func(void) {
  Suite *x;
  x = suite_create("check");

  TCase *exp_case;
  TCase *fmod_case;
  TCase *log_case;
  TCase *pow_case;
  TCase *sqrt_case;

  TCase *sin_case;
  TCase *asin_case;

  TCase *cos_case;
  TCase *acos_case;

  TCase *tan_case;
  TCase *atan_case;
  TCase *abs_case;
  TCase *ceil_case;
  TCase *fabs_case;
  TCase *floor_case;

  abs_case = tcase_create("abs");
  tcase_add_loop_test(abs_case, abs_test1, 0, 10);
  suite_add_tcase(x, abs_case);

  ceil_case = tcase_create("ceil");
  tcase_add_loop_test(ceil_case, ceil_test1, 0, 8);
  tcase_add_loop_test(ceil_case, ceil_test2, 0, 8);
  tcase_add_loop_test(ceil_case, ceil_test3, 0, 2);
  tcase_add_test(ceil_case, ceil_test_nan);
  suite_add_tcase(x, ceil_case);

  fabs_case = tcase_create("fabs");
  tcase_add_loop_test(fabs_case, fabs_test1, 0, 8);
  tcase_add_loop_test(fabs_case, fabs_test2, 0, 8);
  tcase_add_test(fabs_case, fabs_test_nan);
  tcase_add_loop_test(fabs_case, fabs_test_inf, 0, 2);
  suite_add_tcase(x, fabs_case);

  floor_case = tcase_create("floor");
  tcase_add_loop_test(floor_case, floor_test1, 0, 8);
  tcase_add_loop_test(floor_case, floor_test2, 0, 8);
  tcase_add_test(floor_case, floor_test_nan);
  tcase_add_loop_test(floor_case, floor_test_inf, 0, 2);
  suite_add_tcase(x, floor_case);

  sin_case = tcase_create("sin");
  suite_add_tcase(x, sin_case);
  tcase_add_test(sin_case, sin_test_NAN);
  tcase_add_test(sin_case, sin_test_TOL_1);
  tcase_add_test(sin_case, sin_test_TOL_2);
  tcase_add_test(sin_case, sin_test_TABL_1);
  tcase_add_test(sin_case, sin_test_TABL_2);

  asin_case = tcase_create("asin");
  suite_add_tcase(x, asin_case);
  tcase_add_test(asin_case, asin_test_NAN);
  tcase_add_test(asin_case, asin_test_TOL);
  tcase_add_test(asin_case, asin_test_TABL);

  cos_case = tcase_create("cos");
  suite_add_tcase(x, cos_case);
  tcase_add_test(cos_case, cos_test_NAN);
  tcase_add_test(cos_case, cos_test_TOL_1);
  tcase_add_test(cos_case, cos_test_TOL_2);
  tcase_add_test(cos_case, cos_test_TABL_1);
  tcase_add_test(cos_case, cos_test_TABL_2);

  acos_case = tcase_create("acos");
  suite_add_tcase(x, acos_case);
  tcase_add_test(acos_case, acos_test_NAN);
  tcase_add_test(acos_case, acos_test_TOL);
  tcase_add_test(acos_case, acos_test_TABL);

  tan_case = tcase_create("tan");
  suite_add_tcase(x, tan_case);
  tcase_add_test(tan_case, tan_test_NAN);
  tcase_add_test(tan_case, tan_test_TOL_1);
  tcase_add_test(tan_case, tan_test_TOL_2);
  tcase_add_test(tan_case, tan_test_TABL_1);
  tcase_add_test(tan_case, tan_test_TABL_2);

  atan_case = tcase_create("atan");
  suite_add_tcase(x, atan_case);
  tcase_add_test(atan_case, atan_test_NAN);
  tcase_add_test(atan_case, atan_test_TOL);
  tcase_add_test(atan_case, atan_test_TABL);

  exp_case = tcase_create("exp");
  suite_add_tcase(x, exp_case);
  tcase_add_test(exp_case, exp_test_1);
  tcase_add_test(exp_case, exp_test_2);
  tcase_add_test(exp_case, exp_test_3);
  tcase_add_test(exp_case, exp_test_nan_inf);

  fmod_case = tcase_create("fmod");
  tcase_add_test(fmod_case, fmod_test_1);
  tcase_add_test(fmod_case, fmod_test_2);
  tcase_add_test(fmod_case, fmod_test_nan_inf);
  suite_add_tcase(x, fmod_case);

  log_case = tcase_create("log");
  tcase_add_test(log_case, log_test_1);
  tcase_add_test(log_case, log_test_2);
  tcase_add_test(log_case, log_test_3);
  tcase_add_loop_test(log_case, log_test_neg, 0, 8);
  tcase_add_test(log_case, log_test_nan);
  tcase_add_loop_test(log_case, log_test_inf, 0, 2);
  tcase_add_test(log_case, log_test_5);
  suite_add_tcase(x, log_case);

  pow_case = tcase_create("pow");
  tcase_add_test(pow_case, pow_test_1);
  tcase_add_test(pow_case, pow_test_2);
  tcase_add_test(pow_case, pow_test_exeptions);
  suite_add_tcase(x, pow_case);

  sqrt_case = tcase_create("sqrt");
  tcase_add_loop_test(sqrt_case, sqrt_test_1, 0, 8);
  tcase_add_loop_test(sqrt_case, sqrt_test_neg, 0, 8);
  tcase_add_test(sqrt_case, sqrt_test_nan);
  tcase_add_test(sqrt_case, sqrt_test_inf);
  suite_add_tcase(x, sqrt_case);

  return x;
}

int main(void) {
  Suite *s;
  SRunner *runner;

  s = suit_test_func();
  runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  srunner_free(runner);
  return 0;
}

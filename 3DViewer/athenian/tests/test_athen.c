#include "test_athen.h"
#define EPS 1e-6

START_TEST(rotate_test) {
  double first_coord = 3.1245;
  double second_coord = 15.25543;

  rotate_around_axis(&first_coord, &second_coord, 4.18879);
  ck_assert_double_eq_tol(first_coord, 11.649338, EPS);
  ck_assert_double_eq_tol(second_coord, -10.333614, EPS);
}

Suite *test_athen(void) {
  Suite *s = suite_create("test_athen");

  TCase *test_athen = tcase_create("test_athen");
  suite_add_tcase(s, test_athen);
  tcase_add_test(test_athen, rotate_test);

  return s;
}
#include "test.h"

int main(void) {
  int nf = 0;

  Suite *s1 = s21_matrix_test();

  SRunner *sr1 = srunner_create(s1);

  srunner_run_all(sr1, CK_ENV);

  nf = srunner_ntests_failed(sr1);

  srunner_free(sr1);

  return nf == 0 ? 0 : 1;
}
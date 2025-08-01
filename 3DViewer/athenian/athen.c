#include "athen.h"

void rotate_around_axis(double *first_coord, double *second_coord,
                        const double angle) {
  double x = *first_coord, y = *second_coord;

  *first_coord = x * cos(angle) - y * sin(angle);
  *second_coord = x * sin(angle) + y * cos(angle);
}

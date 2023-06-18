#include "lib_flot.h"

bool IsNotZero(const double num) {
  return (fabs(num) >= EPSILON);
}

bool Equal(const double num_1, const double num_2) {
  return (fabs(num_1 - num_2) < EPSILON);
}

bool Greater(const double num_1, const double num_2) {
  return (num_1 - num_2 > EPSILON);
}

bool Less(const double num_1, const double num_2) {
  return Greater(num_2, num_1);
}

int Round(const double real) {
  if (!Less(real - (int)real, 0.5)) return ((int)real) + 1;

  else return (int)real;
}

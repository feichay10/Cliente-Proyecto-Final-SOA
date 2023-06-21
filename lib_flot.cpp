#include "lib_flot.h"

bool RNG_seed_set = false;

float GenerateRandomNumber(float lower_limit, float upper_limit) {
  if (!RNG_seed_set) {
    srand(std::time(NULL));
    RNG_seed_set = true;
  }

  if (lower_limit >= upper_limit) qDebug() << "Invalid range for RNG";

  float RNG_number = (float)rand() / RAND_MAX; //gets a random number between 0.0 and 1.0
  return lower_limit + RNG_number * (upper_limit - lower_limit); //changes it to range [M, P] as asked
}

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

int calcLCM(const std::vector<int>& num) {
  int lcm = num[0];

  for (size_t i = 1; i < num.size(); i++)
    lcm = std::lcm(lcm, num[i]);

  return lcm;
}

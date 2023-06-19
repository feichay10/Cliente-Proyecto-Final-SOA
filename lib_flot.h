#include <ctime>
#include <cmath>
#include "qdebug.h"

#define EPSILON 1e-6

extern bool RNG_seed_set;
float GenerateRandomNumber(float lower_limit, float upper_limit);
bool IsNotZero(const double num);
bool Equal(const double num_1, const double num_2);
bool Greater(const double num_1, const double num_2);
bool Less(const double num_1, const double num_2);
int Round(const double);

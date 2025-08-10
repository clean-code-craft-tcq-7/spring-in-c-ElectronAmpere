#include "stats.h"
#include <float.h>
#include <math.h>
#include <stddef.h>

int checkValueAbsurdity(const float *numbers, int count) {
  for (int index = 0; index < count; index++) {
    if (numbers[index] < 0 || numbers[index] > 1e5) {
      return 1;
    }
  }
  return 0;
}

struct Stats compute_statistics(const float *numbers, int count) {
  struct Stats statistics;
  float sum = 0.0f;
  statistics.average = 0.0f;
  statistics.min = FLT_MAX;
  statistics.max = -FLT_MAX;
  int validCount = 0;

  if (count <= 0) {
    statistics.min = NAN;
    statistics.max = NAN;
    statistics.average = NAN;
    return statistics;
  }

  if (checkValueAbsurdity(numbers, count)) {
    statistics.min = NAN;
    statistics.max = NAN;
    statistics.average = NAN;
    return statistics;
  }

  for (int index = 0; index < count; index++) {

    if (isnan(numbers[index])) {
      continue;
    }
    validCount++;

    if (numbers[index] < statistics.min) {
      statistics.min = numbers[index];
    }
    if (numbers[index] > statistics.max) {
      statistics.max = numbers[index];
    }
    sum += numbers[index];
  }

  if (validCount != 0) {
    statistics.average = (sum / validCount);
  } else {
    statistics.min = NAN;
    statistics.max = NAN;
    statistics.average = NAN;
  }

  return statistics;
}

#include "stats.h"
#include <assert.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stddef.h>

#define NUMBER_SWEEPER_START(index, start, stop)                               \
  for (index = start; index < stop; index++) {
#define NUMBER_SWEEPER_END() }

int checkValueAbsurdity(const float *numbers, int count) {
  int index = 0;

  if ((numbers == NULL) || (count < 0) || (count > (INT_MAX / sizeof(float)))) {
    return -1;
  }

  NUMBER_SWEEPER_START(index, 0, count);
  assert(index >= 0 && index < count && "Array index out of bounds");
  if (numbers[index] < 0.0f || numbers[index] > 1e5f) {
    return 1;
  }
  NUMBER_SWEEPER_END();
  return 0;
}

int setStatisticsNaN(struct Stats *statistics) {
  if (statistics != NULL) {
    statistics->min = NAN;
    statistics->max = NAN;
    statistics->average = NAN;
    return 0;
  }
  return -1;
}

struct Stats compute_statistics(const float *numbers, int count) {
  struct Stats statistics;
  float sum = 0.0f;
  statistics.average = 0.0f;
  statistics.min = FLT_MAX;
  statistics.max = -FLT_MAX;
  int validCount = 0;
  int index = 0;
  int absurdityValidation = 0;

  absurdityValidation = checkValueAbsurdity(numbers, count);

  if ((count <= 0) || (absurdityValidation != 0)) {
    (void)setStatisticsNaN(&statistics);
    return statistics;
  }

  NUMBER_SWEEPER_START(index, 0, count);
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
  NUMBER_SWEEPER_END();

  if (validCount != 0) {
    statistics.average = (sum / validCount);
  } else {
    (void)setStatisticsNaN(&statistics);
  }

  return statistics;
}

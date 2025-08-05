#include "stats.h"
#include <stddef.h>
#include <float.h>

struct Stats compute_statistics(const float* numbers, int count) {
    struct Stats statistics;
    float sum = 0.0f;
    statistics.average = 0.0f;
    statistics.min = FLT_MAX;
    statistics.max = -FLT_MAX;

    for (int index = 0; index < count; index++) {
        if (numbers[index] < statistics.min) {
            statistics.min = numbers[index];
        }
        if (numbers[index] > statistics.max) {
            statistics.max = numbers[index];
        }
        sum += numbers[index];
    }

    statistics.average = (sum / count);
    return statistics;
}

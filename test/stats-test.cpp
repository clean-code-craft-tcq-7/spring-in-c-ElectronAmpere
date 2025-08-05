#include "../src/stats.h"

#include "gtest/gtest.h"
#include <math.h>

TEST(Statistics, ReportsAverageMinMax) {
    float values[] = {1.5, 8.9, 3.2, 4.5};
    auto computedStats = compute_statistics(values, 4);
    float epsilon = 0.001;
    EXPECT_LT(fabsf(computedStats.average - 4.525), epsilon);
    EXPECT_LT(fabsf(computedStats.max - 8.9), epsilon);
    EXPECT_LT(fabsf(computedStats.min - 1.5), epsilon);
}

TEST(Statistics, AverageNaNForEmpty) {
    float values[1] = {};
    auto computedStats = compute_statistics(values, 0);
}

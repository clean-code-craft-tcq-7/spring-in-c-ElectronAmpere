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
  // No way to check for NaN other than isnan() function
  EXPECT_TRUE(isnan(computedStats.average));
  EXPECT_TRUE(isnan(computedStats.min));
  EXPECT_TRUE(isnan(computedStats.max));
}

TEST(Statistics, AverageIgnoreNaN) {
  float values[] = {1.5, 8.9, NAN, 4.5};
  auto computedStats = compute_statistics(values, 4);
  float epsilon = 0.001;
  EXPECT_LT(fabsf(computedStats.average - 4.967), epsilon);
  EXPECT_LT(fabsf(computedStats.max - 8.9), epsilon);
  EXPECT_LT(fabsf(computedStats.min - 1.5), epsilon);
}

TEST(Statistics, AverageOfAllNaN) {
  float values[] = {NAN, NAN, NAN};
  auto computedStats = compute_statistics(values, 3);
  EXPECT_TRUE(isnan(computedStats.average));
  EXPECT_TRUE(isnan(computedStats.min));
  EXPECT_TRUE(isnan(computedStats.max));
}

TEST(Statistics, AverageNaNForAbsurdValues) {
  float values[] = {1e10, -1, 8.9, 4.5, 1000};
  auto computedStats = compute_statistics(values, 5);
  float epsilon = 0.001;
  EXPECT_TRUE(isnan(computedStats.average));
  EXPECT_TRUE(isnan(computedStats.min));
  EXPECT_TRUE(isnan(computedStats.max));
}

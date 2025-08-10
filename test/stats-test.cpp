#include "../src/stats.h"

#include "gtest/gtest.h"
#include <climits>
#include <math.h>

TEST(Statistics, ReportsAverageMinMax) {
  float values[] = {1.5, 8.9, 3.2, 4.5};
  auto computedStats = compute_statistics(values, 4);
  float epsilon = 0.001;
  EXPECT_LT(fabsf((float)(computedStats.average - 4.525)), epsilon);
  EXPECT_LT(fabsf((float)(computedStats.max - 8.9)), epsilon);
  EXPECT_LT(fabsf((float)(computedStats.min - 1.5)), epsilon);
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
  EXPECT_LT(fabsf((float)(computedStats.average - 4.967)), epsilon);
  EXPECT_LT(fabsf((float)(computedStats.max - 8.9)), epsilon);
  EXPECT_LT(fabsf((float)(computedStats.min - 1.5)), epsilon);
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

// Test: Valid input, all values in range
TEST(CheckValueAbsurdityTest, AllValuesInRange) {
  float numbers[] = {1.0f, 500.0f, 99999.0f};
  int count = 3;
  EXPECT_EQ(checkValueAbsurdity(numbers, count), 0);
}

// Test: Value out of range (negative)
TEST(CheckValueAbsurdityTest, NegativeValue) {
  float numbers[] = {1.0f, -0.1f, 500.0f};
  int count = 3;
  EXPECT_EQ(checkValueAbsurdity(numbers, count), 1);
}

// Test: Value out of range (too large)
TEST(CheckValueAbsurdityTest, LargeValue) {
  float numbers[] = {1.0f, 100001.0f, 500.0f};
  int count = 3;
  EXPECT_EQ(checkValueAbsurdity(numbers, count), 1);
}

// Test: NULL pointer
TEST(CheckValueAbsurdityTest, NullPointer) {
  EXPECT_EQ(checkValueAbsurdity(NULL, 5), -1);
}

// Test: Negative count
TEST(CheckValueAbsurdityTest, NegativeCount) {
  float numbers[] = {1.0f, 2.0f};
  EXPECT_EQ(checkValueAbsurdity(numbers, -1), -1);
}

// Test: Zero count (empty array)
TEST(CheckValueAbsurdityTest, ZeroCount) {
  float numbers[] = {1.0f};
  EXPECT_EQ(checkValueAbsurdity(numbers, 0), 0); // No elements to check
}

// Test: Large count (potential overflow)
TEST(CheckValueAbsurdityTest, LargeCount) {
  float numbers[] = {1.0f, 2.0f};
  EXPECT_EQ(checkValueAbsurdity(numbers, INT_MAX), -1); // Count too large
}

// Test: Single element in range
TEST(CheckValueAbsurdityTest, SingleElementInRange) {
  float numbers[] = {42.0f};
  EXPECT_EQ(checkValueAbsurdity(numbers, 1), 0);
}

// Test: Single element out of range
TEST(CheckValueAbsurdityTest, SingleElementOutOfRange) {
  float numbers[] = {-42.0f};
  EXPECT_EQ(checkValueAbsurdity(numbers, 1), 1);
}

// Test: Maximum float value
TEST(CheckValueAbsurdityTest, MaxFloatValue) {
  float numbers[] = {std::numeric_limits<float>::max()};
  EXPECT_EQ(checkValueAbsurdity(numbers, 1), 1); // Exceeds 1e5
}

// Test: Subnormal float value
TEST(CheckValueAbsurdityTest, SubnormalValue) {
  float numbers[] = {std::numeric_limits<float>::denorm_min()};
  EXPECT_EQ(checkValueAbsurdity(numbers, 1), 0); // Positive and < 1e5
}

// Tests for setStatisticsNaN
TEST(StatsTest, SetStatisticsNaN_ValidPointer) {
  struct Stats stats;
  EXPECT_EQ(setStatisticsNaN(&stats), 0);
  EXPECT_TRUE(isnan(stats.min));
  EXPECT_TRUE(isnan(stats.max));
  EXPECT_TRUE(isnan(stats.average));
}

TEST(StatsTest, SetStatisticsNaN_NullPointer) {
  EXPECT_EQ(setStatisticsNaN(NULL), -1);
}

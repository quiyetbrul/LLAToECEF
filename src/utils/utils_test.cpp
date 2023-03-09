#include "utils.h"
#include <gtest/gtest.h>

#include <cmath>

TEST(DegreesToRadiansTest, PositiveInput) {
  EXPECT_NEAR(DegreesToRadians(0), 0.0, 1e-8);
  EXPECT_NEAR(DegreesToRadians(45), M_PI / 4, 1e-8);
  EXPECT_NEAR(DegreesToRadians(90), M_PI / 2, 1e-8);
  EXPECT_NEAR(DegreesToRadians(180), M_PI, 1e-8);
  EXPECT_NEAR(DegreesToRadians(360), 2 * M_PI, 1e-8);
}

TEST(KmToMTest, PositiveInput) {
  EXPECT_EQ(KmToM(0), 0);
  EXPECT_EQ(KmToM(1), 1000);
  EXPECT_EQ(KmToM(2.5), 2500);
  EXPECT_EQ(KmToM(10.567), 10567);
}

TEST(MToKmTest, PositiveInput) {
  EXPECT_EQ(MToKm(0), 0);
  EXPECT_EQ(MToKm(1000), 1);
  EXPECT_NEAR(MToKm(2500), 2.5, 1e-8);
  EXPECT_NEAR(MToKm(10567), 10.567, 1e-8);
}

TEST(MathTest, DegreesToRadiansNegativeInput) {
  double input = -90.0;
  double expected_output = -1.5707963267948966;
  double actual_output = DegreesToRadians(input);
  ASSERT_DOUBLE_EQ(expected_output, actual_output);
}

// Test that negative input to KmToM results in an error
TEST(UnitConversionTest, KmToM_NegativeInput) {
  const double input = -1.0;
  EXPECT_THROW(KmToM(input), std::invalid_argument);
}

// Test that negative input to MToKm results in an error
TEST(UnitConversionTest, MToKm_NegativeInput) {
  const double input = -1.0;
  EXPECT_THROW(MToKm(input), std::invalid_argument);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

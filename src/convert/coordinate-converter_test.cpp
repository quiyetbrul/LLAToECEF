#include "coordinate-converter.h"

#include <gtest/gtest.h>

#include <vector>

const double kTime1 = 1532332859.04;
const double kLatitude1 = 53.349800000004094613359484;
const double kLongitude1 = -6.260299999999997311306288;
const double kAltitude1 = 6.096000000000000085265128;

const double kX1 = 3788243.6852759263;
const double kY1 = -415569.34867794393;
const double kZ1 = 5087836.4513731655;

const double kECEFVelX1 = -0.0016901636608815077;
const double kECEFVelY1 = -0.00027120044200990142;
const double kECEFVelZ1 = 0.0033203206609826756;

const double kVelX1 = -0.0016901636608815077;
const double kVelY1 = -0.00027120044200990142;
const double kVelZ1 = 0.0033203206609826756;

class ECEFVelocityCalculatorTest : public ::testing::Test {
protected:
  ECEFVelocityCalculator calculator_;
  void SetUp() override { calculator_ = ECEFVelocityCalculator("../../../data/test_data.csv"); }
};

TEST_F(ECEFVelocityCalculatorTest, ReadsInputFile) {
  // Ensure that the input file was read correctly
  EXPECT_EQ(calculator_.DataPoints().size(), 2);
  EXPECT_DOUBLE_EQ(calculator_.DataPoints()[0].time, 0);
  EXPECT_DOUBLE_EQ(calculator_.DataPoints()[0].latitude, 0);
  EXPECT_DOUBLE_EQ(calculator_.DataPoints()[0].longitude, 0);
  EXPECT_DOUBLE_EQ(calculator_.DataPoints()[0].altitude, 0);

  EXPECT_DOUBLE_EQ(calculator_.DataPoints()[1].time, kTime1);
  EXPECT_DOUBLE_EQ(calculator_.DataPoints()[1].latitude, kLatitude1);
  EXPECT_DOUBLE_EQ(calculator_.DataPoints()[1].longitude, kLongitude1);
  EXPECT_DOUBLE_EQ(calculator_.DataPoints()[1].altitude, kAltitude1);
}

TEST_F(ECEFVelocityCalculatorTest, CalculateECEFVelocityReturnsExpectedOutput) {
  // Create expected output for a small input file
  std::vector<ECEFVelocity> expected_output = {
      {0, 0, 0}, {kECEFVelX1, kECEFVelY1, kECEFVelZ1}};

  // Calculate the ECEF velocities and compare to expected output
  std::vector<ECEFVelocity> actual_output = calculator_.CalculateECEFVelocity();
  for (int i = 0; i < expected_output.size(); i++) {
    ASSERT_DOUBLE_EQ(expected_output[i].x, actual_output[i].x);
    ASSERT_DOUBLE_EQ(expected_output[i].y, actual_output[i].y);
    ASSERT_DOUBLE_EQ(expected_output[i].z, actual_output[i].z);
  }
}

TEST_F(ECEFVelocityCalculatorTest, ConvertsLLAtoECEF) {
  // Ensure that LLA coordinates are correctly converted to ECEF coordinates
  ECEFPosition position =
      calculator_.ConvertLLAtoECEF(kLatitude1, kLongitude1, kAltitude1);
  EXPECT_NEAR(position.x, kX1, 0.1);
  EXPECT_NEAR(position.y, kY1, 0.1);
  EXPECT_NEAR(position.z, kZ1, 0.1);
}

TEST_F(ECEFVelocityCalculatorTest, CalculatesVelocity) {
  // Ensure that the velocity is correctly calculated between two points
  ECEFPosition current_position = {0, 0, 0};
  ECEFPosition next_position = {1, 1, 1};
  ECEFVelocity velocity =
      calculator_.CalculateVelocity(current_position, 0, next_position, 1);
  EXPECT_DOUBLE_EQ(velocity.x, 1);
  EXPECT_DOUBLE_EQ(velocity.y, 1);
  EXPECT_DOUBLE_EQ(velocity.z, 1);
}

TEST_F(ECEFVelocityCalculatorTest, CalculatesECEFVelocity) {
  // Ensure that the ECEF velocities are correctly calculated
  std::vector<ECEFVelocity> velocities = calculator_.CalculateECEFVelocity();

  EXPECT_EQ(velocities.size(), 2);
  EXPECT_DOUBLE_EQ(velocities[0].x, 0);
  EXPECT_DOUBLE_EQ(velocities[0].y, 0);
  EXPECT_DOUBLE_EQ(velocities[0].z, 0);

  EXPECT_NEAR(velocities[1].x, kVelX1, 0.0001);
  EXPECT_NEAR(velocities[1].y, kVelY1, 0.0001);
  EXPECT_NEAR(velocities[1].z, kVelZ1, 0.0001);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

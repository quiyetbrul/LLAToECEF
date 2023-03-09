#include <iomanip>
#include <iostream>

#include "convert/coordinate-converter.h"

const std::string FILE_NAME = "../data/DATA.csv";
const double CURRENT_TIME = 1532334000.0;
const double NEXT_TIME = 1532335268.0;

int main() {
  // provided data has 24 decimal places
  std::cout << std::fixed;
  std::cout << std::setprecision(24);

  // Create an instance of the ECEFVelocityCalculator class
  ECEFVelocityCalculator calculator(FILE_NAME);
  // Calculate the ECEF velocities
  std::vector<ECEFVelocity> velocities =
      calculator.CalculateECEFVelocity(CURRENT_TIME, NEXT_TIME);

  // Print the velocities
  for (const auto &v : velocities) {
    std::cout << v.x << ", " << v.y << ", " << v.z << std::endl;
  }

  return 0;
}

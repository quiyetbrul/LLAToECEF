#include "utils.h"

#include <cmath>
#include <stdexcept>
#include <vector>

double DegreesToRadians(const double &degrees) {
  return degrees * M_PI / 180.0f;
}

// provided formula uses meters
double KmToM(const double &kilometers) {
  if (kilometers < 0) {
    throw std::invalid_argument("Invalid input");
  }

  return kilometers * 1000.0;
}

// provided data is in kilometers
double MToKm(const double &meters) {
  if (meters < 0) {
    throw std::invalid_argument("Invalid input");
  }
  return meters / 1000.0;
}

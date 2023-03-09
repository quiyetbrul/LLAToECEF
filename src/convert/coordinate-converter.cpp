#include "coordinate-converter.h"

#include "../utils/utils.h"

ECEFVelocityCalculator::ECEFVelocityCalculator() = default;

ECEFVelocityCalculator::ECEFVelocityCalculator(const std::string &file_name)
    : data_(ReadCSVFile(file_name)) {}

std::vector<ECEFVelocity> ECEFVelocityCalculator::CalculateECEFVelocity() {
  std::vector<ECEFVelocity> velocities;

  // Calculate the velocities at each point
  for (int i = 0; i < data_.size() - 1; i++) {
    // Get the position and time at the current point
    ECEFPosition current_position = ConvertLLAtoECEF(
        data_[i].latitude, data_[i].longitude, data_[i].altitude);
    double current_time = data_[i].time;

    // Get the position and time at the next point
    ECEFPosition next_position = ConvertLLAtoECEF(
        data_[i + 1].latitude, data_[i + 1].longitude, data_[i + 1].altitude);
    double next_time = data_[i + 1].time;

    // Calculate the velocity between the two points
    ECEFVelocity velocity = CalculateVelocity(current_position, current_time,
                                              next_position, next_time);

    // Add the velocity to the list of velocities
    velocities.push_back(velocity);
  }

  // Add a zero velocity for the first point
  velocities.insert(velocities.begin(), {0, 0, 0});

  return velocities;
}

std::vector<ECEFVelocity>
ECEFVelocityCalculator::CalculateECEFVelocity(const double &current_time,
                                              const double &next_time) {
  std::vector<ECEFVelocity> velocities;

  // Calculate the velocities at each point
  for (int i = 0; i < data_.size() - 1; i++) {
    // Get the position and time at the current point
    ECEFPosition current_position = ConvertLLAtoECEF(
        data_[i].latitude, data_[i].longitude, data_[i].altitude);

    // Get the position and time at the next point
    ECEFPosition next_position = ConvertLLAtoECEF(
        data_[i + 1].latitude, data_[i + 1].longitude, data_[i + 1].altitude);

    // Calculate the velocity between the two points
    ECEFVelocity velocity = CalculateVelocity(current_position, current_time,
                                              next_position, next_time);

    // Add the velocity to the list of velocities
    velocities.push_back(velocity);
  }

  // Add a zero velocity for the first point
  velocities.insert(velocities.begin(), {0, 0, 0});

  return velocities;
}

std::vector<DataPoint> ECEFVelocityCalculator::DataPoints() const {
  return data_;
}

// Convert latitude, longitude, altitude to ECEF coordinates
ECEFPosition
ECEFVelocityCalculator::ConvertLLAtoECEF(const double &latitude,
                                         const double &longitude,
                                         const double &altitude) const {
  double sinLat = std::sin(DegreesToRadians(latitude));
  double cosLat = std::cos(DegreesToRadians(latitude));
  double cosLon = std::cos(DegreesToRadians(longitude));
  double sinLon = std::sin(DegreesToRadians(longitude));
  const double ALT = KmToM(altitude); // provided data is in kilometers, but
                                      // calculations are done in meters

  double N = RadiusOfCurvature(latitude);
  double x = (N + ALT) * cosLat * cosLon;
  double y = (N + ALT) * cosLat * sinLon;
  double z = (N * (1 - WGS84_E_SQ) + ALT) * sinLat;

  // return {MToKm(x), MToKm(y), MToKm(z)}; // return to original unit of length
  return {x, y, z};
}

// Calculate the velocity between two points using linear interpolation
ECEFVelocity ECEFVelocityCalculator::CalculateVelocity(
    const ECEFPosition &current_position, const double &current_time,
    const ECEFPosition &next_osition, const double &next_time) const {
  double delta_time = std::abs(next_time - current_time);

  double deltaX = next_osition.x - current_position.x;
  double deltaY = next_osition.y - current_position.y;
  double deltaZ = next_osition.z - current_position.z;

  double velX = deltaX / delta_time;
  double velY = deltaY / delta_time;
  double velZ = deltaZ / delta_time;

  return {velX, velY, velZ};
}

#ifndef _COORDINATE_CONVERTER_H_
#define _COORDINATE_CONVERTER_H_

#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

const double WGS84_F = 1.0 / 298.257223563;
const double WGS84_A = 6378137.0;
const double WGS84_B = WGS84_A * (1.0 - WGS84_F);
const double WGS84_E_SQ = (pow(WGS84_A, 2) - pow(WGS84_B, 2)) / pow(WGS84_A, 2);

// A struct to represent a data point
struct DataPoint {
  double time;
  double latitude;
  double longitude;
  double altitude;
};

// A struct to represent a position in ECEF coordinates
struct ECEFPosition {
  double x;
  double y;
  double z;
};

// A struct to represent a velocity in ECEF coordinates
struct ECEFVelocity {
  double x;
  double y;
  double z;
};

// A class to calculate ECEF velocities
class ECEFVelocityCalculator {
public:
  // Constructor
  ECEFVelocityCalculator();
  explicit ECEFVelocityCalculator(const std::string &file_name);

  // Get the data points
  std::vector<DataPoint> DataPoints() const;

  // Calculate the ECEF velocities
  std::vector<ECEFVelocity>
  CalculateECEFVelocity(); // this takes time from the CSV file
  std::vector<ECEFVelocity> CalculateECEFVelocity(const double &current_time,
                                                  const double &next_time);

  // NOTE: These methods are made public for testing purposes. Otherwise, these
  // can be privatized OR be part of the CPP file.
  // Convert latitude, longitude, altitude to ECEF coordinates
  ECEFPosition ConvertLLAtoECEF(const double &latitude, const double &longitude,
                                const double &altitude) const;
  // Calculate the velocity between two points using linear interpolation
  ECEFVelocity CalculateVelocity(const ECEFPosition &current_position,
                                 const double &current_time,
                                 const ECEFPosition &next_position,
                                 const double &next_time) const;

private:
  std::vector<DataPoint> data_;

  double RadiusOfCurvature(const double &latitude) const {
    return WGS84_A / sqrt(1 - WGS84_E_SQ * pow(sin(latitude), 2));
  }

  // Read data from a CSV file
  std::vector<DataPoint> ReadCSVFile(const std::string &file_name) const {
    std::vector<DataPoint> data;

    std::ifstream file(file_name);
    if (!file) {
      throw std::invalid_argument(file_name +
                                  " could not be opened or does not exist");
    }
    std::string line;
    while (getline(file, line)) {
      std::stringstream ss(line);
      DataPoint data_point;

      getline(ss, line, ',');
      data_point.time = stod(line);

      getline(ss, line, ',');
      data_point.latitude = stod(line);

      getline(ss, line, ',');
      data_point.longitude = stod(line);

      getline(ss, line);
      data_point.altitude = stod(line);

      data.push_back(data_point);
    }

    return data;
  }
};

#endif // _COORDINATE_CONVERTER_H_

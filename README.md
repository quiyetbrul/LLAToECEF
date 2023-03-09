# LLA To ECEF Velocity

The solution is a C++ class that takes in an input CSV file containing time, latitude, longitude, and altitude data points. It then converts these LLA (latitude, longitude, altitude) points to ECEF (Earth-centered, Earth-fixed) points and calculates the ECEF velocity at each point using linear interpolation.

## Requirements

- C++ compiler with C++17 or above support
- [CMake 3.0.0](https://cmake.org/) or above
- [Google Test](https://github.com/google/googletest)

## Build

- If you don't have the requirements mentioned above, run

  ```bash
    sudo apt-get install gcc cmake libgtest-dev
  ```

- You might need to build the Google Test framework first
  - navigate to the source directory of Google Test. PS. The directory might differ
    ```bash
      cd /usr/src/googletest
    ```
  - create a directory and navigate into it
    ```bash
      mkdir build; cd build;
    ```
  - generate the build files using CMake
    ```bash
      cmake ..
    ```
  - compile the framework
    ```bash
      make
    ```
  - install the framework
    ```bash
      sudo make install
    ```
  - verify that the framework is installed correctly
    ```bash
      sudo ldconfig -v | grep gtest
    ```
  - If the installation is successful, you should see output similar to the following:
    ```bash
    libgtest.so.0 -> libgtest.so.0.0.0
    libgtest.so -> libgtest.so.0
    ```
- Run the shell script in the project root directory to compile and run the program
  ```bash
    sh makerun.sh
  ```

## Testing

- To run the unit tests, run the following command
  ```terminal
    sh maketest.sh
  ```
- Alternatively, you may run the commands inside `maketest.sh` on the terminal separately
- Please note that scientific calculations may differ from OS to OS and distro to distro. For this case, calculations are done and tested on both macOS Ventura 13.2.1 and gLinux, a Debian Testing-based Linux distribution used at Google. Variations of scientific calculations may cause different results and failures in the unit tests.

## Clean

- Run the following command from the root directory:

```terminal
  sh makeclean.sh
```

## For scripts

If invoking the scripts using `sh file_name.sh` doesn't work, follow these online [instructions](https://www.cyberciti.biz/faq/how-to-execute-a-shell-script-in-linux/).

## Usage

The program takes the input trajectory from a CSV file where the first column is time in seconds, the second column is latitude in decimal degrees, the third column is longitude in decimal degrees, and the fourth column is the altitude in kilometers.

The class has a constructor that takes in the filename of the input CSV file. The CSV file is read and parsed using the `ReadCSVFile()` method. This method reads each line of the CSV file and converts the comma-separated values into a vector of vectors of doubles.

The `CalculateECEFVelocity()` method calculates the ECEF velocity at each point using linear interpolation. It does this by iterating through the vector of vectors of doubles and calculating the ECEF position and time for the current point and the next point. It then calculates the velocity between these two points using the `CalculateVelocity()` method and adds it to a vector of ECEF velocities.

Note that there are overloaded methods to calculate the ECEF velocity. The instructions provided weren't clear why there are three different time values for when doing the calculations (one time value per line from the CSV file and two time values in the OUTPUT section of the PDF file). The first method calculates the ECEF velocity using the time values from the CSV file. The second method calculates the ECEF velocity using the time values from the OUTPUT section of the PDF file. I decided to use the second method in the main.cpp file because I reckon the instructions in the OUTPUT section take precedence.

The `ConvertLLAtoECEF()` method takes in the latitude, longitude, and altitude of a point and converts it to ECEF coordinates using the WGS84 model of the Earth.

The `CalculateVelocity()` method takes in the ECEF position and time for the current point and the next point and calculates the velocity between these two points using linear interpolation.

Note that the `ConvertLLAtoECEF()` and `CalculateVelocity()` methods are deliberately made public. I wanted these methods to be isolated in testing. Otherwise, they should either be private OR included in the .cpp file.

The `DataPoints()` method returns the vector of vectors of doubles containing the data points read from the CSV file. This method can be useful if the user needs to access the original data points for further analysis.

The solution also includes unit tests written using Google Test to ensure the correctness of the class methods. These tests cover the functionality of the `ReadCSVFile(),` `ConvertLLAtoECEF(),` `CalculateVelocity(),` and `CalculateECEFVelocity()` methods, and utility functions like `KmToM(),` `MToKm(),` and `DegreesToRadians().`

Overall, the solution provides a class-based implementation for calculating ECEF velocities from LLA data points, and includes unit tests to ensure correctness.

## Time Complexity

### Main methods and functions

The time and space complexity of this solution depends on the number of data points in the input file, which is denoted by n.

The time complexity of the `ReadCSVFile()` method is O(n), because it reads each line of the input file exactly once, and performs a constant amount of work per line.

The time complexity of the `CalculateECEFVelocity()` method is O(n), because it loops through the data once, and performs a constant amount of work per data point.

The time complexity of the `ConvertLLAtoECEF()` method is O(1), because it performs a constant amount of work, regardless of the size of the input.

The space complexity of this solution is also O(n), because the data member variable of the `class ECEFVelocityCalculator` stores all of the data points from the input file, which requires O(n) space.

### Utility functions

`DegreesToRadians()`: This function performs a single arithmetic operation and returns a value, so its time complexity is O(1). It does not use any additional memory beyond the function's parameters and return value, so its space complexity is O(1).

`KmToM()`: This function performs a single arithmetic operation and returns a value, so its time complexity is O(1). It does not use any additional memory beyond the function's parameters and return value, so its space complexity is O(1).

`MToKm()`: This function performs a single arithmetic operation and returns a value, so its time complexity is O(1). It does not use any additional memory beyond the function's parameters and return value, so its space complexity is O(1).

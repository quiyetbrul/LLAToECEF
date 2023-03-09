# # Define the Convert library
# add_library(Convert
# coordinate-converter.cpp
# coordinate-converter.h
# )

# Define the Convert library
add_library(Convert
  coordinate-converter.cpp
  coordinate-converter.h
)

# Define the Convert test target
add_executable(Convert_test
  coordinate-converter_test.cpp
)

# Link the Convert test target with Google Test and the Convert library
target_link_libraries(Convert_test ${GTEST_LIBRARIES} Convert Utils)

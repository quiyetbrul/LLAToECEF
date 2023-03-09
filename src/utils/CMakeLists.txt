# # Define the Utils library
# add_library(Utils
# utils.cpp
# utils.h
# )

# Define the Utils library
add_library(Utils
  utils.cpp
  utils.h
)

# Define the Utils test target
add_executable(Utils_test
  utils_test.cpp
)

# Link the Utils test target with Google Test and the Utils library
target_link_libraries(Utils_test ${GTEST_LIBRARIES} Utils)

cmake_minimum_required(VERSION 2.6)
project(H5Utils)

#
# Check requirements
#
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

### Fixed-size types
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STDC_LIMIT_MACROS")

#
# Executable
#
add_executable(H5Utils src/main.cpp src/h5utils.cpp)

#
# Link libraries
#
#target_link_libraries(H5Utils rt)
target_link_libraries(H5Utils hdf5 hdf5_cpp)
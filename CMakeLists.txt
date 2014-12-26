cmake_minimum_required(VERSION 2.8)
project(terramechanics)
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(bin)
add_subdirectory(include)
INCLUDE_DIRECTORIES("${CMAKE_BINARY_DIR}/include" "/usr/include/python2.7/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

add_library(terramecha STATIC src/bevameter.cpp src/shear.cpp src/angle.cpp src/wheel_soil.cpp src/intdiff.cpp src/vane.cpp src/bevameter.cpp)
target_link_libraries(terramecha gsl)
add_library(terramecha-share SHARED src/bevameter.cpp src/shear.cpp src/angle.cpp src/wheel_soil.cpp src/intdiff.cpp src/vane.cpp src/bevameter.cpp)
set_target_properties(terramecha-share PROPERTIES COMPILE_FLAGS "-DPIC")
target_link_libraries(terramecha-share gsl)
add_library(pyterramechanics MODULE
  src/pyterramechanics.cpp
  src/angle.cpp
  src/bevameter.cpp)
set_target_properties(pyterramechanics PROPERTIES COMPILE_FLAGS "-fPIC -DPIC")
set_target_properties(pyterramechanics PROPERTIES PREFIX "")
target_link_libraries(pyterramechanics boost_python python2.7)

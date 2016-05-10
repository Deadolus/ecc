###############################################################################
cmake_minimum_required(VERSION 3.2)
project(ecc)
###############################################################################

add_library(googletest
  googletest-release-1.7.0/src/gtest-all.cc)

target_include_directories(googletest
  PUBLIC googletest-release-1.7.0/include
  PRIVATE googletest-release-1.7.0
  )

target_link_libraries(googletest
  PUBLIC pthread)

add_library(googlemock
  googlemock-release-1.7.0/src/gmock-all.cc)

target_include_directories(googlemock
  PUBLIC googlemock-release-1.7.0/include
  PRIVATE googlemock-release-1.7.0
  )

target_link_libraries(googlemock
  PUBLIC googletest)

add_library(googlemock-main
  googlemock-release-1.7.0/src/gmock_main.cc)

target_link_libraries(googlemock-main
  PUBLIC googlemock)

###############################################################################

add_library(ecc
  ecc/ecc.cc
  ecc/key.cc)

target_include_directories(ecc
  PUBLIC ecc/include)

set_property(TARGET ecc PROPERTY CXX_STANDARD 14)

###############################################################################

enable_testing()

add_executable(ecc-test
  ecc-test/ecc.cc
  )

target_link_libraries(ecc-test
  PRIVATE googlemock-main)

set_property(TARGET ecc-test PROPERTY CXX_STANDARD 14)

add_test(NAME check-ecc COMMAND ecc-test)

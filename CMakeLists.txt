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

add_library(matrixssl
  matrixssl-3-8-3-open/core/corelib.c
  matrixssl-3-8-3-open/core/memset_s.c
  matrixssl-3-8-3-open/core/POSIX/osdep.c
  matrixssl-3-8-3-open/crypto/digest/sha1.c
  matrixssl-3-8-3-open/crypto/keyformat/asn1.c
  matrixssl-3-8-3-open/crypto/math/pstm.c
  matrixssl-3-8-3-open/crypto/math/pstm_montgomery_reduce.c
  matrixssl-3-8-3-open/crypto/math/pstm_mul_comba.c
  matrixssl-3-8-3-open/crypto/math/pstm_sqr_comba.c
  matrixssl-3-8-3-open/crypto/pubkey/ecc.c
  matrixssl-3-8-3-open/crypto/prng/prng.c
  matrixssl-3-8-3-open/crypto/layer/matrix.c
  )

target_include_directories(matrixssl
  PUBLIC matrixssl-3-8-3-open
  )

###############################################################################

add_library(ecc
  ecc/ecc.cc
  ecc/key.cc
  ecc/util.cc)

target_include_directories(ecc
  PUBLIC ecc/include)

target_link_libraries(ecc
  PUBLIC matrixssl)

set_property(TARGET ecc PROPERTY CXX_STANDARD 14)

###############################################################################

enable_testing()

add_executable(ecc-test
  ecc-test/ecc.cc
  ecc-test/util.cc)

target_link_libraries(ecc-test
  PRIVATE googlemock-main
  PRIVATE ecc)

set_property(TARGET ecc-test PROPERTY CXX_STANDARD 14)

add_test(NAME check-ecc COMMAND ecc-test)

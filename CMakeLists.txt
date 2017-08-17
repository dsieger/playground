project(playground)
cmake_minimum_required(VERSION 2.8)

set(GOOGLE_TEST_ROOT external/googletest/googletest CACHE STRING "Google Test root")

include_directories(
  ${PROJECT_SOURCE_DIR}/${GOOGLE_TEST_ROOT}
  ${PROJECT_SOURCE_DIR}/${GOOGLE_TEST_ROOT}/include
  )

set(GOOGLE_TEST_SOURCES
  ${PROJECT_SOURCE_DIR}/${GOOGLE_TEST_ROOT}/src/gtest-all.cc
  ${PROJECT_SOURCE_DIR}/${GOOGLE_TEST_ROOT}/src/gtest_main.cc
  )

add_library(googletest ${GOOGLE_TEST_SOURCES})

add_executable(asdf main.cpp)
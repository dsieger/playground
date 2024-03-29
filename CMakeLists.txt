cmake_minimum_required(VERSION 3.6)
project(playground)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" AND CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
  set(CMAKE_C_FLAGS "-g -O0 -W -fprofile-arcs -ftest-coverage")
  set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
endif()

add_library(asdf test.cpp)
if(WIN32)
  target_link_libraries(asdf Psapi.lib)
endif()

set(GOOGLE_TEST_ROOT
    external/googletest/googletest
    CACHE STRING "Google Test root")

include_directories(
  ${PROJECT_SOURCE_DIR}/ ${PROJECT_SOURCE_DIR}/${GOOGLE_TEST_ROOT}
  ${PROJECT_SOURCE_DIR}/${GOOGLE_TEST_ROOT}/include)

set(GOOGLE_TEST_SOURCES
    ${PROJECT_SOURCE_DIR}/${GOOGLE_TEST_ROOT}/src/gtest-all.cc
    ${PROJECT_SOURCE_DIR}/${GOOGLE_TEST_ROOT}/src/gtest_main.cc)

add_library(googletest ${GOOGLE_TEST_SOURCES})

add_executable(unitTests tests/main.cpp tests/trivial.cpp)
add_dependencies(unitTests googletest)

if(UNIX OR APPLE)
  target_link_libraries(unitTests asdf googletest pthread)
elseif(WIN32)
  target_link_libraries(unitTests asdf googletest)
endif()

include(CTest)
enable_testing()

add_test(unitTest ${PROJECT_BINARY_DIR}/unitTests)

set(CPACK_PACKAGE_VERSION 1.0)
set(CPACK_SOURCE_PACKAGE_FILE_NAME
    "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_SOURCE_IGNORE_FILES "/build/;/.git/;~$;${CPACK_SOURCE_IGNORE_FILES}")
set(CPACK_SOURCE_GENERATOR "ZIP")
include(CPack)

add_subdirectory(docs)

if(ENABLE_COVERAGE)

  # set compiler flags
  set(CMAKE_CXX_FLAGS "-O0 -coverage")

  # find required tools
  find_program(LCOV lcov REQUIRED)
  find_program(GENHTML genhtml REQUIRED)

  # add coverage target
  add_custom_target(
    coverage
    # gather data
    COMMAND ${LCOV} --directory . --capture --output-file coverage.info
    # generate report
    COMMAND ${GENHTML} --demangle-cpp -o coverage coverage.info
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

add_executable(test2 test2.cpp)

cmake_minimum_required(VERSION 3.1)

project(rsa-crypto-project)

set(EXECUTABLE_OUTPUT_PATH bin)

include_directories(./include)
include_directories("~/Documents/GMP/include")
link_directories("~/Documents/GMP/lib")

file(GLOB_RECURSE SOURCES "src/*")

add_executable(alea_csv ${SOURCES} mains/alea_primary_into_csv.c)

target_link_libraries(
  alea_csv
  gmp
)

add_executable(fabrique_test ${SOURCES} mains/fabrique_test.c)

target_link_libraries(
  fabrique_test
  gmp
)

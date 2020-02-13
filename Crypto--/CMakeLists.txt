cmake_minimum_required(VERSION 3.1)

project(aes-crypto-project)

set(EXECUTABLE_OUTPUT_PATH bin)

include_directories(./include)

file(GLOB_RECURSE SOURCES "src/*")

file(GLOB_RECURSE JAM_TEST_SRC "test/BourrageTest/*")

add_executable(jam_test ${SOURCES} ${JAM_TEST_SRC})
target_compile_features(jam_test PUBLIC cxx_std_17)
target_link_libraries(
  jam_test
  cppunit
)

add_executable(crypter_hello ${SOURCES} test/Crypter/hello_world.cpp)
target_compile_features(crypter_hello PUBLIC cxx_std_17)

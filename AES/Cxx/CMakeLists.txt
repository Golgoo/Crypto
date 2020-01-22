cmake_minimum_required(VERSION 3.1)

project(aes-crypto-project)

set(EXECUTABLE_OUTPUT_PATH bin)

include_directories(./include)

file(GLOB_RECURSE SOURCES "src/*")

add_executable(aes ${SOURCES} mains/main.cpp)

target_compile_features(aes PUBLIC cxx_std_17)

add_executable(tests ${SOURCES} mains/tests.cpp)
target_compile_features(tests PUBLIC cxx_std_17)

target_link_libraries(
        aes
        m
)

target_link_libraries(
  tests
  m cppunit
)

#target_link_libraries(
#        divers
#        m
#)

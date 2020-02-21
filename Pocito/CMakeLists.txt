cmake_minimum_required(VERSION 3.1)

project(pocito)

set(EXECUTABLE_OUTPUT_PATH bin)

include_directories(./include)

include_directories("../Crypto--/include/")
link_directories("../Crypto--/lib/")

file(GLOB_RECURSE SOURCES "src/*")

add_executable(pocito_app ${SOURCES})
target_compile_features(pocito_app PUBLIC cxx_std_17)
target_link_libraries(
  pocito_app
  cryptom
)

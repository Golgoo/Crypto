cmake_minimum_required(VERSION 3.1)

project(aes-crypto-project)

set(EXECUTABLE_OUTPUT_PATH bin)

include_directories(./include)

file(GLOB_RECURSE SOURCES "src/*")

add_executable(aes ${SOURCES} mains/main.cpp)
#add_executable(divers ${SOURCES} mains/divers.cpp)

target_compile_features(aes PUBLIC cxx_std_17)
#target_compile_features(divers PUBLIC cxx_std_17)

target_link_libraries(
        aes
        m
)

#target_link_libraries(
#        divers
#        m
#)

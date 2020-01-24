cmake_minimum_required(VERSION 3.1)

project(aes-crypto-project)

set(EXECUTABLE_OUTPUT_PATH bin)

include_directories(./include)

file(GLOB_RECURSE SOURCES "src/*")

add_executable(aes ${SOURCES} mains/aes_chiffrement.cpp)
target_compile_features(aes PUBLIC cxx_std_17)

add_executable(aes_d ${SOURCES} mains/aes_dechiffrement.cpp)
target_compile_features(aes_d PUBLIC cxx_std_17)

#Si vous n'avez pas CPPUnit commentez ces deux lignes
#add_executable(tests ${SOURCES} mains/tests.cpp)
#target_compile_features(tests PUBLIC cxx_std_17)

add_executable(key_ext ${SOURCES} mains/key_extension.cpp)
target_compile_features(key_ext PUBLIC cxx_std_17)

target_link_libraries(
        aes
        m
)

target_link_libraries(
        key_ext
        m
)

target_link_libraries(
        aes_d
        m
)

#Si vous n'avez pas CPPUnit commentez ce bloc
#target_link_libraries(
#  tests
#  m cppunit
#)

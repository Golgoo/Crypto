cmake_minimum_required(VERSION 3.1)

project(aes-crypto-project)

set(EXECUTABLE_OUTPUT_PATH bin)

include_directories(./include)

file(GLOB_RECURSE SOURCES "src/*")

option(BUILD_CPPUNIT_TEST "Construire les tests CppUnits" OFF)

if(BUILD_CPPUNIT_TEST)
  file(GLOB_RECURSE JAM_TEST_SRC "test/BourrageTest/*")

  add_executable(jam_test ${SOURCES} ${JAM_TEST_SRC})
  target_compile_features(jam_test PUBLIC cxx_std_17)
  target_link_libraries(
    jam_test
    cppunit
  )

  file(GLOB_RECURSE OP_MODEL_SRC "test/OperatingModel/*")

  add_executable(op_model_test ${SOURCES} ${OP_MODEL_SRC})
  target_compile_features(op_model_test PUBLIC cxx_std_17)
  target_link_libraries(
    op_model_test
    cppunit
  )
endif()


add_executable(crypter_hello ${SOURCES} test/Crypter/hello_world.cpp)
target_compile_features(crypter_hello PUBLIC cxx_std_17)

add_executable(cbc_hello ${SOURCES} test/Crypter/Cbc_Hello.cpp)
target_compile_features(cbc_hello PUBLIC cxx_std_17)

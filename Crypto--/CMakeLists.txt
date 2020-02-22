cmake_minimum_required(VERSION 3.1)

project(aes-crypto-project)

set(EXECUTABLE_OUTPUT_PATH bin)

include_directories(./include)

include_directories("~/Documents/GMP/include")
link_directories("~/Documents/GMP/lib")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib/)
file(GLOB_RECURSE SOURCES "src/*")
add_library(cryptom SHARED ${SOURCES})


target_compile_features(cryptom PUBLIC cxx_std_17)
target_link_libraries(
  cryptom
  gmp
  crypto
)

#Si vous ne possédez pas CPPUNIT, cette option doit être à OFF
option(BUILD_CPPUNIT_TEST "Construire les tests CppUnits" ON)


if(BUILD_CPPUNIT_TEST)
  file(GLOB_RECURSE JAM_TEST_SRC "test/Padder/*")

  add_executable(jam_test ${JAM_TEST_SRC})
  target_compile_features(jam_test PUBLIC cxx_std_17)
  target_link_libraries(
    jam_test
    cryptom
    cppunit
  )

  file(GLOB_RECURSE OP_MODEL_SRC "test/Cipher/*")

  add_executable(op_model_test ${OP_MODEL_SRC})
  target_compile_features(op_model_test PUBLIC cxx_std_17)
  target_link_libraries(
    op_model_test
    cryptom
    cppunit
  )

  file(GLOB_RECURSE RSA_TEST_SRC "test/Crypter/RSA/*")
  add_executable(rsa_test ${RSA_TEST_SRC})
  target_compile_features(rsa_test PUBLIC cxx_std_17)
  target_link_libraries(
    rsa_test
    cryptom
    cppunit
  )

  file(GLOB_RECURSE RSA_TEST_SRC "test/Crypter/AES/*")
  add_executable(aes_test ${RSA_TEST_SRC})
  target_compile_features(aes_test PUBLIC cxx_std_17)
  target_link_libraries(
    aes_test
    cryptom
    cppunit
  )
endif()

add_executable(main_for_no_cppunit___ test/tmpMain.cpp)
target_compile_features(main_for_no_cppunit___ PUBLIC cxx_std_17)

target_link_libraries(
  main_for_no_cppunit___
  cryptom

)

add_executable(crypter_hello test/Crypter/hello_world.cpp)
target_compile_features(crypter_hello PUBLIC cxx_std_17)

target_link_libraries(
  crypter_hello
  cryptom
)

add_executable(cbc_hello test/Crypter/Cbc_Hello.cpp)
target_compile_features(cbc_hello PUBLIC cxx_std_17)

target_link_libraries(
  cbc_hello
  cryptom
)

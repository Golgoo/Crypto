cmake_minimum_required(VERSION 3.1)

project(hmac-crypto-project)

set(EXECUTABLE_OUTPUT_PATH bin)

set(COMMOM_SRC src/HMAC.cpp src/MiniMimeMailer.cpp)
file(GLOB_RECURSE CERT ${COMMOM_SRC} src/cert.cpp )
file(GLOB_RECURSE CHECK ${COMMOM_SRC} src/check.cpp)

include_directories(./include)

add_executable(cert ${CERT})
add_executable(check ${CHECK})

target_compile_features(cert PUBLIC cxx_std_17)
target_compile_features(check PUBLIC cxx_std_17)

target_link_libraries(
        cert
        m ssl crypto
)
target_link_libraries(
        check
        m ssl crypto
)

cmake_minimum_required(VERSION 3.1)

project(hmac-crypto-project)

set(EXECUTABLE_OUTPUT_PATH bin)

set(COMMOM_SRC src/HMAC.cpp src/MiniMimeMailer.cpp)

include_directories(./include)

add_executable(cert ${COMMOM_SRC} src/cert.cpp)
add_executable(check ${COMMOM_SRC} src/check.cpp)

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

cmake_minimum_required(VERSION 3.10)
project(CyberSandbox LANGUAGES CXX)
add_executable(Payload ./src/payloadTest.cpp)
target_link_libraries(Payload ws2_32.lib)
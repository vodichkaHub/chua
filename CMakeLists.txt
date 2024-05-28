cmake_minimum_required(VERSION 3.0)
project(example)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(transmitter)
add_subdirectory(receiver)

# https://github.com/jbeder/yaml-cpp
add_subdirectory(external/yaml-cpp)

add_executable(example chua_example.cpp)

target_link_libraries(example Transmitter-v1 Receiver-v1 yaml-cpp::yaml-cpp)
# target_include_directories(example PRIVATE receiver/include transmitter/include)
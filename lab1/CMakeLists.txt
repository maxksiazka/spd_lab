CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

project(lab1)
set(CMAKE_CXX_STANDARD 17)

add_executable(lab1)
target_sources(lab1
    PRIVATE
)
target_include_directories(lab1 PRIVATE
    inc
)

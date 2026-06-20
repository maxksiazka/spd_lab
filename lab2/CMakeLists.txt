CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

project(lab2)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) #nie usuwaj bo zastrzelę
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

add_executable(lab2
    main.cpp
    src/problem.cpp
    src/solution.cpp
    src/LookThroughSolver.cpp
    src/NEHSolver.cpp
    src/JohnsonFor2M.cpp
    src/BranchAndBound.cpp
    src/FNEHSolver.cpp
)
target_include_directories(lab2 PRIVATE
    inc
)
# add_custom_command(TARGET lab1 POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy
#     ${CMAKE_SOURCE_DIR}/test.txt ${CMAKE_BINARY_DIR}/test.txt
# )

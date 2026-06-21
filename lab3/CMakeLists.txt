CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

project(lab3)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) #nie usuwaj bo zastrzelę
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

add_executable(${PROJECT_NAME}
    main.cpp
    src/problem.cpp
    src/solution.cpp
    src/LSASolver.cpp
    src/LPTSolver.cpp
    src/DynamicSolver.cpp
    src/PTASSolver.cpp
    src/BranchAndBoundSolver.cpp
    src/LookThroughSolver.cpp
    src/FPTASSolver.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE
    inc
)
# add_custom_command(TARGET lab1 POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy
#     ${CMAKE_SOURCE_DIR}/test.txt ${CMAKE_BINARY_DIR}/test.txt
# )

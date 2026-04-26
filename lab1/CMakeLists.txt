CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

project(lab1)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) #nie usuwaj bo zastrzelę
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

add_executable(lab1)
target_sources(lab1 PRIVATE
    main.cpp
    src/problem.cpp
    src/solution.cpp
    src/EDDsolver.cpp
    src/ERDsolver.cpp
    src/LookThroughSolver.cpp
    src/SchrageSolver.cpp
    src/PreemptSchrageSolver.cpp
    src/ConstructionSolver.cpp
    src/CarlierSolver.cpp
)
target_include_directories(lab1 PRIVATE
    inc
)
add_custom_command(TARGET lab1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/test.txt ${CMAKE_BINARY_DIR}/test.txt
)
add_custom_command(TARGET lab1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/100_Independent0290 ${CMAKE_BINARY_DIR}/100_Independent0290
)

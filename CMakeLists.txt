cmake_minimum_required(VERSION 3.10)

project(KnapsackProblemSolver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(KnapsackProblemSolver
    src/main.cpp
    src/knapsack_problem_instance.cpp
    src/knapsack_solution_instance.cpp
    src/simulated_annealing_solver.cpp
)

include_directories(${PROJECT_SOURCE_DIR} lib)

add_custom_target(
    run
    COMMAND $<TARGET_FILE:KnapsackProblemSolver>
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Building and running the Knapsack Problem Solver"
)

add_dependencies(run KnapsackProblemSolver)

cmake_minimum_required(VERSION 3.20)

project(my_app)

set(CMAKE_CXX_STANDARD 17)


set(Boost_ROOT "C:/Boost")
find_package(Boost REQUIRED COMPONENTS program_options)

set(Z3_INCLUDE_DIR "C:/z3/src/api")
set(Z3_LIBRARY "C:/z3/build/Release/libz3.lib")

include_directories(${Z3_INCLUDE_DIR})

add_executable(solve_add
        solve_add/solve_add.cpp
        solve_add/fpa_to_float.cpp
        solve_add/RandomFpa32.cpp
)

add_executable(solve_random
        solve_random/solve_random.cpp
        solve_random/fpa_to_float.cpp
        solve_random/makeRegs.cpp
        solve_random/pseudoOperations.cpp
        solve_random/getOperations.cpp
        solve_random/addLimits.cpp
)

add_executable(sequence_generator
        sequence_generator/sequence_generator.cpp
        sequence_generator/solveRandomApply.cpp
        sequence_generator/genSeq.cpp
        sequence_generator/Instruction.h
        sequence_generator/fpa_to_float.cpp
)

target_include_directories(solve_add PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(solve_add PRIVATE ${Boost_LIBRARIES} ${Z3_LIBRARY})

target_include_directories(solve_random PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(solve_random PRIVATE ${Boost_LIBRARIES} ${Z3_LIBRARY})

target_include_directories(sequence_generator PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(sequence_generator PRIVATE ${Boost_LIBRARIES} ${Z3_LIBRARY})
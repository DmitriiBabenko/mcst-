cmake_minimum_required(VERSION 3.20)

project(my_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost QUIET COMPONENTS program_options)
find_package(Z3 QUIET CONFIG)

add_executable(sequence_generator
    sequence_generator/sequence_generator.cpp
    sequence_generator/solveRandomApply.cpp
    sequence_generator/genSeq.cpp
    sequence_generator/generateComponents.cpp
    sequence_generator/Instruction.h
    common_add/fpa_to_float.cpp
    sequence_generator/DependencyAnalysis.cpp
)

target_link_libraries(sequence_generator PRIVATE 
    Boost::program_options
    z3::libz3
)
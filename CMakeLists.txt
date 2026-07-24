cmake_minimum_required(VERSION 3.20)
project(sequence_generator)

find_path(Z3_INCLUDE_DIR NAMES z3++.h PATHS /usr/include)
find_library(Z3_LIBRARY NAMES z3 PATHS /usr/lib/x86_64-linux-gnu)

if(NOT Z3_INCLUDE_DIR OR NOT Z3_LIBRARY)
    message(FATAL_ERROR "Z3 not found")
endif()

add_library(z3::libz3 UNKNOWN IMPORTED)

add_executable(sequence_generator
    sequence_generator/sequence_generator.cpp
    sequence_generator/solveRandomApply.cpp
    sequence_generator/genSeq.cpp
    sequence_generator/generateComponents.cpp
    sequence_generator/Instruction.h
    common_add/fpa_to_float.cpp
    sequence_generator/DependencyAnalysis.cpp
    sequence_generator/Jsondiskcache.h
    sequence_generator/ComponentSolution.h
    sequence_generator/Jsondiskcache.cpp
    sequence_generator/Node.h
    sequence_generator/Node.cpp
    sequence_generator/Graph.h
    sequence_generator/Graph.cpp
)

set_target_properties(z3::libz3 PROPERTIES
    IMPORTED_LOCATION "${Z3_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${Z3_INCLUDE_DIR}"
)

find_package(Boost REQUIRED COMPONENTS program_options json)

target_link_libraries(sequence_generator
    PRIVATE
    Boost::program_options
    Boost::json
    z3::libz3
)
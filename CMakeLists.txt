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
    common_add/fpa_to_float.cpp
    sequence_generator/Graph.h
    sequence_generator/Graph.cpp
    sequence_generator/Values.h
    sequence_generator/Values.cpp
    sequence_generator/Cache.h
    sequence_generator/Cache.cpp
    sequence_generator/topSort.h
    sequence_generator/topSort.cpp
    sequence_generator/assignRegisters.h
    sequence_generator/assignRegisters.cpp
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
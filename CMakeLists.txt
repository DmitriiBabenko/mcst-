cmake_minimum_required(VERSION 3.20)

project(my_app)

set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0144 NEW)
cmake_policy(SET CMP0167 NEW)

set(Boost_ROOT "C:/Boost")
find_package(Boost REQUIRED COMPONENTS program_options)

set(Z3_INCLUDE_DIR "C:/z3/src/api")
set(Z3_LIBRARY "C:/z3/build/Release/libz3.lib")

include_directories(${Z3_INCLUDE_DIR})

add_executable(sequence_generator
        sequence_generator.cpp
        solveRandomApply.cpp
        genSeq.cpp
        Instruction.h
)

target_include_directories(sequence_generator PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(sequence_generator PRIVATE ${Boost_LIBRARIES} ${Z3_LIBRARY})
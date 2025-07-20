cmake_minimum_required(VERSION 3.14)
project(MyProject VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(download_z3)
    set(Z3_VERSION "4.15.2")
    set(Z3_URL "https://github.com/Z3Prover/z3/releases/download/z3-${Z3_VERSION}/z3-${Z3_VERSION}-x64-win.zip")
    set(Z3_ZIP_FILE "${CMAKE_BINARY_DIR}/z3.zip")
    set(Z3_EXTRACT_DIR "${CMAKE_BINARY_DIR}/z3-extracted")
    set(Z3_DIR "${CMAKE_BINARY_DIR}/z3" PARENT_SCOPE)

    if(NOT EXISTS "${CMAKE_BINARY_DIR}/z3")
        message(STATUS "Downloading Z3 from ${Z3_URL}")

        file(DOWNLOAD
                "${Z3_URL}"
                "${Z3_ZIP_FILE}"
                SHOW_PROGRESS
                STATUS DOWNLOAD_STATUS
        )

        list(GET DOWNLOAD_STATUS 0 STATUS_CODE)
        if(NOT STATUS_CODE EQUAL 0)
            message(FATAL_ERROR "Failed to download Z3")
        endif()

        message(STATUS "Extracting Z3...")
        file(ARCHIVE_EXTRACT
                INPUT "${Z3_ZIP_FILE}"
                DESTINATION "${Z3_EXTRACT_DIR}"
        )

        file(GLOB Z3_EXTRACTED_CONTENT "${Z3_EXTRACT_DIR}/*")
        foreach(ITEM ${Z3_EXTRACTED_CONTENT})
            get_filename_component(ITEM_NAME ${ITEM} NAME)
            if(IS_DIRECTORY ${ITEM})
                file(RENAME ${ITEM} "${CMAKE_BINARY_DIR}/z3")
                break()
            endif()
        endforeach()

        file(REMOVE "${Z3_ZIP_FILE}")
        file(REMOVE_RECURSE "${Z3_EXTRACT_DIR}")
    endif()

    set(Z3_DIR "${CMAKE_BINARY_DIR}/z3" PARENT_SCOPE)
endfunction()

download_z3()

set(Z3_INCLUDE_DIR "${Z3_DIR}/include")
set(Z3_BIN_DIR "${Z3_DIR}/bin")

if(NOT EXISTS "${Z3_INCLUDE_DIR}/z3++.h")
    message(FATAL_ERROR "z3++.h not found at ${Z3_INCLUDE_DIR}")
endif()

find_library(Z3_LIBRARY
        NAMES z3 libz3
        PATHS ${Z3_BIN_DIR}
        NO_DEFAULT_PATH
)

if(NOT Z3_LIBRARY)
    message(FATAL_ERROR "Z3 library not found in ${Z3_BIN_DIR}")
endif()

message(STATUS "Z3 include directory: ${Z3_INCLUDE_DIR}")
message(STATUS "Z3 library: ${Z3_LIBRARY}")

add_executable(my_app main.cpp fpa_to_float.cpp pseudoOperations.cpp RandomFpa32.cpp)

target_include_directories(my_app PRIVATE ${Z3_INCLUDE_DIR})
target_link_libraries(my_app PRIVATE ${Z3_LIBRARY})

add_custom_command(TARGET my_app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${Z3_BIN_DIR}/libz3.dll"
        "$<TARGET_FILE_DIR:my_app>"
        COMMENT "Copying Z3 DLL"
)

if(MSVC)
    target_compile_options(my_app PRIVATE /W4)
else()
    target_compile_options(my_app PRIVATE -Wall -Wextra -pedantic)
endif()

message(STATUS "Build configuration complete")
message(STATUS "Z3 DLL will be copied to: $<TARGET_FILE_DIR:my_app>")
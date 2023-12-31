cmake_minimum_required(VERSION 3.16)

set(FLAGS -Wall) #-g
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER g++)

add_compile_options(${FLAGS})

project(SHELL_UXP1A VERSION 0.1 LANGUAGES CXX)

file(GLOB_RECURSE SRC ${CMAKE_SOURCE_DIR}/source/*.cpp)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(program main.cpp ${SRC})
add_executable(runTests tests/test_shell.cpp tests/test_program.cpp ${SRC})

target_include_directories(program PUBLIC BEFORE ${CMAKE_SOURCE_DIR}/include)

# target_include_directories(runTests PUBLIC BEFORE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(program shell_lib)
target_link_libraries(runTests gmock gtest gmock_main gtest_main pthread shell_lib)

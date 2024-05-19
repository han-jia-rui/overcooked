cmake_minimum_required(VERSION 3.14)
project(Overcooked)

find_package(Git)

set(CMAKE_CXX_STANDARD 20)
include_directories("include")
file(GLOB sources "source/*.cpp")
add_library(Overcooked ${sources})

add_custom_target(
    GitTraceAdd
    COMMAND "${GIT_EXECUTABLE}" add -A . --ignore-errors
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
add_custom_target(
    GitTraceCommit
    COMMAND
        "${GIT_EXECUTABLE}" commit -q --allow-empty --no-verify -m "compile"
        --author="tracer-ps4 <tracer-ps4@nju.edu.cn>"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
add_dependencies(GitTraceCommit GitTraceAdd) # Avoid data race
add_dependencies(Overcooked GitTraceCommit)
add_custom_command(
    TARGET Overcooked
    POST_BUILD
    COMMAND
        "${GIT_EXECUTABLE}" commit -q --allow-empty --no-verify -m
        "compile succeed" --author="tracer-ps4 <tracer-ps4@nju.edu.cn>"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

if(FOR_WIN)
    include(CMakeForceCompiler)
    set(TOOLCHAIN_PREFIX x86_64-w64-mingw32)

    # Force compilers for cross compilation
    cmake_force_c_compiler(${TOOLCHAIN_PREFIX}-gcc GNU)
    cmake_force_cxx_compiler(${TOOLCHAIN_PREFIX}-g++ GNU)

    add_executable(main-win ${sources})
else()
    # Your custom tests below
    add_executable(main ${sources})
endif()

cmake_minimum_required(VERSION 3.1)
project(sample_cmake_proj)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# The most commonly used rule is "One CMakeLists.txt per target".
add_subdirectory(lib_stairs)

add_executable(myExecutable
    main.cpp)


# include of both libA and libC is made public
# Hence, include path of them will be appended to INCLUDE_DIRECTORIES of current target myExecutable
# for the use in current target myExecutable
target_link_libraries(myExecutable
    PRIVATE libstairs.so
    )

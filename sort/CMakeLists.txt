cmake_minimum_required(VERSION 3.1)
project(project_name)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add_executable(merge_sort ./merge_sort.cc)
# add_executable(a.out ./quick_sort.cc)
# add_executable(a.out ./demo_one.cc)
add_executable(heapsort ./heap_sort.cc)


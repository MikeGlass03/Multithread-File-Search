cmake_minimum_required(VERSION 3.16)

project(MultithreadFileSearch)

find_package(Threads REQUIRED)

add_executable(
    MultithreadFileSearch
    src/main.cpp
    src/ThreadedFileSearch.cpp
)

target_include_directories(
    MultithreadFileSearch
    PRIVATE
    include
)

target_compile_features(
    MultithreadFileSearch
    PRIVATE cxx_std_17
)

target_link_libraries(
    MultithreadFileSearch
    PRIVATE Threads::Threads
)
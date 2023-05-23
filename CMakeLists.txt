cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


project(boost_graph_algorithms)

FIND_PACKAGE(Boost 1.83.0 COMPONENTS graph REQUIRED)

add_library(iterate_all_edges STATIC src/all_edges_iteration.cpp)
add_executable(boost_graph_measurements src/main.cpp)
target_link_libraries(boost_graph_measurements iterate_all_edges Boost::graph)


cmake_minimum_required(VERSION 3.1.0)


project(NetworkGraph CXX)

# INCLUDE NETWORK GRAPH HEADER FILES
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# NETWORK GRAPH SOURCE FILES
file(GLOB_RECURSE NETWORK_GRAPH_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# ADD NETWORK GRAPH TARGET
add_executable(NetworkGraph ${NETWORK_GRAPH_SOURCE})

# SET COMPILE FEATURES FOR NETWORK GRAPH
target_compile_features(NetworkGraph PRIVATE cxx_range_for)
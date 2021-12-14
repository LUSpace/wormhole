cmake_minimum_required(VERSION 3.19.6)
project(whSO)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-lnuma -lrt -lpthread -ldl -mrtm -msse4.1 -mavx2 -O3 -g -march=native")
 
set (PROJECT_LINK_LIBS libwh.so)
link_directories(./)
 
include_directories(./)

add_library(whWrapper SHARED worm_wrapper.cpp)
target_link_libraries(whWrapper ${PROJECT_LINK_LIBS})
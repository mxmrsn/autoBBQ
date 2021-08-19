cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(BBQTest)

# find_package(Torch REQUIRED)
# find_package (Python COMPONENTS Interpreter Development)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# linux setup
set(EIGEN3_INCLUDE_DIR /usr/local/include/eigen3)

include_directories(
	include
	${EIGEN3_INCLUDE_DIR}
)

add_executable(BBQTest src/main.cpp)

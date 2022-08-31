cmake_minimum_required(VERSION 3.0.0)
project(MotionDetection VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
include(CTest)
enable_testing()
find_package( OpenCV REQUIRED )
find_package(PkgConfig)

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(MotionDetection src/main.cpp)
target_link_libraries( MotionDetection ${OpenCV_LIBS} )
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)



cmake_minimum_required(VERSION 3.0.0)
project(MotionDetection VERSION 0.1.0)

include(CTest)
enable_testing()
find_package( libcamera REQUIRED )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} ${libcamera_INCLUDE_DIRS} )

add_executable(MotionDetection src/main.cpp)
target_link_libraries( MotionDetection ${OpenCV_LIBS} ${libcamera_LIBS} )
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)



cmake_minimum_required(VERSION 3.0.0)
project(MotionDetection VERSION 0.1.0)

include(CTest)
enable_testing()
find_package( OpenCV REQUIRED )
find_package(PkgConfig)

pkg_check_modules(LIBCAMERA REQUIRED IMPORTED_TARGET libcamera)
include_directories( ${OpenCV_INCLUDE_DIRS} ${LIBCAMERA_INCLUDE_DIRS} )

add_executable(MotionDetection src/main.cpp)
target_link_libraries( MotionDetection ${OpenCV_LIBS} PkgConfig::LIBCAMERA )
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)



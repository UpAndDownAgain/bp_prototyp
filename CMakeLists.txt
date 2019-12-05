cmake_minimum_required(VERSION 3.14)
project(bp_prototyp)

set(CMAKE_CXX_STANDARD 17)


find_package(OpenCV REQUIRED)

add_executable(bp_prototyp main.cpp classes/videoPlayer.cpp classes/videoPlayer.h classes/Detector.h classes/CascadeDetector.cpp classes/CascadeDetector.h classes/DetectorFactory.cpp classes/DetectorFactory.h classes/YoloDetector.cpp classes/YoloDetector.h)
target_link_libraries(bp_prototyp ${OpenCV_LIBS})
target_link_libraries(bp_prototyp stdc++fs)
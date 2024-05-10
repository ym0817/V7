cmake_minimum_required(VERSION 3.0.0)
project(yolov8_snpe210)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ubuntu_third_party/snpe1.68/include/zdl
                    ${CMAKE_CURRENT_SOURCE_DIR}/ubuntu_third_party/Opencv4.6/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/include   
                    ${CMAKE_CURRENT_SOURCE_DIR}/ubuntu_third_party/yaml_0.7.0/include
                     )

link_directories(
                 ${CMAKE_CURRENT_SOURCE_DIR}/ubuntu_third_party/snpe1.68/lib/x86_64-linux-clang
                 ${CMAKE_CURRENT_SOURCE_DIR}/ubuntu_third_party/Opencv4.6/lib
                 ${CMAKE_CURRENT_SOURCE_DIR}/ubuntu_third_party/yaml_0.7.0/lib
                )


add_executable(yolov8_snpe210
        src/yolo_tiny_640x640_85classes.cpp
        )


target_compile_features(yolov8_snpe210 PRIVATE cxx_std_17)
target_link_libraries(yolov8_snpe210 
        SNPE
        opencv_dnn
        opencv_highgui 
        opencv_imgproc 
        opencv_imgcodecs
        opencv_video
        opencv_core
        opencv_features2d
        opencv_videoio
        yaml-cpp.a
)


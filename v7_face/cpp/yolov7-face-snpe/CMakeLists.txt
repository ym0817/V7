cmake_minimum_required(VERSION 3.0.0)
project(yolov8_snpe1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/ubuntu_third_party/snpe1.68/include/zdl
                                        ${CMAKE_CURRENT_SOURCE_DIR}/ubuntu_third_party/Opencv4.7.0/include   
                                        ${CMAKE_CURRENT_SOURCE_DIR}/include   
)

link_directories( ${CMAKE_CURRENT_SOURCE_DIR}/ubuntu_third_party/snpe1.68/lib/x86_64-linux-clang   
                                 ${CMAKE_CURRENT_SOURCE_DIR}/ubuntu_third_party/Opencv4.7.0/lib   
)

add_executable(snpe_face
               src/yolov7face.cpp
               src/main.cpp)

add_executable(dnn_face
                dnn_main.cpp
        )
# target_compile_features(yolov8_snpe1 PRIVATE cxx_std_17)
target_link_libraries(snpe_face
        SNPE
        opencv_dnn
        opencv_highgui 
        opencv_imgproc 
        opencv_imgcodecs
        opencv_video
        opencv_core
        opencv_features2d
        opencv_videoio
)

####################

target_link_libraries(dnn_face
        opencv_dnn
        opencv_highgui 
        opencv_imgproc 
        opencv_imgcodecs
        opencv_video
        opencv_core
        opencv_features2d
        opencv_videoio
)
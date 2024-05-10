#设置cmake版本号
cmake_minimum_required(VERSION 3.5.0)

#设置工程名称
project(YOLOX_demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SNPE_DIR "/home/ymm/AI_INFERENCE/3rdparty/snpe1.68")
set (OPENCV_DIR "/home/ymm/AI_INFERENCE/3rdparty/Opencv4.8.0")

include_directories(${OPENCV_DIR}/include
                    ${SNPE_DIR}/include/zdl
                    )

link_directories(${SNPE_DIR}/lib/x86_64-linux-clang
                 ${OPENCV_DIR}/lib )


add_executable(YOLOX_demo yolo_tiny_640x640_85classes.cpp )

target_link_libraries(YOLOX_demo
                    SNPE
                    opencv_dnn
                    opencv_highgui
                    opencv_imgproc
                    opencv_imgcodecs
                    opencv_video
                    opencv_core
                    opencv_features2d
                    opencv_videoio )




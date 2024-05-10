#include <regex>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <ctime>
#include "yolov7face.h"


int main(int argc, char *argv[])
{
    float confThreshold = 0.4f;
    float iouThreshold = 0.4f;

	const std::string imagePath = "../images";
	const std::string save_imgs_path = "../images_result";
    std::string command = "mkdir -p " + save_imgs_path;
    system(command.c_str());

	const std::string modelPath = "../models/yolov7-lite-t_168.dlc";
//	const std::string classNamesPath = "../models/coco.names";

//    bool isGPU = false;
//    const std::string suffixName = "m";
//    const std::vector<std::string> classNames = utils::loadNames(classNamesPath);
    
//    if (classNames.empty())
//    {
//        std::cerr << "Error: Empty class names file." << std::endl;
//        return -1;
//    }
    if (!std::filesystem::exists(modelPath))
    {
        std::cerr << "Error: There is no model." << std::endl;
        return -1;
    }
    if (!std::filesystem::is_directory(imagePath))
    {
        std::cerr << "Error: There is no model." << std::endl;
        return -1;
    }

    std::cout << "Model from :::" << modelPath << std::endl;
    std::cout << "Images from :::" << imagePath << std::endl;
//    std::cout << "Resluts will be saved :::" << savePath << std::endl;

//    YOLOv8_face predictor{nullptr};
    std::shared_ptr<YOLOv_face> predictor(new YOLOv_face(modelPath, 0, confThreshold, iouThreshold ));
//    std::YOLOv8_face predictor = YOLOv8_face(modelPath, 0, confThreshold, iouThreshold );
    std::cout << "Model was initialized." << std::endl;

//    assert(classNames.size() == predictor.classNums);
//    std::regex pattern(".+\\.(jpg|jpeg|png|gif)$");
//    std::cout << "Start predicting..." << std::endl;

    clock_t startTime, endTime;
    startTime = clock();

    int picNums = 0;

    for (const auto &entry : std::filesystem::directory_iterator(imagePath))
    {

        picNums += 1;
        std::string Filename = entry.path().string();
        std::string baseName = std::filesystem::path(Filename).filename().string();
        std::cout << Filename << " predicting..." << std::endl;
        clock_t st_infer = clock();;
        cv::Mat image = cv::imread(Filename);
        std::vector<Object> results;
	    predictor->detect(image, results);
        clock_t en_infer = clock();;
        std::cout << Filename << "   detection_num  ..." << results.size() << std::endl;
        std::cout << "per image inference time cost is:   " << (double)(en_infer - st_infer) / CLOCKS_PER_SEC * 1000 << "  ms" << std::endl;
        for(int i = 0; i < results.size(); i ++)
	    {
            float x1 = results[i].x1;
            float y1 = results[i].y1;
            float x2 = results[i].x2;
            float y2 = results[i].y2;
            cv::Rect2f box(x1, y1, x2 - x1, y2 - y1);
            cv::rectangle(image, box, cv::Scalar(0, 255, 0), 2, 8, 0);
            for(int j = 0; j < 5; j ++)
            {
                cv::Point2f pt;
                pt.x = results[i].landmark[j].x;
                pt.y = results[i].landmark[j].y;
                if(results[i].landmark[j].prob > 0.5){
                    cv::circle(image, pt, 1, cv::Scalar(0,255,0), 2, 8, 0);
                }
            }
		}
		// cv::imwrite("result.jpg", image);
       cv::imshow("Face", image);
	    cv::waitKey(0);

//            utils::visualizeDetection(image, result, classNames);
//            std::string::size_type iPos = Filename.find_last_of('/') + 1;
//            std::string filename = Filename.substr(iPos, Filename.length() - iPos);
//            std::string save_img_path = save_imgs_path + '/' + filename;
//            cv::imwrite(save_img_path, image);

//            std::cout << outputFilename << " Saved !!!" << std::endl;

    }
    endTime = clock();
    std::cout << "The total run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "seconds" << std::endl;
    std::cout << "The average run time is: " << (double)(endTime - startTime) / picNums / CLOCKS_PER_SEC << "seconds" << std::endl;

    std::cout << "##########DONE################" << std::endl;

    return 0;
}

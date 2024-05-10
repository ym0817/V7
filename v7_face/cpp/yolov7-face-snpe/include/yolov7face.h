#pragma once
#include <opencv2/opencv.hpp>
#include <utility>

#include "DlContainer/IDlContainer.hpp"
#include "DlSystem/DlEnums.hpp"
#include "DlSystem/DlError.hpp"
#include "DlSystem/ITensorFactory.hpp"
#include "DlSystem/RuntimeList.hpp"
#include "SNPE/SNPEBuilder.hpp"
#include "SNPE/SNPEFactory.hpp"
#include "SNPE/SNPE.hpp"

#define YOLOFACE_INPUT_WIDTH  640
#define YOLOFACE_INPUT_HEIGHT 640
#define NUM_OUTPUTS 3
#define NUM_KEYPOINTS 5

struct Point{
    float x;
	float y;
	float prob;
};

typedef struct Object
{
	float x1;
	float y1;
	float x2;
	float y2;
	float score;
	Point landmark[NUM_KEYPOINTS];
} Object;


class YOLOv_face
{
public:
	YOLOv_face(std::string modelpath, int platdorm, float confThreshold, float nmsThreshold);
	void detect(cv::Mat &image, std::vector<Object>& objects, float prob_threshold = 0.5f, float nms_threshold = 0.45f);

private:
    void buildtensor(cv::Mat &input_image);
    std::vector<float>LetterboxImage(const cv::Mat& src, cv::Mat& dst, const cv::Size& out_size);
    void decode(zdl::DlSystem::TensorMap &output_tensors, std::string &out_name, std::vector<int> anchor, std::vector<Object> &prebox, float threshold, int stride);

//	cv::Mat resize_image(cv::Mat srcimg, int *newh, int *neww, int *padh, int *padw);
//	std::vector<cv::Rect> postprocessing(const cv::Size &resizedImageShape,
//                                             const cv::Size &originalImageShape,
//                                             zdl::DlSystem::TensorMap &output_tensors);
//	const bool keep_ratio = true;
//	const int inpWidth = 640;
//	const int inpHeight = 640;
	float confThreshold;
	float nmsThreshold;
	std::vector<int> anchor0 = {4,5,  6,8,  10,12};
	std::vector<int> anchor1 = {15,19,  23,30,  39,52};
	std::vector<int> anchor2 = {72,97,  123,164,  209,297};
//	const int num_class = 1;  ///只有人脸这一个类别
//	const int reg_max = 16;
//	Net net;
	std::unique_ptr<zdl::SNPE::SNPE> _engine;
    std::unique_ptr<zdl::DlContainer::IDlContainer> _container;
    zdl::DlSystem::RuntimeList _runtime_list;
    std::unique_ptr<zdl::DlSystem::ITensor> _input_tensor;
    zdl::DlSystem::TensorMap _output_tensor_map;

};






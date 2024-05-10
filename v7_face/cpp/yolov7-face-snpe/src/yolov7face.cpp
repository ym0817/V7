#include "yolov7face.h"

YOLOv_face::YOLOv_face(std::string modelpath, int platdorm, float confThreshold, float nmsThreshold)
{

    this->confThreshold = confThreshold;
	this->nmsThreshold = nmsThreshold;

    auto Version = zdl::SNPE::SNPEFactory::getLibraryVersion();
    std::cout << "[SNPE][setRuntime] SNPE Version: " << Version.asString().c_str() << std::endl;
    zdl::DlSystem::Runtime_t runtime_t;     // 设置推理硬件
    switch (platdorm) {
    case 0:
        runtime_t =  zdl::DlSystem::Runtime_t::CPU;
        break;
    case 1:
        runtime_t = zdl::DlSystem::Runtime_t::GPU;
        break;
    case 2:
        runtime_t = zdl::DlSystem::Runtime_t::DSP;
        break;
    case 3:
        runtime_t = zdl::DlSystem::Runtime_t::AIP_FIXED8_TF;
        break;
    default:
        runtime_t = zdl::DlSystem::Runtime_t::CPU;
        break;
    }
    const char* runtime_string = zdl::DlSystem::RuntimeList::runtimeToString(runtime_t);
    if (!zdl::SNPE::SNPEFactory::isRuntimeAvailable(runtime_t) )
    {
       std:: cout << "SNPE runtime " <<  runtime_string << " not support" <<std:: endl;
    } else {
        std::cout << "Current SNPE runtime Support :   " <<  runtime_string  << std::endl;
    }
    _runtime_list.add(runtime_t);

    _container = zdl::DlContainer::IDlContainer::open(modelpath);
    if (_container == nullptr) {
        std::cout << "load model error : " << zdl::DlSystem::getLastErrorString() << std::endl;
    }
    zdl::DlSystem::StringList outputs;
    outputs.append("/model.22/Concat");    //  1, 80,80,80
    outputs.append("/model.22/Concat_1");       //  1, 40, 40, 80
    outputs.append("/model.22/Concat_2");       //  1, 40, 40, 80

    zdl::SNPE::SNPEBuilder snpe_builder(_container.get());
    zdl::DlSystem::UDLBundle udlBundle;
    zdl::DlSystem::PlatformConfig platformConfig;
    zdl::DlSystem::PerformanceProfile_t profile = zdl::DlSystem::PerformanceProfile_t::HIGH_PERFORMANCE;
    _engine = snpe_builder
	    .setOutputLayers(outputs)
	            // .setRuntimeProcessor(runtime_)
	    .setRuntimeProcessorOrder(_runtime_list)
//	    .setUseUserSuppliedBuffers(false)
//	    .setPerformanceProfile(profile)
//	    .setUdlBundle(udlBundle)
	    .build();

    if (_engine == nullptr) {
        std::cout << "build engine error : " << zdl::DlSystem::getLastErrorString() << std::endl;
    }

    std::cout << "init success..." << std::endl;

}

std::vector<float> YOLOv_face::LetterboxImage(const cv::Mat& src, cv::Mat& dst, const cv::Size& out_size)
{
	auto in_h = static_cast<float>(src.rows);
	auto in_w = static_cast<float>(src.cols);
	float out_h = out_size.height;
	float out_w = out_size.width;

	float scale = std::min(out_w / in_w, out_h / in_h);

	int mid_h = static_cast<int>(in_h * scale);
	int mid_w = static_cast<int>(in_w * scale);

	cv::resize(src, dst, cv::Size(mid_w, mid_h), 0, 0, cv::INTER_NEAREST);

	int top = (static_cast<int>(out_h) - mid_h) / 2;
	int down = (static_cast<int>(out_h)- mid_h + 1) / 2;
	int left = (static_cast<int>(out_w)- mid_w) / 2;
	int right = (static_cast<int>(out_w)- mid_w + 1) / 2;

	cv::copyMakeBorder(dst, dst, top, down, left, right, cv::BORDER_CONSTANT, cv::Scalar(114, 114, 114));

	std::vector<float> pad_info{static_cast<float>(left), static_cast<float>(top), scale};
	return pad_info;
}



void YOLOv_face::buildtensor(cv::Mat &input_image)
{
    unsigned long int in_size = 1;
    const zdl::DlSystem::TensorShape i_tensor_shape = _engine->getInputDimensions();
    const zdl::DlSystem::Dimension *shapes = i_tensor_shape.getDimensions();
    size_t img_size = input_image.channels() * input_image.cols * input_image.rows;
    for(int i=1; i<i_tensor_shape.rank(); i++) {
      in_size *= shapes[i];
    }

    _input_tensor = zdl::SNPE::SNPEFactory::getTensorFactory().createTensor(_engine->getInputDimensions());
    zdl::DlSystem::ITensor *tensor_ptr = _input_tensor.get();
    if(tensor_ptr == nullptr) {
        std::cout << "Could not create SNPE input tensor" << std::endl;
    }
    float *tensor_ptr_fl = reinterpret_cast<float *>(&(*_input_tensor -> begin()));
    for(auto i = 0; i < img_size; i++){
        tensor_ptr_fl[i] = static_cast<float>(input_image.data[i]);
        tensor_ptr_fl[i] = tensor_ptr_fl[i] / 255.0;
    }

}



// ----------------------------   NMS  --------------------------
void nms(std::vector<Object> &input_boxes, float NMS_THRESH)
{
	std::vector<float>vArea(input_boxes.size());
	for (int i = 0; i < int(input_boxes.size()); ++i)
	{
		vArea[i] = (input_boxes.at(i).x2 - input_boxes.at(i).x1 + 1)
			* (input_boxes.at(i).y2 - input_boxes.at(i).y1 + 1);
	}
	for (int i = 0; i < int(input_boxes.size()); ++i)
	{
		for (int j = i + 1; j < int(input_boxes.size());)
		{
			float xx1 = std::max(input_boxes[i].x1, input_boxes[j].x1);
			float yy1 = std::max(input_boxes[i].y1, input_boxes[j].y1);
			float xx2 = std::min(input_boxes[i].x2, input_boxes[j].x2);
			float yy2 = std::min(input_boxes[i].y2, input_boxes[j].y2);
			float w = std::max(float(0), xx2 - xx1 + 1);
			float h = std::max(float(0), yy2 - yy1 + 1);
			float inter = w * h;
			float ovr = inter / (vArea[i] + vArea[j] - inter);
			if (ovr >= NMS_THRESH)
			{
				input_boxes.erase(input_boxes.begin() + j);
				vArea.erase(vArea.begin() + j);
			}
			else
			{
				j++;
			}
		}
	}
}

//  ---------------------------------------------------------------

bool cmp(Object b1, Object b2) 
{
    return b1.score > b2.score;
}


static inline float sigmoid(float x){
	return static_cast<float>(1.f / (1.f + exp(-x)));
}


void YOLOv_face::decode(zdl::DlSystem::TensorMap &output_tensors,std::string &out_name, std::vector<int> anchor, std::vector<Object> &prebox, float threshold, int stride)
{

    zdl::DlSystem::ITensor *outTensor = output_tensors.getTensor(out_name.c_str());  // 1  80  80  16
//    std::cout <<  " dddddddddddd" << std::endl;
    float *ptr = reinterpret_cast<float *>(&(*outTensor->begin()));
//    std::cout <<  " ################" << std::endl;
    zdl::DlSystem::TensorShape outTensor_shape= outTensor->getShape();
//    std::cout <<  " eeeeeeee" << std::endl;

    int fea_h = outTensor_shape[2];
	int fea_w = outTensor_shape[1];
	int spacial_size = fea_w*fea_h;
	int channels = NUM_KEYPOINTS * 3 + 6;
//	float *ptr = (float*)(outTensor_value.data);
	for(int c = 0; c < anchor.size() / 2; c++)
	{
		float anchor_w = float(anchor[c * 2 + 0]);
		float anchor_h = float(anchor[c * 2 + 1]);
		float *ptr_x = ptr + spacial_size * (c * channels + 0);
		float *ptr_y = ptr + spacial_size * (c * channels + 1);
		float *ptr_w = ptr + spacial_size * (c * channels + 2);
		float *ptr_h = ptr + spacial_size * (c * channels + 3);
		float *ptr_s = ptr + spacial_size * (c * channels + 4);
		float *ptr_c = ptr + spacial_size * (c * channels + 5);

//        std::cout <<  " ptr_x," << ptr_x << "," << ptr_y << std::endl;
//                       max_conf = conf;
//		float *ptr_x = ptr[spacial_size * (c * channels + 0)] ;
//		float *ptr_y = ptr [spacial_size * (c * channels + 1)] ;
//		float *ptr_w = ptr [spacial_size * (c * channels + 2)] ;
//		float *ptr_h = ptr [spacial_size * (c * channels + 3)] ;
//		float *ptr_s = ptr [spacial_size * (c * channels + 4)] ;
//		float *ptr_c = ptr [spacial_size * (c * channels + 5)] ;

		for(int i = 0; i < fea_h; i++)
		{
			for(int j = 0; j < fea_w; j++)
			{
				int index = i * fea_w + j;
//				float confidence = ptr_s[index] * ptr_c[index];
//				std::cout <<  " confidence   " << confidence << "  " << std::endl;

				float confidence = sigmoid(ptr_s[index]) * sigmoid(ptr_c[index]);
				if(confidence > threshold)
				{
				    // std::cout <<  " confidence   " << confidence << "  " << std::endl;
					Object temp_box;
					float dx = sigmoid(ptr_x[index]);
					float dy = sigmoid(ptr_y[index]);
					float dw = sigmoid(ptr_w[index]);
					float dh = sigmoid(ptr_h[index]);

					float pb_cx = (dx * 2.f - 0.5f + j) * stride;
					float pb_cy = (dy * 2.f - 0.5f + i) * stride;

					float pb_w = pow(dw * 2.f, 2) * anchor_w;
					float pb_h = pow(dh * 2.f, 2) * anchor_h;

					temp_box.score = confidence;
					temp_box.x1 = pb_cx - pb_w * 0.5f;
					temp_box.y1 = pb_cy - pb_h * 0.5f;
					temp_box.x2 = pb_cx + pb_w * 0.5f;
					temp_box.y2 = pb_cy + pb_h * 0.5f;
//                    std::cout <<  " box   " << temp_box.x1 << "  " << temp_box.y1 <<std::endl;
					for(int l = 0; l < NUM_KEYPOINTS; l ++)
					{
						temp_box.landmark[l].x = (ptr[(spacial_size * (c * channels + l * 3 + 6)) + index] * 2 - 0.5 + j) * stride;
						temp_box.landmark[l].y = (ptr[(spacial_size * (c * channels + l * 3 + 7)) + index] * 2 - 0.5 + i) * stride;
						temp_box.landmark[l].prob = sigmoid(ptr[spacial_size * (c * channels + l * 3 + 8) + index]);
					}
					prebox.push_back(temp_box);
				}
			}
		}
	}


}


void YOLOv_face::detect(cv::Mat &image, std::vector<Object>& objects, float prob_threshold, float nms_threshold)
{
    cv::Mat srcimg = image.clone();
    cv::Mat dst;
    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    std::vector<float> infos = LetterboxImage(image, dst, cv::Size(YOLOFACE_INPUT_WIDTH, YOLOFACE_INPUT_HEIGHT));
//    cv::imshow("Face", dst);
//	    cv::waitKey(0);
    buildtensor(dst);

    bool ret = _engine->execute(_input_tensor.get(), _output_tensor_map);
    if (!ret) {
        std::cerr << "engine inference error : " << zdl::DlSystem::getLastErrorString() << std::endl;
    } else {
        std::cout << "engine inference success..." << std::endl;
    }
    zdl::DlSystem::StringList tensorNames = _output_tensor_map.getTensorNames();
    for(auto& name : tensorNames) {
//    std::cout << "Output tensor name: " << name << std::endl;
    auto tensorPtr = _output_tensor_map.getTensor(name);
//    output_size += tensorPtr->getSize();
//    for(auto it = tensorPtr->cbegin(); it != tensorPtr->cend(); it++) {
//      result_temp.push_back(*it);
//    }
  }


    for(size_t i=0; i<tensorNames.size(); i++) {
        zdl::DlSystem::ITensor *outTensor_i = _output_tensor_map.getTensor(tensorNames.at(i));
        zdl::DlSystem::TensorShape shape_i = outTensor_i->getShape();
        // out_tensors.emplace_back(shape_i[2], shape_i[1]);
         std::cout << "tensor_dim"<< ": " << i << "   "  <<shape_i[1] << "  " <<  shape_i[2] << "   " << shape_i[3]  << "    tensor_name   :    " << tensorNames.at(i)  << std::endl;
    }
//    std::string out_0 = "/model.22/Concat";  // 1  80  80  16
//    std::string out_1 = "/model.22/Concat_1";  // 1  40  40  16
//    std::string out_2 = "/model.22/Concat_2";  // 1  20  20  16
    std::string out_0 ="stride_8";  // 1  80  80  16
    std::string out_1 = "stride_16";  // 1  40  40  16
    std::string out_2 = "stride_32";  // 1  20  20  16
    objects.clear();
    decode(_output_tensor_map,out_0, anchor0, objects, prob_threshold, 8);
    decode(_output_tensor_map,out_1, anchor1, objects, prob_threshold, 16);
    decode(_output_tensor_map,out_2, anchor2, objects, prob_threshold, 32);

    std::sort(objects.begin(), objects.end(), cmp);
	nms(objects, nms_threshold);
    for(int i = 0; i < objects.size(); i ++)
	{
		objects[i].x1 = (objects[i].x1 - infos[0]) / infos[2];
		objects[i].y1 = (objects[i].y1 - infos[1]) / infos[2];
		objects[i].x2 = (objects[i].x2 - infos[0]) / infos[2];
		objects[i].y2 = (objects[i].y2 - infos[1]) / infos[2];
		for(int j = 0; j < NUM_KEYPOINTS; j ++)
		{
			objects[i].landmark[j].x = (objects[i].landmark[j].x - infos[0]) / infos[2];
			objects[i].landmark[j].y = (objects[i].landmark[j].y - infos[1]) / infos[2];
		}
	}


}






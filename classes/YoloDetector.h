//
// Created by nrg on 12/2/19.
//

#ifndef BP_PROTOTYP_YOLODETECTOR_H
#define BP_PROTOTYP_YOLODETECTOR_H


#include "Detector.h"
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
//TODO
class YoloDetector : Detector {
private:
    cv::dnn::Net net;

public:
    YoloDetector(std::string &cfg, std::string &weights, std::string &classes);
};


#endif //BP_PROTOTYP_YOLODETECTOR_H

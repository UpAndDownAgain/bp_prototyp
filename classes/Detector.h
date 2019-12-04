//
// Created by nrg on 12/2/19.
//

#ifndef BP_PROTOTYP_DETECTOR_H
#define BP_PROTOTYP_DETECTOR_H


#include <vector>
#include <opencv2/opencv.hpp>
#include <exception>
#include <memory>

class Detector {
public:
    virtual std::vector<cv::Rect> detect(cv::Mat &frame) = 0;
};


#endif //BP_PROTOTYP_DETECTOR_H

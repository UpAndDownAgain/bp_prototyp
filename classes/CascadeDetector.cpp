//
// Created by nrg on 12/2/19.
//

#include "CascadeDetector.h"

cv::Mat CascadeDetector::preprocess(cv::Mat &frame) {
    cv::Mat grayscale;
    cv::cvtColor(frame, grayscale, cv::COLOR_BayerBG2GRAY);
    cv::equalizeHist(grayscale, grayscale);
    return grayscale;
}

CascadeDetector::CascadeDetector(const std::string &cascadeName) {
    if(!cascade.load(cascadeName)){
        throw std::invalid_argument("Error opening cascade");
    }
}

std::vector<cv::Rect> CascadeDetector::detect(cv::Mat &frame) {
    if(cascade.empty()){
        throw std::invalid_argument("cascade not loaded");
    }

    cv::Mat image = this->preprocess(frame);
    std::vector<cv::Rect> detects;
    cascade.detectMultiScale(frame, detects);
    return detects;
}

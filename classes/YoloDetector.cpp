//
// Created by nrg on 12/2/19.
//

#include "YoloDetector.h"

YoloDetector::YoloDetector(std::string &cfg, std::string &weights, std::string &classes) {
    this->net = cv::dnn::readNetFromDarknet(cfg, weights);

}

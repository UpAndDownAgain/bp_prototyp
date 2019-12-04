//
// Created by nrg on 12/2/19.
//

#ifndef BP_PROTOTYP_CASCADEDETECTOR_H
#define BP_PROTOTYP_CASCADEDETECTOR_H


#include "Detector.h"


class CascadeDetector : public Detector {
private:
    cv::CascadeClassifier cascade;

    cv::Mat preprocess(cv::Mat &frame);
public:
    explicit CascadeDetector(const std::string &cascadeName);
    std::vector<cv::Rect> detect(cv::Mat &frame) override;
};


#endif //BP_PROTOTYP_CASCADEDETECTOR_H

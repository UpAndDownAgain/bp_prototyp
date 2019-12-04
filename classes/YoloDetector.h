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
class YoloDetector : public Detector {
private:

    double threshold = 0.0;
    double nmsThreshold = 0.0;
    cv::dnn::Net net;
    void postprocess(cv::Mat &frame, std::vector<cv::Mat> &vect);
    void drawPrediction(float &d, int x, int y, int i, int i1, cv::Mat &mat);

public:
    explicit YoloDetector(std::string &cfg,const std::string &weights);
    void detectAndDisplay(cv::Mat &frame) override;

};


#endif //BP_PROTOTYP_YOLODETECTOR_H

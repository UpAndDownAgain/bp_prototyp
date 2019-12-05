//
// Created by nrg on 12/2/19.
//

#ifndef BP_PROTOTYP_YOLODETECTOR_H
#define BP_PROTOTYP_YOLODETECTOR_H


#include "Detector.h"
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/cvstd.hpp>
#include <opencv2/core.hpp>
//TODO
class YoloDetector : public Detector {
private:
    double threshold = 0.5;
    double nmsThreshold = 0.4;
    cv::dnn::Net net;
    std::vector<cv::String> outNames;
    std::vector<cv::Point> barpath;

    void postprocess(cv::Mat &frame, std::vector<cv::Mat> &vect);
    void drawPred(int classId, float confidence, int left, int top, int right, int bottom, cv::Mat &frame);
    static void keepClosestDetection(std::vector<cv::Rect> &boxes, std::vector<int> &indices);

public:
    explicit YoloDetector(std::string &cfg,const std::string &weights);
    void detectAndDisplay(cv::Mat &frame) override;

};


#endif //BP_PROTOTYP_YOLODETECTOR_H

//
// Created by nrg on 12/2/19.
//

#include "YoloDetector.h"

YoloDetector::YoloDetector(std::string &cfg,const std::string &weights) {
    this->net = cv::dnn::readNetFromDarknet(cfg, weights);
    this->net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    this->net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
}

void YoloDetector::detectAndDisplay(cv::Mat &frame) {
    cv::Mat blob;
    std::vector<cv::Mat> outputs;

    cv::dnn::blobFromImage(frame, blob, 1/255,
            cvSize(480,480),
            cv::Scalar(0,0,0),
            true, false);

    net.setInput(blob);
    net.forward(outputs, "plate");

    this->postprocess(frame, outputs);
}

void YoloDetector::postprocess(cv::Mat &frame, std::vector<cv::Mat> &vect) {
    std::vector<cv::Rect> boxes;
    std::vector<float> confidences;

    for(auto &i : vect){

        auto* data = (float*) i.data;

        for(size_t j = 0; j < i.rows; ++j){
            double confidence;
            cv::Mat scores = i.row(j).colRange(5, i.cols);
            cv::minMaxLoc(scores, 0, &confidence, 0);

            if(confidence > this->threshold){
                int centerX = (int)(data[0] * frame.cols);
                int centerY = (int)(data[0] * frame.rows);
                int width = (int)(data[0] * frame.cols);
                int height = (int)(data[0] * frame.rows);

                int left = centerX - width / 2;
                int top = centerY - height /2;

                confidences.emplace_back(confidence);
                boxes.emplace_back(cv::Rect(left, top, width, height));
            }
        }
    }
    std::vector<int> indexVect;
    cv::dnn::NMSBoxes(boxes, confidences, this->threshold, this->nmsThreshold, indexVect);

    for(int idx : indexVect){
        cv::Rect box = boxes[idx];
        drawPrediction(confidences[idx], box.x, box.y, box.x + box.width, box.y + box.height, frame);
    }
}

void YoloDetector::drawPrediction(float &confidence, int left, int top, int right, int bottom, cv::Mat &frame) {
    cv::rectangle(frame, cv::Point(left, top),
            cv::Point(right, bottom),
            cv::Scalar(0,255,0), 3);
}


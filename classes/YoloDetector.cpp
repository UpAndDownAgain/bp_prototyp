//
// Created by nrg on 12/2/19.
//

#include "YoloDetector.h"

YoloDetector::YoloDetector(std::string &cfg,const std::string &weights) {
    net = cv::dnn::readNetFromDarknet(cfg, weights);
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
    outNames = net.getUnconnectedOutLayersNames();
}

void YoloDetector::detectAndDisplay(cv::Mat &frame) {
    cv::Mat blob;
    std::vector<cv::Mat> outputs;

    cv::dnn::blobFromImage(frame, blob, 1/255.0,
            cv::Size(480,480),
            cv::Scalar(0,0,0),
            true, false), CV_8U;

    net.setInput(blob);
    net.forward(outputs, outNames);

    std::cout << outputs.size() << " detect " <<  std::endl;
    postprocess(frame, outputs);
}

void YoloDetector::postprocess(cv::Mat &frame, std::vector<cv::Mat> &vect) {
    std::vector<cv::Rect> boxes;
    std::vector<float> confidences;
    std::vector<int> outLayers = net.getUnconnectedOutLayers();
    std::vector<int> classIds;
    std::string outLayerType = net.getLayer(outLayers[0])->type;

    if(outLayerType == "DetectionOutput"){
        CV_Assert(!vect.empty());
        for(auto & i : vect){
            auto *data = (float*) i.data;
            for(size_t j = 0; j < i.total(); ++j){
                float confidence = data[j+2];
                if(confidence > threshold){
                    int left   = (int)data[j + 3];
                    int top    = (int)data[j + 4];
                    int right  = (int)data[j + 5];
                    int bottom = (int)data[j + 6];
                    int width  = right - left + 1;
                    int height = bottom - top + 1;
                    if (width <= 2 || height <= 2){
                        left   = (int)(data[j + 3] * frame.cols);
                        top    = (int)(data[j + 4] * frame.rows);
                        right  = (int)(data[j + 5] * frame.cols);
                        bottom = (int)(data[j + 6] * frame.rows);
                        width  = right - left + 1;
                        height = bottom - top + 1;
                    }
                    classIds.push_back((int)(data[j+1])-1);
                    boxes.emplace_back(left,top, width, height);
                    confidences.push_back(confidence);
                }
            }
        }
    }
    else if(outLayerType == "Region"){
        for(auto & i : vect){
            auto* data = (float*) i.data;

            for(size_t j = 0; j < i.rows; ++j, data += i.cols){
                cv::Mat scores = i.row(j).colRange(5, i.cols);
                cv::Point classIdPoint;
                double confidence;
                cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);

                if(confidence > threshold){
                    int centerX = (int)(data[0] * frame.cols);
                    int centerY = (int)(data[1] * frame.rows);
                    int width = (int)(data[2] * frame.cols);
                    int height = (int)(data[3] * frame.rows);
                    int left = centerX - width / 2;
                    int top = centerY - height / 2;

                    classIds.push_back(classIdPoint.x);
                    confidences.push_back((float)confidence);
                    boxes.emplace_back(left, top, width, height);
                }
            }
        }
    }
    else{
       throw std::runtime_error("unknown layer: " + outLayerType);
    }
    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences, threshold, nmsThreshold, indices);

    for(int idx : indices){
        cv::Rect box = boxes[idx];
        barpath.emplace_back(cv::Point(box.x + (box.width / 2), box.y + (box.height / 2)));
        drawPred(classIds[idx], confidences[idx],
                 box.x, box.y, box.x + box.width, box.y + box.height, frame);
    }
}

void YoloDetector::drawPred(int classId, float confidence, int left, int top, int right, int bottom, cv::Mat &frame) {
    std::string label = cv::format("%.2f", confidence);
    int baseline;

    cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseline);

    top = cv::max(top, labelSize.height);

    for(auto &i : barpath){
        cv::line(frame, i, i, cv::Scalar(0,0,255), 4);
    }
    cv::rectangle(frame, cv::Point(left, top), cv::Point(right,bottom), cv::Scalar(0,255,0), 3);

    cv::rectangle(frame, cv::Point(left, top - labelSize.height),
            cv::Point(left + labelSize.width,top + baseline),
            cv::Scalar::all(255), cv::FILLED);

    cv::putText(frame, label, cv::Point(left, top), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar());
}


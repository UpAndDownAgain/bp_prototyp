//
// Created by nrg on 10/7/19.
//

#ifndef BP_PROTOTYP_VIDEOPLAYER_H
#define BP_PROTOTYP_VIDEOPLAYER_H


#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <string>
#include <iostream>
#include <queue>
#include "DetectorFactory.h"

class VideoPlayer {
public:
    VideoPlayer(const std::string &videoFile, const std::string &detectorFile);
    void playVideo(const std::string &windowName );
    void loadFrames();
    void useDetector();

private:
    std::unique_ptr<Detector> detector;
    cv::VideoCapture videoCapture;

    std::vector<cv::Mat> processedFrames;
    std::queue<cv::Mat> framesToProcess;

};


#endif //BP_PROTOTYP_VIDEOPLAYER_H

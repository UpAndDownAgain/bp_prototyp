//
// Created by nrg on 10/7/19.
//

#ifndef BP_PROTOTYP_VIDEOPLAYER_H
#define BP_PROTOTYP_VIDEOPLAYER_H


#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/core.hpp>

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
    void save(std::string &outName);
    ~VideoPlayer();
private:
    std::unique_ptr<Detector> detector;
    cv::VideoCapture videoCapture;

    double fps, frame_width, frame_height;

    std::vector<cv::Mat> processedFrames;
    std::queue<cv::Mat> framesToProcess;

};


#endif //BP_PROTOTYP_VIDEOPLAYER_H

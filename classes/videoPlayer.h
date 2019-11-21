//
// Created by nrg on 10/7/19.
//

#ifndef BP_PROTOTYP_VIDEOPLAYER_H
#define BP_PROTOTYP_VIDEOPLAYER_H


#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <iostream>
#include <thread>
#include <queue>

class videoPlayer {
public:
    void playVideo(const std::string &windowName );
    bool openVideoFile(const std::string &fileName);
    bool openCascade(const std::string &cascadeName);
    void loadFrames();
    void detectAndDisplay();

private:
    cv::CascadeClassifier haarcascade;
    cv::VideoCapture videoCapture;
    std::vector<std::pair<int, cv::Rect>> object_vect;
    std::vector<cv::Mat> processedFrames;
    std::queue<cv::Mat> framesToProcess;

};


#endif //BP_PROTOTYP_VIDEOPLAYER_H

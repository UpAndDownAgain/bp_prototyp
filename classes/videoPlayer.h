//
// Created by nrg on 10/7/19.
//

#ifndef BP_PROTOTYP_VIDEOPLAYER_H
#define BP_PROTOTYP_VIDEOPLAYER_H


#include <highgui.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <iostream>

class videoPlayer {
public:
    videoPlayer();
    videoPlayer(const std::string &fileName);

    void playVideo(const std::string &windowName );
    bool openVideoFile(const std::string &fileName);
    bool openCascade(const std::string &cascadeName);
    void detect();

private:
    cv::CascadeClassifier haarcascade;
    cv::VideoCapture videoCapture;
    cv::Mat frame;
    bool play;
    std::vector<std::pair<int, cv::Rect>> object_vect;

    void display(cv::Mat &frame, int frame_number);
    void detectAndDisplay(cv::Mat &frame);
};


#endif //BP_PROTOTYP_VIDEOPLAYER_H

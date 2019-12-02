//
// Created by nrg on 10/7/19.
//

#include "videoPlayer.h"

/*
 * prehrani videa ze zpracovanych framu a vykresleni do okna
 */
void VideoPlayer::playVideo(const std::string &windowName) {
    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    cv::resizeWindow(windowName, 600, 600);

    while(true){
        for(auto &frame : processedFrames){
            cv::imshow(windowName, frame);
            int c = cv::waitKey(24);
            if(c == 'q'){
                return;
            }
        }
    }

}

/*
 * nahrani framu do fronty pro zpracovani
 */
void VideoPlayer::loadFrames() {
    cv::Mat frame;
    std::cout << "loading frames" << std::endl;
    while (true) {

        videoCapture >> frame;
        if (frame.empty())
            break;
        else
            framesToProcess.push(frame.clone());
    }
    std::cout << "frames loaded" << std::endl;
}

VideoPlayer::VideoPlayer(const std::string &videoFile, const std::string &detectorFile) {
    try{
    detector = detectorFactory.createDetector(detectorFile);
    videoCapture.open(videoFile);
    }catch(std::exception &e){
        throw e;
    }
    if(!videoCapture.isOpened()){
        throw std::invalid_argument("Failed to open video file");
    }
}
/**
 * nacte framy z fronty preda je detectoru k detekci a vysledek zakresli do origin
 * framu, ktery ulozi pro prehrani
 */
void VideoPlayer::detectAndDisplay() {
    int i=0;
    while(!framesToProcess.empty()){
        std::cout << "detecting frame " << i++ << std::endl;
        cv::Mat frame = framesToProcess.front();
        framesToProcess.pop();
        std::vector<cv::Rect> detects = detector->detect(frame);
        for(const auto &obj : detects){
            cv::rectangle(frame, obj, cv::Scalar(0,255,0));
        }
        processedFrames.push_back(frame);
    }
}

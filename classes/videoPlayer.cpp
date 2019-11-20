//
// Created by nrg on 10/7/19.
//

#include "videoPlayer.h"

void videoPlayer::playVideo(const std::string &windowName) {
    cv::namedWindow(windowName, cv::WINDOW_NORMAL); //vytvoreni okna pro video
    cv::resizeWindow(windowName, 600, 600);

    std::cout << "end of video file" << std::endl;
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

bool videoPlayer::openVideoFile(const std::string &fileName) {
    std::cout << "opening video file " << fileName << std::endl;
    videoCapture.open(fileName);
    return videoCapture.isOpened();
}

bool videoPlayer::openCascade(const std::string &cascadeName) {
    if(!haarcascade.load(cascadeName)){
        std::cerr << "Error loading cascade" << std::endl;
        return false;
    }
    return true;
}

void videoPlayer::loadFrames() {
    cv::Mat frame;
    while (true) {

        videoCapture >> frame;
        if (frame.empty())
            break;
        else
            framesToProcess.push(frame.clone());
    }
}

void videoPlayer::detectAndDisplay() {
    cv::Mat frame;
    cv::Mat grayScale;
    std::vector<cv::Rect> detects;
    while(!framesToProcess.empty()){
        frame = framesToProcess.front();

        cv::cvtColor(frame, grayScale, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(grayScale, grayScale);
        haarcascade.detectMultiScale(grayScale, detects);

        for(auto &rect : detects ){
            cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 2);
        }
        processedFrames.push_back(frame);
        detects.clear();
        framesToProcess.pop();

    }


}

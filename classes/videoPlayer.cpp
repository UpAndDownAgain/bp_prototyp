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
    double scale;
    std::cout << "loading frames" << std::endl;
    while (true) {

        videoCapture >> frame;
        if (frame.empty())
            break;
        else {
            scale = 640.0 / frame.size().height;
            cv::resize(frame, frame, cv::Size(), scale, scale, CV_INTER_AREA);
            //std::cout << frame.size().width << " x " << frame.size().height << std::endl;
            framesToProcess.push(frame.clone());
        }
    }
    std::cout << "frames loaded" << std::endl;
}

VideoPlayer::VideoPlayer(const std::string &videoFile, const std::string &detectorFile) {
    try{
        detector = DetectorFactory::createDetector(detectorFile); //vytvori tridu pro detektor v zavisloti na dodanem souboru
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
void VideoPlayer::useDetector() {
    int i=0;
    while(!framesToProcess.empty()){
        std::cout << "detecting frame " << i++ << std::endl;
        cv::Mat frame = framesToProcess.front();
        framesToProcess.pop();
        detector->detectAndDisplay(frame);
        processedFrames.push_back(frame);
    }
}

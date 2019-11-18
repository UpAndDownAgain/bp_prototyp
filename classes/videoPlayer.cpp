//
// Created by nrg on 10/7/19.
//

#include "videoPlayer.h"
videoPlayer::videoPlayer() {
    play = false; //video zacina zastavene
}

videoPlayer::videoPlayer(const std::string &fileName) {
    std::cout << "opening video file " << fileName << std::endl;
    this->videoCapture.open(fileName);
    videoPlayer();
}

void videoPlayer::playVideo(const std::string &windowName) {
    cv::namedWindow(windowName, cv::WINDOW_NORMAL); //vytvoreni okna pro video
    cv::resizeWindow(windowName, 600, 600);
    auto fps = (double)videoCapture.get(CV_CAP_PROP_FPS);
    int currentFrame = (int)videoCapture.get(CV_CAP_PROP_POS_FRAMES);
    std::cout << "playing video" << std::endl;

    while(true){
        if(play || currentFrame == 0) { //video zacina zastavene
            videoCapture >> frame; //nacteni framu z video souboru
            currentFrame = (int)videoCapture.get(CV_CAP_PROP_POS_FRAMES);
            if (frame.empty()){
                //loop video
                videoCapture.set(CV_CAP_PROP_POS_FRAMES, 0);
                continue;
            }
            std::cout << "showing frame number" << currentFrame << std::endl;
            //detectAndDisplay(frame);
            display(frame, currentFrame);
            cv::imshow(windowName, frame); //zobrazeni framu v okne
        }
        char c = (char)cv::waitKey(fps);
        if(c == 'p'){
            play = !play;
        }
        else if(c == 'q'){
            break;
        }
    }
    std::cout << "end of video file" << std::endl;
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

void videoPlayer::detectAndDisplay(cv::Mat &frame) {
    cv::Mat frame_gray;
    cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY); //img na grayscale
    cv::equalizeHist(frame_gray, frame_gray);

    std::vector<cv::Rect> objects;
    haarcascade.detectMultiScale(frame_gray, objects);
    std::cout << "Objects detected " << objects.size() << std::endl;

    for(size_t i = 0; i < objects.size(); ++i){
        cv::rectangle(frame, objects[i], cv::Scalar(0,255,0), 2);
    }
}

void videoPlayer::detect(){
    cv::Mat frame;
    cv::Mat frame_gray;
    double currentFrame;
    std::vector<cv::Rect> detects;

    while(true){

        videoCapture >> frame;
        if(frame.empty())
            break;
        currentFrame = videoCapture.get(CV_CAP_PROP_POS_FRAMES);

        cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(frame_gray, frame_gray);
        std::cout << "detecting frame " << currentFrame << std::endl;
        haarcascade.detectMultiScale(frame_gray, detects);

        for(const auto &item : detects){ //ulozi detekce to object_vect s cislem framu ve kterem se vyskytuje pro pozdejsi vykresleni
            object_vect.emplace_back( std::pair<int,cv::Rect>(currentFrame, item) );
        }
        detects.clear();
    }
    videoCapture.set(CV_CAP_PROP_POS_FRAMES, 0);
}

void videoPlayer::display(cv::Mat &frame, int frame_number) {
    for(size_t i = 0; i < object_vect.size(); ++i){
        if(object_vect[i].first == frame_number){
            cv::rectangle(frame, object_vect[i].second, cv::Scalar(0,255,0), 2);
        }
    }
}


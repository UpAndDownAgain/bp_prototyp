//
// Created by nrg on 10/7/19.
//

#include "videoPlayer.h"

/*
 * prehrani videa ze zpracovanych framu a vykresleni do okna
 */
void videoPlayer::playVideo(const std::string &windowName) {
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
 * nacteni videa
 */
bool videoPlayer::openVideoFile(const std::string &fileName) {
    std::cout << "opening video file " << fileName << std::endl;
    videoCapture.open(fileName);
    return videoCapture.isOpened();
}
/*
 * nacteni kaskady z xml
 */
bool videoPlayer::openCascade(const std::string &cascadeName) {
    if(!haarcascade.load(cascadeName)){
        std::cerr << "Error loading cascade" << std::endl;
        return false;
    }
    return true;
}
/*
 * nahrani framu do fronty pro zpracovani
 */
void videoPlayer::loadFrames() {
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

/*
 * zpracovani framu z fronty a vykresleni detekovanych objektu
 */
void videoPlayer::detectAndDisplay() {
    std::cout << "detecting objects" << std::endl;

    cv::Mat frame;
    cv::Mat grayScale;
    std::vector<cv::Rect> detects;

    while(!framesToProcess.empty()){
        frame = framesToProcess.front();
        //vytvoreni cernobileho framu z originalnu
        cv::cvtColor(frame, grayScale, cv::COLOR_BGR2GRAY); 
        //vyrovnání histogramu
        cv::equalizeHist(grayScale, grayScale);
        //detekce pomoci kaskady
        haarcascade.detectMultiScale(grayScale, detects); 
        cv::groupRectangles(detects, 2, 0.67);
        //vykresleni ctvercu kolem detekovanych objektu
        for(auto &rect : detects ){
            cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 2);
        }
        processedFrames.push_back(frame);
        detects.clear();
        framesToProcess.pop();
    }
}

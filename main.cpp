#include <iostream>
#include "classes/videoPlayer.h"

int main(int argc, char **argv) {

    cv::CommandLineParser parser(argc, argv,
            "{-video||path to video file}"
                     "{-detect||path to cascade or weights file");

    if(argc < 3 ){
        std::cerr << "no arguments" << std::endl;
        return -1;
    }

    VideoPlayer *vp;
    try{
        vp = new VideoPlayer(parser.get<std::string>("-video"),
                parser.get<std::string>("-detect") );
    }catch(std::exception &e){
        std::cerr << e.what() << std::endl;
        return -1;
    }

    vp->loadFrames();

    vp->playVideo("video player");
    return 0;
}
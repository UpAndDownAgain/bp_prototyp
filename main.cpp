#include <iostream>
#include "classes/videoPlayer.h"

int main(int argc, char **argv) {

    if(argc < 3 ){
        std::cerr << "no arguments" << std::endl;
        return -1;
    }

    if(CV_MAJOR_VERSION < 4){
        std::cerr << "error old opencv version" << std::endl;
        return -1;
    }
    std::cout << "Opencv Version: ";
    std::cout << CV_VERSION << std::endl;

    VideoPlayer *vp;
    std::string outFile;

    if(argc == 4){
        outFile = argv[3];
    }else{
        outFile = "output";
    }

    vp = new VideoPlayer(argv[1], argv[2]);

    vp->loadFrames();
    std::cout << "frames loaded\ndetecting" << std::endl;

    vp->useDetector();
    vp->playVideo("video player");
    vp->save(outFile);

    delete(vp);
    return 0;
}
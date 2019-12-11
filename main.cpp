#include <iostream>
#include "classes/videoPlayer.h"

int main(int argc, char **argv) {

    if(argc < 3 ){
        std::cerr << "no arguments" << std::endl;
        return -1;
    }

    VideoPlayer *vp;
    std::string outFile;

    if(argc == 4){
        outFile = argv[3];
    }else{
        outFile = "output";
    }

    try{
        vp = new VideoPlayer( argv[1],argv[2] );
    }catch(std::exception &e){
        std::cerr << e.what() << std::endl;
        return -1;
    }

    vp->loadFrames();
    std::cout << "frames loaded\ndetecting" << std::endl;
    vp->useDetector();
    vp->playVideo("video player");
    vp->save(outFile);
    return 0;
}
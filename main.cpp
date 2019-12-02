#include <iostream>
#include "classes/videoPlayer.h"

int main(int argc, char **argv) {

    if(argc < 3 ){
        std::cerr << "no arguments" << std::endl;
        return -1;
    }

    VideoPlayer *vp;
    try{
        vp = new VideoPlayer( argv[1],argv[2] );
    }catch(std::exception &e){
        std::cerr << e.what() << std::endl;
        return -1;
    }

    vp->loadFrames();
    std::cout << "frames loaded\ndetecting" << std::endl;
    vp->detectAndDisplay();
    vp->playVideo("video player");
    return 0;
}
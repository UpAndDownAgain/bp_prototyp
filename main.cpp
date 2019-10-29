#include <iostream>
#include "classes/videoPlayer.h"

int main(int argc, char **argv) {
    videoPlayer vp;
    std::string fName;

    if(argc < 3){
        std::cout << "file name please" << std::endl;
        std::cin >> fName;
    }else{
        fName = argv[1];
    }
    if(!vp.openCascade(argv[2]))
        return -1;
    if(!vp.openVideoFile(fName)) {
        std::cerr << "error opening video" << std::endl;
        return -1;
    }
    vp.detect();
    vp.playVideo("video player");
    return 0;
}
//
// Created by nrg on 12/2/19.
//

#ifndef BP_PROTOTYP_YOLODETECTOR_H
#define BP_PROTOTYP_YOLODETECTOR_H


#include "Detector.h"
//TODO
class YoloDetector : Detector {
private:


public:
    YoloDetector(std::string &cfg, std::string &weights, std::string &classes);
};


#endif //BP_PROTOTYP_YOLODETECTOR_H

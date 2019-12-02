//
// Created by nrg on 12/2/19.
//

#ifndef BP_PROTOTYP_DETECTORFACTORY_H
#define BP_PROTOTYP_DETECTORFACTORY_H


#include "Detector.h"
#include <memory>

class DetectorFactory {
public:
    DetectorFactory() = default;
    std::unique_ptr<Detector> createDetector(const std::string &file);
};


#endif //BP_PROTOTYP_DETECTORFACTORY_H

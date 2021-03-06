//
// Created by nrg on 12/2/19.
//

#ifndef BP_PROTOTYP_DETECTORFACTORY_H
#define BP_PROTOTYP_DETECTORFACTORY_H


#include "Detector.h"
#include <memory>
#include <exception>

class DetectorFactory {
private:

public:
    DetectorFactory() = default;
    static std::unique_ptr<Detector> createDetector(const std::string &file);

};


#endif //BP
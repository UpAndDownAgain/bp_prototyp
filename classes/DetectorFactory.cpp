//
// Created by nrg on 12/2/19.
//

#include "DetectorFactory.h"
#include "CascadeDetector.h"
#include "YoloDetector.h"
#include <experimental/filesystem>
#include <memory>

std::unique_ptr<Detector> DetectorFactory::createDetector(const std::string &file) {
    std::unique_ptr<Detector> detector;
    std::string extension = std::experimental::filesystem::path(file).extension();
    if(extension == ".xml"){
        detector = std::make_unique<CascadeDetector>(file);
    }
    else if(extension == ".weights"){
        std::string config = "../config/yolov3_custom.cfg";
        detector = std::make_unique<YoloDetector>(config, file);
    }else{
        throw std::invalid_argument("cannot resolve file");
    }
    return detector;
}
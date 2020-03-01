//
// Created by kuskov on 29.02.2020.
//

#ifndef COD_DETECTOR_H
#define COD_DETECTOR_H
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/opencv.hpp"

#include <iostream>
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>

struct DetectedObject{
    std::string object_class;
    int x1;
    int y1;
    int x2;
    int y2;
};

class Detector {
public:
    void detectFaceDlibHog(cv::Mat &frameDlibHog, int inHeight=300, int inWidth=0);
    std::vector<DetectedObject> getDetects();


private:
    dlib::frontal_face_detector hogFaceDetector = dlib::get_frontal_face_detector();
    std::vector<DetectedObject> detected_objs_;
};


#endif //COD_DETECTOR_H
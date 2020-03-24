//
// Created by kuskov on 29.02.2020.
//

#ifndef COD_DETECTOR_H
#define COD_DETECTOR_H

#include "multiheaders.h"
#include <queue>

class Detector {
public:
    void detectFaceDlibHog(cv::Mat &frameDlibHog, int inHeight=300, int inWidth=0);
    DetectedFrame getDetectedFrame();

private:
    dlib::frontal_face_detector hogFaceDetector = dlib::get_frontal_face_detector();
    std::priority_queue<DetectedFrame> detected_image_q_;
};


#endif //COD_DETECTOR_H

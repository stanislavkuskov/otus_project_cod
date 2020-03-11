//
// Created by kuskov on 29.02.2020.
//

#ifndef COD_DETECTOR_H
#define COD_DETECTOR_H

#include "multiheaders.h"

class Detector {
public:
    void detectFaceDlibHog(cv::Mat &frameDlibHog, int inHeight=300, int inWidth=0);
    std::vector<DetectedObject> getDetects();
    cv::Mat getFrame();

private:
    std::mutex cout_mutex;

    dlib::frontal_face_detector hogFaceDetector = dlib::get_frontal_face_detector();
    std::vector<DetectedObject> detected_objs_;
    cv::Mat frame_;
};


#endif //COD_DETECTOR_H

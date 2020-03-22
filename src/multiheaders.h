//
// Created by kuskov on 04.03.2020.
//

#ifndef COD_MULTIHEADERS_H
#define COD_MULTIHEADERS_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/opencv.hpp"


#include <iostream>

#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>

using namespace cv;

struct DetectedObject{
    std::string object_class;
    int x1;
    int y1;
    int x2;
    int y2;
};

struct FrameSize{
    FrameSize():width(640), height(480){};
    double width;
    double height;
};


struct Detected_image{
    cv::Mat image;
    DetectedObject detects;
};


#endif //COD_MULTIHEADERS_H

//
// Created by kuskov on 04.03.2020.
//

#ifndef COD_VISUALIZER_H
#define COD_VISUALIZER_H

#include "multiheaders.h"

using namespace cv;

class Visualizer {
public:
    void drawDetects(const cv::Mat& frame, const std::vector<DetectedObject>& detects);
    cv::Mat getFrame();

private:
    cv::Mat drawed_frame_;
};


#endif //COD_VISUALIZER_H

//
// Created by kuskov on 04.03.2020.
//

#include "visualizer.h"

cv::Mat Visualizer::getFrame() {
    return drawed_frame_;
}

void Visualizer::drawDetects(const cv::Mat& frame_v, const std::vector<DetectedObject>& detects) {

    for (auto & detect : detects) {
        cv::rectangle(
                frame_v,
                cv::Point(detect.x1, detect.y1),
                cv::Point(detect.x2, detect.y2),
                cv::Scalar(0, 255, 0),
                4
        );
    }

    drawed_frame_ = frame_v;

}

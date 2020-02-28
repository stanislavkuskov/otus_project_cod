//
// Created by kuskov on 26.02.2020.
//

#ifndef COD_STREAMER_H
#define COD_STREAMER_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio/videoio.hpp"

#include <utility>
#include <thread>
#include <mutex>
#include <iostream>

struct FrameSize{
    FrameSize():width(640), height(480){};
    double width;
    double height;
};

class Streamer{
public:
    Streamer(int source, FrameSize frame_size);
    cv::Mat getFrame();
    void createFrame();
    ~Streamer();

private:
    cv::VideoCapture capture_;
    cv::Mat image_;
};

#endif //COD_STREAMER_H

//
// Created by kuskov on 26.02.2020.
//

#ifndef COD_STREAMER_H
#define COD_STREAMER_H

#include "multiheaders.h"

class Streamer{
public:
    Streamer(int source, FrameSize frame_size);
    cv::Mat getFrame();
    void createFrame();
    void stop();
    ~Streamer();

private:
    cv::VideoCapture capture_;
    cv::Mat image_;
    std::mutex cout_mutex_;

    bool is_stopped_ = false;
};

#endif //COD_STREAMER_H

//
// Created by kuskov on 26.02.2020.
//

#include "streamer.h"

Streamer::Streamer(int source, FrameSize frame_size) {
    capture_.open(source);
    capture_.set(3, frame_size.width);
    capture_.set(4, frame_size.height);
}

void Streamer::createFrame(){
    cv::Mat frame;
    while (capture_.isOpened()){
        cout_mutex_.lock();
        capture_ >> frame;
//        process frame functions
        image_ = std::move(frame);
        cout_mutex_.unlock();
    }
}

cv::Mat Streamer::getFrame() {
    return image_;
}

Streamer::~Streamer() = default;


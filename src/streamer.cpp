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
    while (!is_stopped_){
        capture_ >> frame;

        cout_mutex_.lock();
        image_ = std::move(frame);
        cout_mutex_.unlock();

        if (!capture_.isOpened()) break;
    }
}

cv::Mat Streamer::getFrame() {

    return image_;
}

void Streamer::stop(){
    is_stopped_ = true;
}

Streamer::~Streamer() = default;


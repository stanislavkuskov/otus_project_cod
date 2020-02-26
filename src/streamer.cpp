//
// Created by kuskov on 26.02.2020.
//

#include "streamer.h"

Streamer::Streamer(int source, FrameSize frame_size) {
    capture_.open(source);
    capture_.set(3, frame_size.width);
    capture_.set(4, frame_size.height);
}

cv::Mat Streamer::getFrame() {
    capture_ >> image_;
    return image_;
}

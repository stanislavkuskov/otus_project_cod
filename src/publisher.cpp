//
// Created by kuskov on 11.03.2020.
//
#include "publisher.h"

Publisher::Publisher(): context_(1), pub_(context_, ZMQ_PUB) {
    pub_.bind("tcp://*:5563");
    printf("Starting server...\n");
}

void Publisher::setDetect(std::vector<DetectedObject> detected_objs) {
    // TODO make it atomic
    detected_objs_ = std::move(detected_objs);
}

void Publisher::transmitDetect() {
    std::string data_text = "Text";
    while (true){
        // TODO make it atomic
        zmq_send(pub_, topic_.data(), topic_.size(), ZMQ_SNDMORE);
        zmq_send(pub_, data_text.data(), data_text.size(), 0);

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

}

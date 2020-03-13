//
// Created by kuskov on 11.03.2020.
//
#include "publisher.h"

Publisher::Publisher(): context_(1), pub_(context_, ZMQ_PUB) {
    pub_.bind("tcp://*:5563");
    printf("Starting server...\n");
}

void Publisher::setDetect(std::vector<DetectedObject> detected_objs) {
    cout_mutex_.lock();
    detected_objs_ = std::move(detected_objs);
    cout_mutex_.unlock();
}

void Publisher::transmitDetect() {
    std::string data_text = "Text";
    while (true){

        cout_mutex_.lock();

        std::string msg_data = convertToJson(detected_objs_);
        zmq_send(pub_, topic_.data(), topic_.size(), ZMQ_SNDMORE);
        zmq_send(pub_, msg_data.data(), msg_data.size(), 0);

        cout_mutex_.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

}

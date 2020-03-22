//
// Created by kuskov on 11.03.2020.
//
#include <thread>
#include <chrono>
#include "publisher.h"

Publisher::Publisher(): context_(1), pub_(context_, ZMQ_PUB) {
    pub_.bind("tcp://*:5563");
    printf("Starting server...\n");
}

void Publisher::setDetect(const std::vector<DetectedObject> &detected_objs) {
    cout_mutex_.lock();
    detected_objs_ = detected_objs;
    cout_mutex_.unlock();
}

void Publisher::transmitDetect() {

    while (!is_stopped_){

        cout_mutex_.lock();
        std::string msg_data = convertToJson(detected_objs_);
        cout_mutex_.unlock();

        zmq_send(pub_, topic_.data(), topic_.size(), ZMQ_SNDMORE);
        zmq_send(pub_, msg_data.data(), msg_data.size(), 0);

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

}

std::string Publisher::convertToJson(const std::vector<DetectedObject>& detected_objs) {
    std::string msg_data;

    msg_data += R"([)";
    if (!detected_objs.empty()){
        for (const DetectedObject& detected_object: detected_objs){
            msg_data +=
                R"([{)"
                    R"("object_class":")" + detected_object.object_class + R"(",)"
                    R"("x1":")" + std::to_string(detected_object.x1) + R"(",)"
                    R"("x2":")" + std::to_string(detected_object.x2) + R"(",)"
                    R"("y1":")" + std::to_string(detected_object.y1) + R"(",)"
                    R"("y2":")" + std::to_string(detected_object.y2) + R"(")"
                R"(}])";
                if (&detected_object != &detected_objs.back()){
                    msg_data += R"(,)";
                }
        }
    }
    msg_data += R"(])";

    return msg_data;
}

void Publisher::stop() {
    is_stopped_ = true;
}

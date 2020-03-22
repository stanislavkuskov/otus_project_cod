//
// Created by kuskov on 11.03.2020.
//

#ifndef COD_PUBLISHER_H
#define COD_PUBLISHER_H

#include "multiheaders.h"
#include <zmq.hpp>

class Publisher {
public:
    Publisher();
    void setDetect(const std::vector<DetectedObject> &detected_objs);
    void transmitDetect();
    void stop();

private:

    static std::string convertToJson(const std::vector<DetectedObject>& detected_objs);

    std::string topic_ = "cod";
    std::string msg_data_ = "";
    std::vector<DetectedObject> detected_objs_;

    zmq::context_t context_;
    zmq::socket_t pub_;
    std::mutex cout_mutex_;

    bool is_stopped_ = false;

};


#endif //COD_PUBLISHER_H

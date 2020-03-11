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
    void setDetect(std::vector<DetectedObject> detected_objs);
    void transmitDetect();

private:
    std::string topic_ = "cod";
    std::vector<DetectedObject> detected_objs_;

    zmq::context_t context_;
    zmq::socket_t pub_;

};


#endif //COD_PUBLISHER_H

//
// Created by kuskov on 11.03.2020.
//

#include "publisher.h"

void Publisher::setDetect(std::vector<DetectedObject> detected_objs) {
    detected_objs_ = std::move(detected_objs);
}

void Publisher::transmitDetect() {
    while (true){
        std::cout << "transmit" << std::endl;
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

}

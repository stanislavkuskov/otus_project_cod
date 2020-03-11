//
// Created by kuskov on 11.03.2020.
//

#ifndef COD_PUBLISHER_H
#define COD_PUBLISHER_H

#include "multiheaders.h"

class Publisher {
public:
    void setDetect(std::vector<DetectedObject> detected_objs);
    void transmitDetect();

private:
    std::vector<DetectedObject> detected_objs_;
};


#endif //COD_PUBLISHER_H

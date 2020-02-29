//https://pydeeplearning.com/opencv/install-opencv-with-c-on-ubuntu-18-04/
//https://gist.github.com/Randommood/478ccd806511d45febc1

#include <iostream>
#include "src/streamer.h"


int main()
{
    FrameSize frame_size;
    cv::Mat frame;

    auto * streamer = new Streamer(0, frame_size);
    std::thread (&Streamer::createFrame, streamer).detach();

    while (true){

        frame = streamer->getFrame();
        if (!frame.empty()){
            imshow("Sample2", frame);
        }
        if(cv::waitKey(10) >= 0)
            break;
    }

    delete streamer;
    return 0;
}
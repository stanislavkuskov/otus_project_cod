//https://pydeeplearning.com/opencv/install-opencv-with-c-on-ubuntu-18-04/
//https://gist.github.com/Randommood/478ccd806511d45febc1

#include "src/streamer.h"

int main(int argc, char*argv[])
{
    FrameSize frame_size;
    Streamer streamer(0, frame_size);
    cv::Mat frame;
    while (true){
        frame = streamer.getFrame();
        imshow("Sample", frame);
        if(cv::waitKey(10) >= 0)
            break;
    }
    return 0;
}
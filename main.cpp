//https://pydeeplearning.com/opencv/install-opencv-with-c-on-ubuntu-18-04/
//https://gist.github.com/Randommood/478ccd806511d45febc1

#include "src/streamer.h"
#include "src/detector.h"

int main()
{
    FrameSize frame_size;
    Streamer streamer(0, frame_size);
    Detector detector;

    cv::Mat frame;
    while (true){
        frame = streamer.getFrame();
        if(frame.empty()){
            break;
        }

        detector.detectFaceDlibHog(frame);
        imshow("Sample", frame);


        if(cv::waitKey(10) >= 0)
            break;
    }
    return 0;
}
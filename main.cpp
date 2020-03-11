//https://pydeeplearning.com/opencv/install-opencv-with-c-on-ubuntu-18-04/
//https://gist.github.com/Randommood/478ccd806511d45febc1


#include "src/streamer.h"
#include "src/detector.h"
#include "src/visualizer.h"

int main()
{
    FrameSize frame_size;
    cv::Mat frame;
    cv::Mat drawed;
    auto * streamer = new Streamer(2, frame_size);
    std::thread (&Streamer::createFrame, std::ref(streamer)).detach();

    Detector detector;
    Visualizer visualizer;

    while (true){
        frame = streamer->getFrame();
        drawed = frame.clone();

        if (!frame.empty()){
            detector.detectFaceDlibHog(frame);
            std::vector<DetectedObject> detects = detector.getDetects();

            visualizer.drawDetects(drawed, detects);
            cv::Mat vis_frame = visualizer.getFrame();

            cv::imshow("Sample1", vis_frame);
        }

        if(frame.empty()){
            break;
        }
        if(cv::waitKey(10) >= 0)
            break;
    }
    delete streamer;
    return 0;
}
//https://pydeeplearning.com/opencv/install-opencv-with-c-on-ubuntu-18-04/
//https://gist.github.com/Randommood/478ccd806511d45febc1

#include <thread>

#include "src/detector.h"
#include "src/streamer.h"
#include "src/publisher.h"
#include "src/visualizer.h"

int main()
{
    FrameSize frame_size;
    cv::Mat frame;
    cv::Mat drawed;

    auto * streamer = new Streamer(0, frame_size);
    std::thread streamer_thread(&Streamer::createFrame, std::ref(streamer));

    auto * publisher = new Publisher();
    std::thread publisher_thread(&Publisher::transmitDetect, std::ref(publisher));

    Detector detector;
    Visualizer visualizer;

    while (true){
        frame = streamer->getFrame();

        if (!frame.empty()){
            detector.detectFaceDlibHog(frame);
            std::vector<DetectedObject> detects = detector.getDetects();
            cv::Mat detector_img = detector.getFrame();

            cv::Mat detector_current_frame = detector.getFrame();
            visualizer.drawDetects(detector_current_frame, detects);

            cv::Mat vis_frame = visualizer.getFrame();
            cv::imshow("Sample1", vis_frame);

            publisher->setDetect(detects);
        }


        if(frame.empty()){
            break;
        }
        if(cv::waitKey(10) >= 0){
            streamer->stop();
            publisher->stop();
            break;
        }

    }

    streamer_thread.join();
    publisher_thread.join();
    delete streamer;
    delete publisher;
    return 0;
}
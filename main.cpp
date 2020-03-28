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

    auto streamer = std::make_unique<Streamer>(0, frame_size);
    std::thread streamer_thread(&Streamer::createFrame, streamer.get());

    auto publisher = std::make_unique<Publisher>();
    std::thread publisher_thread(&Publisher::transmitDetect, publisher.get());

    Detector detector;
    Visualizer visualizer;

    DetectedFrame detected_frame;

    while (true){
        frame = streamer->getFrame();

        if (!frame.empty()){
            detector.detectFaceDlibHog(frame);

            detected_frame = detector.getDetectedFrame();

            visualizer.drawDetects(detected_frame.image, detected_frame.detects);

            cv::Mat vis_frame = visualizer.getFrame();
            cv::imshow("Sample1", vis_frame);

            publisher->setDetect(detected_frame.detects);
        }


        if(frame.empty()){
            streamer->stop();
            publisher->stop();
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
    return 0;
}
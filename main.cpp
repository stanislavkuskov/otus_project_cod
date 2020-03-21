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

    auto * streamer = new Streamer(2, frame_size); // Лучше использовать умные указатели, например unique_ptr
    std::thread (&Streamer::createFrame, std::ref(streamer)).detach(); // Довольно опасно так делать, в данном случае лучше
                                                                       // созадть именовыный поток std::thread th_stream()
                                                                       // в конец программы подождать завершения методом join

    auto * publisher = new Publisher(); // Умные указатели
    std::thread (&Publisher::transmitDetect, std::ref(publisher)).detach(); // Тоже самое с этим потоком

    Detector detector;
    Visualizer visualizer;

    while (true){ // Лучше добавить некое условие на выход. Будет полезно когда код будет запускаться в виде сервиса.
        frame = streamer->getFrame();
        drawed = frame.clone();

        if (!frame.empty()){
            detector.detectFaceDlibHog(frame);
            std::vector<DetectedObject> detects = detector.getDetects();
            cv::Mat detector_img = detector.getFrame();

            visualizer.drawDetects(drawed, detector_img);
            publisher->setDetect(detects);

            cv::Mat vis_frame = visualizer.getFrame();
            cv::imshow("Sample1", vis_frame);
        }

        if(frame.empty()){
            break;
        }
        if(cv::waitKey(10) >= 0)
            break;
    }
    delete streamer; // Умные указатели
    delete publisher; // Умные указаели
    return 0;
}

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void drawText(Mat & image);

int main()
{
    cout << "Built with OpenCV " << CV_VERSION << endl;
    Mat image;
    VideoCapture capture;
    capture.open(0);
    capture.set(3,640);
    capture.set(4,480);

    while (capture.isOpened())
    {
        capture >> image;
        imshow("Sample", image);
        if(waitKey(10) >= 0)
            break;
    }
    return 0;
}
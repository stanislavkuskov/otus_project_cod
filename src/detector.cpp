//
// Created by kuskov on 29.02.2020.
//

#include "detector.h"
//https://github.com/spmallick/learnopencv/blob/master/FaceDetectionComparison/face_detection_dlib_hog.cpp
void Detector::detectFaceDlibHog(cv::Mat &frameDlibHog, int inHeight,
                                 int inWidth) {

    int frameHeight = frameDlibHog.rows;
    int frameWidth = frameDlibHog.cols;
    if (!inWidth)
        inWidth = (int)((frameWidth / (float)frameHeight) * inHeight);

    float scaleHeight = frameHeight / (float)inHeight;
    float scaleWidth = frameWidth / (float)inWidth;

    cv::Mat frameDlibHogSmall;
    cv::resize(frameDlibHog, frameDlibHogSmall, cv::Size(inWidth, inHeight));

    // Convert OpenCV image format to Dlib's image format
    dlib::cv_image<dlib::bgr_pixel> dlibIm(frameDlibHogSmall);

    // Detect faces in the image
    std::vector<dlib::rectangle> faceRects = hogFaceDetector(dlibIm);

    for (auto & faceRect : faceRects)
    {
        int x1 = (int)(faceRect.left() * scaleWidth);
        int y1 = (int)(faceRect.top() * scaleHeight);
        int x2 = (int)(faceRect.right() * scaleWidth);
        int y2 = (int)(faceRect.bottom() * scaleHeight);
        cv::rectangle(frameDlibHog, Point(x1, y1), Point(x2, y2), Scalar(0,255,0), (int)(frameHeight/150.0), 4);
    }
}


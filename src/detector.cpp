//
// Created by kuskov on 29.02.2020.
//

#include "detector.h"

//https://github.com/spmallick/learnopencv/blob/master/FaceDetectionComparison/face_detection_dlib_hog.cpp
void Detector::detectFaceDlibHog(cv::Mat &frameDlibHog, int inHeight,
                                 int inWidth) {

    std::vector<DetectedObject> detected_objs;
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
        DetectedObject detected_obj;
        detected_obj.x1 = x1;
        detected_obj.y1 = y1;
        detected_obj.x2 = x2;
        detected_obj.y2 = y2;
//        TODO добавление обьектов не должно прерываться
        detected_objs.push_back(detected_obj);
    }
//    TODO make as atomic operation
    cout_mutex.lock();
    detected_objs_ = detected_objs;
    frame_ = frameDlibHog;
    cout_mutex.unlock();
}

std::vector<DetectedObject> Detector::getDetects() {
    return detected_objs_;
}

cv::Mat Detector::getFrame(){
    return frame_;
}

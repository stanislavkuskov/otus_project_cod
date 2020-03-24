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

        detected_objs.push_back(detected_obj);
    }

    DetectedFrame detected_frame;
    detected_frame.image = frameDlibHog;
    detected_frame.detects = detected_objs;
    if ((detected_image_q_.size() > q_size_) and (!detected_image_q_.empty())){
        detected_image_q_.pop();
    }
    std::cout << detected_image_q_.size() << std::endl;
    detected_image_q_.push(detected_frame);

}

DetectedFrame Detector::getDetectedFrame(){
    return detected_image_q_.back();
}

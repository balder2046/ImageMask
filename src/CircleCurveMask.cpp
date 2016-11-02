//
// Created by 赵磊 on 2016/10/31.
//

#include "CircleCurveMask.h"

using namespace cv;

void CircleCurveMask::FillMask(cv::Mat &matMask) {
    // -1 for fill the circle
    circle(matMask, center, radius, Scalar(255), -1);
    setDirty(false);
}

void CircleCurveMask::ShowEditMarker(cv::Mat &matImage, const cv::Scalar &fillColor) {
    circle(matImage, center, radius, fillColor, 5);
    setDirty(false);
}

void CircleCurveMask::OnMouse(int event, int x, int y, int flags) {
    if (event == CV_EVENT_LBUTTONDOWN) {
        Point pos(x, y);
        center = pos;
        setDirty(true);
    }
    MaskDataBase::OnMouse(event, x, y, flags);
}

CircleCurveMask::CircleCurveMask(const cv::Point &center) {
    this->center = center;

}

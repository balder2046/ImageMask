//
// Created by 赵磊 on 2016/10/27.
//

#include "CatmullCurveMask.h"
#include "MathUtil.h"

using namespace cv;
CatmullCurveMask::CatmullCurveMask() {
    interCount = 4;
    nCurveWidth = 30;
    iterWeights.clear();
    for (int i = 1; i < interCount + 2; ++i)
    {
        iterWeights.push_back((float)i / (interCount + 2));
    }
}

CatmullCurveMask::~CatmullCurveMask() {

}

void CatmullCurveMask::ShowEditMarker(cv::Mat &matImage, const cv::Scalar &fillColor) {
    for (int i = 0; i < (int)vecPointData.size(); ++i) {
        circle(matImage,vecPointData[i], 10,fillColor);
    }
}

void CatmullCurveMask::OnMouse(int event, int x, int y, int flags) {
    Point pos(x,y);
    if (event == CV_EVENT_LBUTTONDOWN)
    {
        if (flags & CV_EVENT_FLAG_CTRLKEY)
        {
            vecPointData.push_back(pos);
        }
    }
}

void CatmullCurveMask::EditDone() {

    MaskDataBase::EditDone();

}

void CatmullCurveMask::OnKey(int event, int keycode, int flags) {
    MaskDataBase::OnKey(event, keycode, flags);


}

void CatmullCurveMask::FillMask(cv::Mat &matMask) {
    std::vector<Point> pts;
    generateNewPoints(pts);
    int pointcount = (int) vecPointData.size();
    if (pointcount < 1) {
        return;
    }
    else if (pointcount < 2) {
        // only draw

    }
    else
    {
        int curvepointcount = (int)pts.size();
        for (int i = 0; i < curvepointcount - 1; ++i) {
            Point start = pts[i];
            Point end = pts[i + 1];
            line(matMask, start, end, Scalar(255),nCurveWidth);
        }
    }


}

void CatmullCurveMask::generateNewPoints(std::vector<cv::Point> &pts) {
    // We inter points from segments!
    // check the size, 1 points return;
    if (vecPointData.size() < 2) return;
    int pointcount = (int)vecPointData.size();
    for (int i = 0; i < pointcount - 1; ++i) {
        pts.push_back(vecPointData[i]);
        int leftleft = i - 1;
        int left = i;
        int right = i + 1;
        int rightright = i + 2;
        if (leftleft < 0) leftleft = 0;
        if (rightright > pointcount - 1) rightright = pointcount - 1;
        for (int j = 0; j < (int)iterWeights.size(); ++j) {
            Point newPt = CatmullRom(vecPointData[leftleft],vecPointData[left],vecPointData[right],vecPointData[rightright],iterWeights[j]);
            pts.push_back(newPt);
        }
    }
    // add the last
    pts.push_back(vecPointData.back());
}

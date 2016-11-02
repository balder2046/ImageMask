//
// Created by 赵磊 on 2016/10/31.
//

#ifndef IMAGEMASK_CIRCLECURVEMASK_H
#define IMAGEMASK_CIRCLECURVEMASK_H

#include "opencv2/opencv.hpp"
#include "MaskDataBase.h"

class CircleCurveMask : public MaskDataBase{
public:

    CircleCurveMask(const cv::Point &center);

    virtual void FillMask(cv::Mat &matMask) override;

    virtual void OnMouse(int event, int x, int y, int flags) override;

    virtual void ShowEditMarker(cv::Mat &matImage, const cv::Scalar &fillColor) override;

protected:
    int radius = 10;
    cv::Point center;

};


#endif //IMAGEMASK_CIRCLECURVEMASK_H

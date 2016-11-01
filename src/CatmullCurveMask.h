//
// Created by 赵磊 on 2016/10/27.
//

#ifndef IMAGEMASK_CATMULLCUVEMASK_H
#define IMAGEMASK_CATMULLCUVEMASK_H

#include "MaskDataBase.h"
#include "opencv2/opencv.hpp"
class CatmullCurveMask : public MaskDataBase{
public:
    virtual ~CatmullCurveMask();

    CatmullCurveMask();
public:
    virtual void OnMouse(int event, int x, int y, int flags) override;

    virtual void FillMask(cv::Mat &matMask) override;

    virtual void ShowEditMarker(cv::Mat &matImage, const cv::Scalar &fillColor) override;

    virtual void OnKey(int event, int keycode, int flags) override;

private:
    std::vector<cv::Point> vecPointData;

    int interCount;
    void generateNewPoints(std::vector<cv::Point> &pts);

protected:
    virtual void EditDone() override;

private:
    std::vector<float> iterWeights;
    int nCurveWidth;
};


#endif //IMAGEMASK_CATMULLCUVEMASK_H

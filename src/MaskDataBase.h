//
// Created by 赵磊 on 2016/10/24.
//

#ifndef IMAGEMASK_MASKDATABASE_H
#define IMAGEMASK_MASKDATABASE_H

#include <memory>
#include "opencv2/opencv.hpp"
class MaskDataBase {
public:

    virtual ~MaskDataBase();
public:
    /// summary fill the mask from mat
    /// \param matMask
    virtual void FillMask(cv::Mat &matMask) = 0;
    virtual void ShowEditMarker(cv::Mat &matImage, const cv::Scalar &fillColor) = 0;
    virtual void OnMouse(int event, int x, int y,int flags)
    {

    }
    virtual void OnKey(int event,int keycode, int flags)
    {

    }
public:
    bool IsEditDone()
    {
        return mEditDone;
    }
public:
    virtual void EditDone()
    {
        mEditDone = true;
    }
    bool isDirty()
    {
        return mDirty;
    }
protected:
    void setDirty(bool dirty = true)
    {
        mDirty = dirty;
    }


protected:
    bool mEditDone = false; // Edit complete?
    bool mDirty = false;

};
typedef std::shared_ptr<MaskDataBase> MaskPtr;

#endif //IMAGEMASK_MASKDATABASE_H

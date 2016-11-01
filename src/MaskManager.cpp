//
// Created by 赵磊 on 2016/10/25.
//

#include "MaskManager.h"
#include "CatmullCurveMask.h"
using namespace cv;
void MaskManager::AddMask(MaskPtr newPtr) {
    maskArray.push_back(newPtr);
}

void MaskManager::Pop() {
    if (maskArray.empty()) return;
    maskArray.pop_back();
}

void MaskManager::FillMask(cv::Mat &matMask) {
    for (int i = 0; i < (int)maskArray.size(); ++i) {
        if (maskArray[i] && maskArray[i]->IsEditDone())
       maskArray[i]->FillMask(matMask);
    }

}

void MaskManager::OnMouse(int event, int x, int y, int flags) {
    // only the last is the actor mask
    //Iter(std::bind(&MaskDataBase::OnMouse,std::placeholders::_1,event,x,y,flags));
    MaskPtr ptr = GetActiveMaskEditor();
    if (ptr != nullptr)
    {
        ptr->OnMouse(event, x, y, flags);
    }
}

void MaskManager::OnKey(int event, int keycode,int flags) {
    // Iter(std::bind(&MaskDataBase::OnKey,std::placeholders::_1,event,keycode,flags));
    MaskPtr ptr = GetActiveMaskEditor();
    // the return key
    if (keycode == '\r')
    {
        if (ptr != nullptr)
        {
            ptr->EditDone();
            NewMaskEditor();
            return;
        }
    }
        // the backspace key
    else if (keycode == 8)
    {
        if (ptr != nullptr)
        {

        }
    }
        // the esc key
    else if (keycode == 27)
    {
        if( ptr != nullptr && !ptr->IsEditDone())
        {
            Pop();
            ptr = nullptr;
        }
    }
    if (ptr != nullptr)
    {
        ptr->OnKey(event,keycode,flags);
    }
}

void MaskManager::Iter(const std::function<void(MaskPtr)> &func) {
    for (int i = 0; i < (int)maskArray.size(); ++i) {
        MaskPtr ptr = maskArray[i];
        func(ptr);
    }


}

MaskPtr MaskManager::GetActiveMaskEditor() {
    if (maskArray.empty()) return nullptr;
    MaskPtr ptr = maskArray.back();
    if (ptr->IsEditDone()) return nullptr;
    return ptr;
}

void MaskManager::NewMaskEditor() {
    MaskPtr ptr(new CatmullCurveMask());
    AddMask(ptr);

}

void MaskManager::OnDraw(cv::Mat &frame) {
    // first calc the mask
    // the mask has 1 channel
    cv::Mat mask(frame.rows,frame.cols,CV_8UC1);

    for (int i = 0; i < (int)maskArray.size(); ++i)
    {
        MaskPtr ptr = maskArray[i];
        if (ptr && ptr->IsEditDone())
        {
            ptr->FillMask(mask);
        }
    }
    ApplyPixelFuncWithMask(frame,mask);
    MaskPtr editPtr = GetActiveMaskEditor();
    if (editPtr)
    {
        editPtr->ShowEditMarker(frame,cv::Scalar(0,255,0));
    }

}

void MaskManager::ApplyPixelFuncWithMask(cv::Mat &frame, cv::Mat &mask) {
    for (int row = 0; row < frame.rows; ++row) {
        cv::Vec3b *rgbbuf = frame.ptr<cv::Vec3b>(row);
        unsigned char *bytebuf = mask.ptr<unsigned char>(row);
        for (int col = 0; col < frame.cols; ++col) {
            if (bytebuf[col] > 0)
            {
                Vec3b &color = rgbbuf[col];
                for (int i = 0; i < 3; ++i) {
                    color[i] = color[i] * 2 > 255 ? 255 : color[i] * 2;
                }

            }
        }
    }


}

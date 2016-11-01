//
// Created by 赵磊 on 2016/10/25.
//

#ifndef IMAGEMASK_MASKMANAGER_H
#define IMAGEMASK_MASKMANAGER_H

#include "MaskDataBase.h"
#include <vector>
#include <memory>
#include <functional>

class MaskManager {
public:
    void AddMask(MaskPtr newPtr);
    void Pop();
public:
    void Reset()
    {
        maskArray.clear();
    }
public:
    void FillMask(cv::Mat &matMask);
public:
    void OnMouse(int event, int x, int y,int flags);

    void OnKey(int event,int keycode,int flags);
public:

    void NewMaskEditor();
public:
    void OnDraw(cv::Mat &frame);
public:
    MaskPtr GetActiveMaskEditor();
public:
    void Iter(const std::function<void(MaskPtr)> &func);
public:
    static void ApplyPixelFuncWithMask(cv::Mat &frame, cv::Mat &mask);
private:
    std::vector<MaskPtr> maskArray;
};


#endif //IMAGEMASK_MASKMANAGER_H

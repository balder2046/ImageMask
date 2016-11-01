#include <iostream>
#include "opencv2/opencv.hpp"
#include <gtest/gtest.h>
#include <MaskManager.h>
#include <CatmullCurveMask.h>

using namespace cv;
int main(int argc, char **argv) {
    int width = 640;
    int height = 368;
    Mat matFrame(height, width, CV_8UC3);
    Mat matMask(height,width,CV_8UC3);

    namedWindow("MaskEditor", CV_WINDOW_AUTOSIZE);
    circle(matMask,Point(width / 2, height / 2),50,Scalar(255,255,255),-1);
    matFrame = imread("color.png");
    addWeighted(matFrame,0.5, matMask, 0.5,0.0,matFrame);
    imshow("MaskEditor",matFrame);
    createButton("Add Curve", nullptr,0,QT_PUSH_BUTTON);
    int frametime = 30;
    int keycode = 0;
    MaskManager maskManager;
    while (keycode != 27)
    {
        keycode = waitKey(frametime);
        switch(keycode)
        {
            case 27:
                break;
            case 'n':
            {
                MaskPtr ptr(new CatmullCurveMask());
                maskManager.AddMask(ptr);
                break;
            }

            default:
                maskManager.OnKey(0,keycode,0);
                break;


        }
    }


    return 0;
}
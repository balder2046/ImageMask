#include <iostream>
#include "opencv2/opencv.hpp"
#include <gtest/gtest.h>
#include <MaskManager.h>
#include <CatmullCurveMask.h>
#include <list>
#include <CircleCurveMask.h>

using namespace cv;

struct MouseEvent {
    MouseEvent(int _evt, int _x, int _y, int _flags, void *_param) {
        event = _evt;
        x = _x;
        y = _y;
        flags = _flags;
        param = _param;
    }

    int event;
    int x, y;
    int flags;
    void *param;
};

std::list<MouseEvent> listMouseEvent;

void cbmouse(int event, int x, int y, int flags, void *param) {
    bool brecord = false;
    int events_to_record[] = {CV_EVENT_LBUTTONDOWN, CV_EVENT_LBUTTONUP, CV_EVENT_RBUTTONDOWN, CV_EVENT_RBUTTONUP};
    for (int i = 0; i < (int) sizeof(events_to_record) / sizeof(int); ++i) {
        if (events_to_record[i] == event) {
            brecord = true;
        }
    }
    if (brecord) {
        MouseEvent evt(event, x, y, flags, param);
        listMouseEvent.push_back(evt);
    }
}

void mainloop(int frametime, const std::string &mainwndname, Mat &frame) {
    bool needexit = false;
    int width = frame.cols;
    int height = frame.rows;
    bool bFirst = true;
    listMouseEvent.clear();
    setMouseCallback(mainwndname,cbmouse);
    MaskManager maskManager;
    while (!needexit) {
        int keycode = waitKey(frametime);
        if (keycode == 27) {
            break;
        }
        switch (keycode) {
            case 'n': {
                MaskPtr ptr(new CatmullCurveMask());
                maskManager.AddMask(ptr);
                break;
            }
            case 't': {
                MaskPtr ptr(new CircleCurveMask(Point(width / 2, height / 2)));
                maskManager.AddMask(ptr);
                break;
            }


            default:
                maskManager.OnKey(0, keycode, 0);
        }
        // now we deal with mouse messages
        while (!listMouseEvent.empty()) {
            MouseEvent evt = listMouseEvent.back();
            listMouseEvent.pop_back();
            maskManager.OnMouse(evt.event, evt.x, evt.y, evt.flags);

        }
        if (maskManager.IsDirty() || bFirst) {
            Mat render;
            bFirst = false;
            frame.copyTo(render);
            maskManager.OnDraw(render);
            imshow(mainwndname, render);
        }


    }
}

int main(int argc, char **argv) {
    int width = 640;
    int height = 368;
    Mat matFrame(height, width, CV_8UC3);
    Mat matMask(height, width, CV_8UC3);

    namedWindow("MaskEditor", CV_WINDOW_AUTOSIZE);
    circle(matMask, Point(width / 2, height / 2), 50, Scalar(255, 255, 255), -1);
    matFrame = imread("color.png");
    // addWeighted(matFrame, 0.5, matMask, 0.5, 0.0, matFrame);
    // imshow("MaskEditor", matFrame);
//    createButton("Add Curve", nullptr,0,QT_PUSH_BUTTON);
    int frametime = 30;
    mainloop(frametime, "MaskEditor", matFrame);

    return 0;
}
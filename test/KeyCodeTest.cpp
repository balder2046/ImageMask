//
// Created by 赵磊 on 2016/10/28.
//
#include <opencv2/opencv.hpp>
#include <iostream>
#include "stdio.h"
using namespace cv;
using namespace std;
int main(int argc, char **argv)
{
    int keycode = 0;
    namedWindow("Hello");
    while (keycode != 27)
    {
        cout << "Pressed Any Key To Test ...." << endl;
        keycode = waitKey(0);
        cout << " You Clicked keycode " << keycode << endl;
        cout << endl;
        cout << endl;
        cout << endl;
    }
}

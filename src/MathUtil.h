//
// Created by 赵磊 on 2016/10/27.
//

#ifndef IMAGEMASK_MATHUTIL_H
#define IMAGEMASK_MATHUTIL_H
template <class T>
T CatmullRom(const T &p1, const T &p2 , const T &p3, const T &p4,float s)
{
    float t1 = -1.0f * s * s * s + 2.0f * s * s - s;
    float t2 =  3.0f * s * s * s - 5.0f * s * s + 2.0f;
    float t3 = -3.0f * s * s * s + 4.0f * s * s + s;
    float t4 =  1.0f * s * s * s - 1.0f * s * s;
    return (t1 * p1 + t2 * p2 + t3 * p3 + t4 * p4) * 0.5f;
}
#endif //IMAGEMASK_MATHUTIL_H

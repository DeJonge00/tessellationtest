#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include <QTime>
#include <QVector>
#include <chrono>


class FPScounter
{
public:
    FPScounter();
    void addFrameTime(std::chrono::high_resolution_clock::time_point t);
    int getFPS();

private:
    int len;
    int lastInsertIndex;
    QVector<std::chrono::high_resolution_clock::time_point> frameTimes;
};

#endif // FPSCOUNTER_H

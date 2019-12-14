#include <QDebug>
#include "fpscounter.h"
#include "math.h"

FPScounter::FPScounter()
    :len(50), lastInsertIndex(len), frameTimes(QVector<std::chrono::high_resolution_clock::time_point>())
{
    std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < len; i++) {
        frameTimes.append(currentTime);
    }
}

void FPScounter::addFrameTime(std::chrono::high_resolution_clock::time_point t) {
    lastInsertIndex = (lastInsertIndex + 1) % len;
    frameTimes.remove(lastInsertIndex);
    frameTimes.insert(lastInsertIndex, t);
}


int FPScounter::getFPS() {
    double passed = std::chrono::duration_cast<std::chrono::duration<double>>(frameTimes.at(fmod(lastInsertIndex, len))-frameTimes.at(fmod(lastInsertIndex+1, len))).count();
    if (passed == 0.0) { return 0; }
    return 1 / (passed / len);
}

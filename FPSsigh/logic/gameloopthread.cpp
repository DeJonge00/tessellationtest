#include "gameloopthread.h"

GameLoopThread::GameLoopThread(MainWindow* mw, GameWindow *gw)
    : running(false), ui(mw), gameWindow(gw), fpsCounter(new FPScounter()),
      maxFps(330)
{

}

void GameLoopThread::run() {
    running = true;
    int framecounter = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    double prevCycleTime = 0;
    while (running) {
        framecounter++;
        // Loop time stuff
        start = std::chrono::high_resolution_clock::now();

        // Update character (handle controls)
        gameWindow->gameRenderer->gameCharacter->update(2*prevCycleTime);

        // Update FPS counter
        fpsCounter->addFrameTime(start);

        if (framecounter % 100 == 0) {
            ui->setFpsLabel(fpsCounter->getFPS());
        }

        gameWindow->update();
        end = std::chrono::high_resolution_clock::now();

        prevCycleTime = std::chrono::duration_cast<std::chrono::duration<double>>(end-start).count();
        double minLoopTime = 1000/maxFps; // milliseconds
        double sleepTime = fmin(minLoopTime-(1000*prevCycleTime), minLoopTime);
//        qDebug() << "Thread" << minLoopTime << maxFps << prevCycleTime << sleepTime;
        if (sleepTime > 0) {
            msleep(sleepTime);
            prevCycleTime = minLoopTime;
        }
    }
}

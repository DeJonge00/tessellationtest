#include "gameloopthread.h"

GameLoopThread::GameLoopThread(MainWindow* mw, GameWindow *gw)
    : running(false), ui(mw), gameWindow(gw), fpsCounter(new FPScounter())
{

}

void GameLoopThread::run() {
    running = true;
    int framecounter = 0;
    std::chrono::high_resolution_clock::time_point start, end;
    end = std::chrono::high_resolution_clock::now();
    while (running) {
        // Loop time stuff
        start = std::chrono::high_resolution_clock::now();
        double prevCycleTime = std::chrono::duration_cast<std::chrono::duration<double>>(end-start).count();

        double minLoopTime = 0.01; // seconds
        if (prevCycleTime < minLoopTime) {
            msleep(1000*(minLoopTime - prevCycleTime));
            prevCycleTime = minLoopTime;
        }
        framecounter++;

        // Update character (handle controls)
        gameWindow->gameRenderer->gameCharacter->update(1000*prevCycleTime);

        // Update FPS counter
        fpsCounter->addFrameTime(start);

        if (framecounter % 100 == 0) {
            ui->setFpsLabel(fpsCounter->getFPS());
        }

        gameWindow->update();
        end = std::chrono::high_resolution_clock::now();
    }
}

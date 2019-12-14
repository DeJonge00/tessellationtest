#ifndef GAMELOOPTHREAD_H
#define GAMELOOPTHREAD_H

#include <QThread>
#include <chrono>

#include "gamewindow.h"
#include "mainwindow.h"


class GameLoopThread : public QThread
{
    Q_OBJECT
public:
    GameLoopThread(MainWindow *ms, GameWindow *gw);

    bool running;

    void run() override;

private:
    MainWindow *ui;
    GameWindow *gameWindow;
    FPScounter *fpsCounter;

};

#endif // GAMELOOPTHREAD_H

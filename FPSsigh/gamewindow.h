#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QThread>

#include "rendering/renderer.h"


class GameWindow : public QOpenGLWidget
{
public:
    GameWindow(QWidget *Parent = 0);
    ~GameWindow();

    Renderer* gameRenderer;
    bool paused;
    bool running;

protected:
    void initializeGL();
    void resizeGL(int newWidth, int newHeight);
    void paintGL();

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    void switchMouseEnabled();
    bool mouseTracking;

};

#endif // GAMEWINDOW_H

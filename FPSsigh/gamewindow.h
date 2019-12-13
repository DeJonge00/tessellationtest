#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLWidget>
#include <QMouseEvent>

#include "rendering/renderer.h"

class GameWindow : public QOpenGLWidget
{
public:
    GameWindow(QWidget *Parent = 0);
    ~GameWindow();
    Renderer *gameRenderer;

protected:
    void initializeGL();
    void resizeGL(int newWidth, int newHeight);
    void paintGL();

    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

private:
    void initDebugger();
    QOpenGLDebugLogger *debugLogger;
};

#endif // GAMEWINDOW_H

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
    void keyPressEvent(QKeyEvent* event);

protected:
    void initializeGL();
    void resizeGL(int newWidth, int newHeight);
    void paintGL();

private:

    void initDebugger();
    QOpenGLDebugLogger *debugLogger;
};

#endif // GAMEWINDOW_H

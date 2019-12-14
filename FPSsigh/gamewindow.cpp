#include <QTime>

#include "gamewindow.h"
#include "logic/gameloopthread.h"


GameWindow::GameWindow(QWidget *Parent) : QOpenGLWidget(Parent),
    mouseTracking(true)
{
    setEnabled(true);
    switchMouseEnabled();
}

GameWindow::~GameWindow() {

}

// Override QOpenGLWidget functions
void GameWindow::initializeGL() {
    makeCurrent();
    gameRenderer = new Renderer();
}

void GameWindow::resizeGL(int newWidth, int newHeight) {
    gameRenderer->gameCharacter->changeDispRatio((float)newWidth/newHeight);
}

void GameWindow::paintGL() {
//    qDebug() << "PaintGL";
    gameRenderer->render();
}

void GameWindow::keyPressEvent(QKeyEvent* event) {
    if (event->key() == 'M') {
        switchMouseEnabled();
    }
    gameRenderer->gameCharacter->handleKeypress(event->key(), true);
}

void GameWindow::switchMouseEnabled() {
    mouseTracking = !mouseTracking;
    setMouseTracking(mouseTracking);
    if (mouseTracking) {
        setCursor(Qt::BlankCursor);
    } else {
        setCursor(Qt::ArrowCursor);
    }
}

void GameWindow::keyReleaseEvent(QKeyEvent* event) {
    gameRenderer->gameCharacter->handleKeypress(event->key(), false);
}

void GameWindow::mousePressEvent(QMouseEvent* event) {
    setFocus();
}

void GameWindow::wheelEvent(QWheelEvent* event) {
    gameRenderer->gameCharacter->changeFoV(-event->delta() / 12.0);
}

void GameWindow::mouseMoveEvent(QMouseEvent *event) {
    if (this->hasFocus()) {
        gameRenderer->gameCharacter->handleMouse(event->pos());
        QCursor::setPos(pos().x()+width()/2, pos().y() + height()/2);
    }
}

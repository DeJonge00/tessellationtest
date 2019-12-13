#include "gamewindow.h"

GameWindow::GameWindow(QWidget *Parent) : QOpenGLWidget(Parent)
{

}

GameWindow::~GameWindow() {
    debugLogger->stopLogging();

    delete debugLogger;
}

void GameWindow::initDebugger() {
    debugLogger = new QOpenGLDebugLogger();
    connect( debugLogger, SIGNAL( messageLogged( QOpenGLDebugMessage ) ), this, SLOT( onMessageLogged( QOpenGLDebugMessage ) ), Qt::DirectConnection );

    if ( debugLogger->initialize() ) {
        qDebug() << ":: Logging initialized";
        debugLogger->startLogging( QOpenGLDebugLogger::SynchronousLogging );
        debugLogger->enableMessages();
    }
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
    qDebug() << "PaintGL";
    gameRenderer->render();
}

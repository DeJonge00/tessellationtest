#include "rendering/renderer.h"

Renderer::Renderer(QWidget *Parent) : QOpenGLWidget(Parent)
{
    qDebug() << "Renderer constructor";
    gameWorld = new World();
    gameCharacter = new Character();
}

Renderer::~Renderer()
{
    qDebug() << "Renderer destructor";
    glDeleteBuffers(1, &coordinatesBO);
    glDeleteBuffers(1, &normalsBO);

    debugLogger->stopLogging();

    delete debugLogger;
    delete mainShaderProgram;
}

void Renderer::createShaderPrograms() {
    mainShaderProgram = new QOpenGLShaderProgram();
    mainShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader_t.glsl");
    mainShaderProgram->addShaderFromSourceFile(QOpenGLShader::TessellationControl, ":/shaders/tcs.glsl");
    mainShaderProgram->addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation, ":/shaders/tes.glsl");
    mainShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader.glsl");

    mainShaderProgram->link();
}

void Renderer::createBuffers() {
    glGenVertexArrays(1, &worldVAO);
    glBindVertexArray(worldVAO);

    glGenBuffers(1, &coordinatesBO);
    glBindBuffer(GL_ARRAY_BUFFER, coordinatesBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &normalsBO);
    glBindBuffer(GL_ARRAY_BUFFER, normalsBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}

void Renderer::updateBuffers() {

    QVector<QVector3D> vertices = QVector<QVector3D>();
    QVector<QVector3D> normals = QVector<QVector3D>();

    gameWorld->getWorldObjects(vertices, normals);
    qDebug() << "updateBuffers:" << vertices.first() << normals.first();

    glBindBuffer(GL_ARRAY_BUFFER, coordinatesBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normalsBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*normals.size(), normals.data(), GL_DYNAMIC_DRAW);

    worldIBOsize = vertices.size();

    update();
}

void Renderer::updateUniforms() {
    // update matrices
}

void Renderer::initDebugger() {
    debugLogger = new QOpenGLDebugLogger();
    connect( debugLogger, SIGNAL( messageLogged( QOpenGLDebugMessage ) ), this, SLOT( onMessageLogged( QOpenGLDebugMessage ) ), Qt::DirectConnection );

    if ( debugLogger->initialize() ) {
        qDebug() << ":: Logging initialized";
        debugLogger->startLogging( QOpenGLDebugLogger::SynchronousLogging );
        debugLogger->enableMessages();
    }
}

// Override QOpenGLWidget functions
void Renderer::initializeGL() {
    initializeOpenGLFunctions();

    QString glVersion;
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    qDebug() << ":: Using OpenGL" << qPrintable(glVersion);

    makeCurrent();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
    // Default is GL_LESS
    glDepthFunc(GL_LEQUAL);

    GLint MaxPatchVertices = 0;
    glGetIntegerv(GL_MAX_PATCH_VERTICES, &MaxPatchVertices);
    qDebug() << "Maximum patch vertices:" << MaxPatchVertices;
    glPatchParameteri(GL_PATCH_VERTICES, 4);

    createShaderPrograms();
    createBuffers();
}

void Renderer::resizeGL(int newWidth, int newHeight) {
    gameCharacter->changeDispRatio((float)newWidth/newHeight);
}

void Renderer::paintGL() {

}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class GameLoopThread;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void startGameLoop();
    void setFpsLabel(int fps);

private slots:
    void on_pushButton_clicked();
    void on_fovSpinbox_valueChanged(int value);

    void on_positionX_valueChanged(double value);
    void on_positionY_valueChanged(double value);
    void on_positionZ_valueChanged(double value);

    void on_viewPointX_valueChanged(double value);
    void on_viewPointY_valueChanged(double value);

    void on_simpleShaderCheckbox_stateChanged(int value);
    void on_tessShaderCheckbox_stateChanged(int value);
    void on_tessInnerSpinbox_valueChanged(int value);
    void on_tessOuterSpinbox_valueChanged(int value);

    void on_scaleSpinbox_valueChanged(double value);

    void on_respawnButton_clicked();

    void on_maxFps_valueChanged(int arg1);

    void on_simpleWireframe_stateChanged(int arg1);

    void on_tessWireframe_stateChanged(int arg1);

    void on_bicubicInterpolation_stateChanged(int arg1);

    void on_phase_valueChanged(double arg1);

    void on_normalShader_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    GameLoopThread* gameLoopThread;

public slots:
    void gameLoopQuit();
};
#endif // MAINWINDOW_H

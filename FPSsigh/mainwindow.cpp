#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->GameWidget->update();
}

void MainWindow::on_fovSpinbox_valueChanged(int value)
{
    ui->GameWidget->gameRenderer->gameCharacter->setFoV(value);
    ui->GameWidget->gameRenderer->uniformUpdateRequired = true;
    ui->GameWidget->update();
}

void MainWindow::on_positionX_valueChanged(double value)
{
    ui->GameWidget->gameRenderer->gameCharacter->setXPosition(value);
    ui->GameWidget->gameRenderer->uniformUpdateRequired = true;
    ui->GameWidget->update();
}

void MainWindow::on_positionY_valueChanged(double value)
{
    ui->GameWidget->gameRenderer->gameCharacter->setYPosition(value);
    ui->GameWidget->gameRenderer->uniformUpdateRequired = true;
    ui->GameWidget->update();
}

void MainWindow::on_positionZ_valueChanged(double value)
{
    ui->GameWidget->gameRenderer->gameCharacter->setZPosition(value);
    ui->GameWidget->gameRenderer->uniformUpdateRequired = true;
    ui->GameWidget->update();
}

void MainWindow::on_viewPointX_valueChanged(double value)
{
    ui->GameWidget->gameRenderer->gameCharacter->setRotationAngleX(value);
    ui->GameWidget->gameRenderer->uniformUpdateRequired = true;
    ui->GameWidget->update();
}

void MainWindow::on_viewPointY_valueChanged(double value)
{
    ui->GameWidget->gameRenderer->gameCharacter->setRotationAngleY(value);
    ui->GameWidget->gameRenderer->uniformUpdateRequired = true;
    ui->GameWidget->update();
}

void MainWindow::on_simpleShaderCheckbox_stateChanged(int value)
{
    ui->GameWidget->gameRenderer->enableSimpleShader = value == 2;
    ui->GameWidget->update();
}

void MainWindow::on_tessShaderCheckbox_stateChanged(int value)
{
    ui->GameWidget->gameRenderer->enableTessShader = value == 2;
    ui->GameWidget->update();
}

void MainWindow::on_tessInnerSpinbox_valueChanged(int value)
{
    ui->GameWidget->gameRenderer->tessellationInner = value;
    ui->GameWidget->update();
}

void MainWindow::on_tessOuterSpinbox_valueChanged(int value)
{
    ui->GameWidget->gameRenderer->tessellationOuter = value;
    ui->GameWidget->update();
}

void MainWindow::on_scaleSpinbox_valueChanged(double value)
{
    ui->GameWidget->gameRenderer->scale = value;
    ui->GameWidget->gameRenderer->uniformUpdateRequired = true;
    ui->GameWidget->update();
}

void MainWindow::on_respawnButton_clicked()
{
    ui->GameWidget->gameRenderer->gameCharacter->setPosition(QVector3D(0, 2, 0));
    ui->GameWidget->gameRenderer->gameCharacter->setRotation(QVector2D(0, -1));
    ui->GameWidget->update();
}

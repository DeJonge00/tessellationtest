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
    ui->GameWidget->gameRenderer->gameCharacter->changeFoV(value);
    ui->GameWidget->gameRenderer->uniformUpdateRequired = true;
    ui->GameWidget->update();
}

void MainWindow::on_scaleSpinbox_valueChanged(int value)
{
    ui->GameWidget->gameRenderer->scale = value;
    ui->GameWidget->gameRenderer->uniformUpdateRequired = true;
    ui->GameWidget->update();
}

void MainWindow::on_positionX_valueChanged(double value)
{
    ui->GameWidget->gameRenderer->gameCharacter->changeXPosition(value);
    ui->GameWidget->gameRenderer->uniformUpdateRequired = true;
    ui->GameWidget->update();
}

void MainWindow::on_positionY_valueChanged(double value)
{
    ui->GameWidget->gameRenderer->gameCharacter->changeYPosition(value);
    ui->GameWidget->gameRenderer->uniformUpdateRequired = true;
    ui->GameWidget->update();
}

void MainWindow::on_positionZ_valueChanged(double value)
{
    ui->GameWidget->gameRenderer->gameCharacter->changeZPosition(value);
    ui->GameWidget->gameRenderer->uniformUpdateRequired = true;
    ui->GameWidget->update();
}

void MainWindow::on_viewPointX_valueChanged(double value)
{
    ui->GameWidget->gameRenderer->gameCharacter->changeRotationAngleX(value);
    ui->GameWidget->gameRenderer->uniformUpdateRequired = true;
    ui->GameWidget->update();
}

void MainWindow::on_viewPointY_valueChanged(double value)
{
    ui->GameWidget->gameRenderer->gameCharacter->changeRotationAngleY(value);
    ui->GameWidget->gameRenderer->uniformUpdateRequired = true;
    ui->GameWidget->update();
}

void MainWindow::on_viewPointZ_valueChanged(double value)
{
    ui->GameWidget->gameRenderer->gameCharacter->changeRotationAngleZ(value);
    ui->GameWidget->gameRenderer->uniformUpdateRequired = true;
    ui->GameWidget->update();
}

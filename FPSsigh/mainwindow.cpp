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

void MainWindow::on_angleSpinbox_valueChanged(int value)
{
    ui->GameWidget->gameRenderer->gameCharacter->changeRotationAngle(value);
    ui->GameWidget->gameRenderer->uniformUpdateRequired = true;
    ui->GameWidget->update();
}

void MainWindow::on_scaleSpinbox_valueChanged(int value)
{
    ui->GameWidget->gameRenderer->scale = value;
    ui->GameWidget->gameRenderer->uniformUpdateRequired = true;
    ui->GameWidget->update();
}

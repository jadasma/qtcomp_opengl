#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_verticalSlider_actionTriggered(int action)
{
ui->widget->rotate_x=ui->verticalSlider->value();
ui->widget->update();
}

void MainWindow::on_verticalSlider_2_actionTriggered(int action)
{
    ui->widget->rotate_y=ui->verticalSlider_2->value();
    //this->update();
ui->widget->update();
}

void MainWindow::on_verticalSlider_3_actionTriggered(int action)
{
    ui->widget->rotate_z=ui->verticalSlider_3->value();
    //this->update();
ui->widget->update();
}

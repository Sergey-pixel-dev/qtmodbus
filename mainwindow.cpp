#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    my_core = new core();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_send_clicked()
{
    ui->spin_set_heater_ccurrent->value();

}

void MainWindow::on_pushButton_clicked() {}

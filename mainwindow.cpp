#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    modbus = NULL;
}

MainWindow::~MainWindow()
{
    if (modbus != NULL)
        delete modbus;
    delete ui;
}

void MainWindow::on_button_send_clicked()
{
    ui->spin_set_heater_ccurrent->value();

}


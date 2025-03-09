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
    my_core->connect();
    uint16_t a[4];
    my_core->modbus->ReadRegisters(41005, 4, a);
}

void MainWindow::on_pushButton_clicked()
{
    my_core->conn_params = new conn_struct{.type = 1,
                                           .com_params = new com_struct{
                                               .device = "/dev/ttyUSB0",
                                               .baud_rate = 19200,

                                               .polarity = 'N',
                                               .data_bits = 8,
                                               .stop_bits = 1,
                                           }};
    my_core->open();
}

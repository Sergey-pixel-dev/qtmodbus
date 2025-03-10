#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    my_core = new core();
    my_core->conn_params = new conn_struct{.type = 1,
                                           .com_params = new com_struct{
                                               .device = "/dev/ttyUSB0",
                                               .baud_rate = 19200,

                                               .polarity = 'N',
                                               .data_bits = 8,
                                               .stop_bits = 1,
                                           }};
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_send_clicked()
{
    uint16_t a[4]{1, 2, 3, 4};
    my_core->modbus->WriteRegisters(41005, 2, a);
}

void MainWindow::on_button_connect_clicked()
{
    if (my_core->status != CONNECTED) {
        if (!my_core->open() && !my_core->connect()) {
            ui->button_connect->setText("Отключить");
            if (!my_core->HasBeenConnected()) {
                UpdateValues();
            }
        }
    } else if (my_core->status == CONNECTED) {
        my_core->close();
        ui->button_connect->setText("Подключить");
    }
}

void MainWindow::UpdateValues()
{
    ui->label_heater_current->setText(
        QString::number(my_core->heater->Heater_Current / 1000.0, 'g', 2));
}

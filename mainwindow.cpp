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

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));

    msgBox = new QMessageBox();

    ui->label_heater_current->setDisabled(true);
    ui->label_heater_voltage->setDisabled(true);

    ui->label_control_12v->setDisabled(true);
    ui->label_control_27v->setDisabled(true);
    ui->label_internal_3_3v->setDisabled(true);
    ui->label_internal_5v->setDisabled(true);

    ui->button_send->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete my_core;
    delete timer;
}

void MainWindow::on_button_send_clicked()
{
    if (my_core->status == CONNECTED) {
        my_core->heater->Set_Current_Heater = ui->spin_set_heater_current->value() * 1000;
        my_core->SetValues();
    }
}

void MainWindow::on_button_connect_clicked()
{
    if (my_core->status != CONNECTED) {
        int a = my_core->open();
        if (!a) {
            a = my_core->connect();
            if (!a) {
                HasBeenConnected();
                ui->button_connect->setText("Отключить");
            } else
                showErrMsgBox("Ошибка подключения", my_core->modbus->GetErrMsg(a));

        } else
            showErrMsgBox("Ошибка подключения", my_core->modbus->GetErrMsg(a));

    } else if (my_core->status == CONNECTED) {
        HasBeenDisconnected();
        ui->button_connect->setText("Подключить");
    }
}

void MainWindow::PrintValuesFromCore()
{
    ui->label_heater_current->setText(
        QString::number(my_core->heater->Heater_Current / 1000.0, 'f', 3));
    ui->label_heater_voltage->setText(
        QString::number(my_core->heater->Heater_Voltage / 1000.0, 'f', 3));

    ui->label_control_12v->setText(QString::number(my_core->heater->control_12v / 1000.0, 'f', 3));
    ui->label_control_27v->setText(QString::number(my_core->heater->control_27v / 1000.0, 'f', 3));
    ui->label_internal_3_3v->setText(
        QString::number(my_core->heater->internal_3_3v / 1000.0, 'f', 2));
    ui->label_internal_5v->setText(QString::number(my_core->heater->internal_5v / 1000.0, 'f', 3));
}

void MainWindow::HasBeenConnected()
{
    ui->button_send->setEnabled(true);

    if (!my_core->UpdateValues()) {
        ui->label_heater_current->setEnabled(true);
        ui->label_heater_voltage->setEnabled(true);

        ui->label_control_12v->setEnabled(true);
        ui->label_control_27v->setEnabled(true);
        ui->label_internal_3_3v->setEnabled(true);
        ui->label_internal_5v->setEnabled(true);

        PrintValuesFromCore();
        timer->start(1000);
    }
}

void MainWindow::HasBeenDisconnected()
{
    timer->stop();
    ui->label_heater_current->setDisabled(true);
    ui->label_heater_voltage->setDisabled(true);

    ui->label_control_12v->setDisabled(true);
    ui->label_control_27v->setDisabled(true);
    ui->label_internal_3_3v->setDisabled(true);
    ui->label_internal_5v->setDisabled(true);

    ui->button_send->setDisabled(true);

    my_core->close();
}

void MainWindow::slotTimerAlarm()
{
    if (my_core->status == CONNECTED)
        if (!my_core->UpdateValues())
            PrintValuesFromCore();
}
void MainWindow::showErrMsgBox(const char *title, const char *msg)
{
    msgBox->setWindowTitle(title);
    msgBox->setText(msg);
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setStyleSheet("QLabel{font-size: 16px;}");
    int ret = msgBox->exec();

    if (ret == QMessageBox::Ok) {
        // мб что-то добавить
    }
}

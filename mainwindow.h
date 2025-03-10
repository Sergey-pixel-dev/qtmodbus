#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include "core.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_send_clicked();
    void slotTimerAlarm();
    void on_button_connect_clicked();

private:
    void PrintValuesFromCore();
    void HasBeenConnected();
    void HasBeenDisconnected();
    QTimer *timer;
    Ui::MainWindow *ui;
    core *my_core;
    QMessageBox *msgBox;
    void showErrMsgBox(const char *title, const char *msg);
};
#endif // MAINWINDOW_H

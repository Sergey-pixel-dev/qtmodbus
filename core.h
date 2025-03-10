#ifndef CORE_H
#define CORE_H
#include "qtmodbus.h"

enum STATUS_ENUM {
    DISCONNECTED,
    CONNECTED,
    ERR,
};
struct com_struct
{
    const char *device;
    int baud_rate;
    char polarity;
    char data_bits;
    char stop_bits;
};

struct tcp_struct
{
    const char *ip;
    int port;
};
struct conn_struct
{
    int type;
    com_struct *com_params;
    tcp_struct *tcp_params;
};

struct heater_struct
{
    int Set_Current_Heater;
    int Heater_Current;
    int Heater_Voltage;
    int control_27v;
    int control_12v;
    int control_minus_5v;
    int internal_3_3v;
    int internal_3_3va;
    int internal_5v;
};

class core
{
private:
public:
    STATUS_ENUM status;
    heater_struct *heater;
    conn_struct *conn_params;
    int open();
    int connect();
    void close();
    int HasBeenConnected();
    int UpdateValues();
    qtmodbus *modbus;

    core();
    ~core();
};

#endif // CORE_H

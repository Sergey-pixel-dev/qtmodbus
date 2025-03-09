#ifndef CORE_H
#define CORE_H
#include "qtmodbus.h"

enum STATUS_ENUM {
    DISCONNECTED,
    CONNECTED,
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

class core
{
private:
    STATUS_ENUM status;

public:
    conn_struct *conn_params;
    int open();
    int connect();
    qtmodbus *modbus;

    core();
    ~core();
};

#endif // CORE_H

#include "core.h"

core::core()
{
    this->modbus = NULL;
    this->status = DISCONNECTED;
}
core::~core()
{
    if (modbus != NULL)
        delete modbus;
}

int core::open(connection_struct *con_params)
{
    int feedback = -1;
    modbus = new qtmodbus(con_params->type);
    if (con_params->type == 0 || con_params->type == 1) {
        if (con_params->com_params == NULL || con_params->com_params->device == NULL)
            return -1;
        feedback = modbus->COM_Init(con_params->com_params->device,
                                    con_params->com_params->baud_rate,
                                    con_params->com_params->polarity,
                                    con_params->com_params->data_bits,
                                    con_params->com_params->stop_bits);
    }
    if (con_params->type == 2) {
        if (con_params->tcp_params == NULL || con_params->tcp_params->ip == NULL)
            return -1;

        feedback = modbus->TCP_Init(con_params->tcp_params->ip, con_params->tcp_params->port);
    }
    if (feedback == 0) {
        this->status = CONNECTED;
        return 0;
    }
    this->status = DISCONNECTED;
    return -1;
}

int core::connect()
{
    return 0;
}

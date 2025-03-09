#include "core.h"

core::core()
{
    this->modbus = NULL;
    this->status = DISCONNECTED;
    this->conn_params = NULL;
}
core::~core()
{
    if (modbus != NULL)
        delete modbus;
}

int core::open()
{
    if (this->conn_params == NULL) {
        return -1;
    }
    int feedback = -1;
    modbus = new qtmodbus(this->conn_params->type);
    if (this->conn_params->type == 0 || this->conn_params->type == 1) {
        if (this->conn_params->com_params == NULL || this->conn_params->com_params->device == NULL)
            return -1;
        feedback = modbus->COM_Init(this->conn_params->com_params->device,
                                    this->conn_params->com_params->baud_rate,
                                    this->conn_params->com_params->polarity,
                                    this->conn_params->com_params->data_bits,
                                    this->conn_params->com_params->stop_bits);
    }
    if (this->conn_params->type == 2) {
        if (this->conn_params->tcp_params == NULL || conn_params->tcp_params->ip == NULL)
            return -1;

        feedback = modbus->TCP_Init(conn_params->tcp_params->ip, conn_params->tcp_params->port);
    }
    if (feedback == 0) {
        modbus->SetSlave(10);
        this->status = CONNECTED;
        return 0;
    }
    this->status = DISCONNECTED;
    return -1;
}

int core::connect()
{
    if (modbus == NULL)
        return -1;
    return modbus->Connect();
}

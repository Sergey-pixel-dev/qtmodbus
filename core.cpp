#include "core.h"

core::core()
{
    this->modbus = NULL;
    this->status = DISCONNECTED;
    this->conn_params = NULL;
    this->heater = new heater_struct{
        .Set_Current_Heater = 0,
        .Heater_Current = 0,
        .Heater_Voltage = 0,
        .control_27v = 0,
        .control_12v = 0,
        .control_minus_5v = 0,
        .internal_3_3v = 0,
        .internal_3_3va = 0,
        .internal_5v = 0,
    };
}
core::~core()
{
    if (modbus != NULL)
        delete modbus;
    if (conn_params != NULL) {
        if (conn_params->com_params != NULL)
            delete conn_params->com_params;
        if (conn_params->tcp_params != NULL)
            delete conn_params->tcp_params;
        delete conn_params;
    }
    delete heater;
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
        return 0;
    }
    this->status = ERR;
    return -1;
}

int core::connect()
{
    if (modbus == NULL)
        return -1;

    if (modbus->Connect() == 0) {
        this->status = CONNECTED;
        return 0;
    }
    this->status = ERR;
    return -1;
}

void core::close()
{
    if (modbus == NULL)
        return;
    this->status = DISCONNECTED;
    modbus->Close();
}

int core::HasBeenConnected()
{
    if (!UpdateValues())
        return 0;
    return -1;
}

int core::UpdateValues()
{
    int feedback = 0;
    uint16_t buffer[16];

    //read Heater current and voltage
    if (modbus->ReadRegisters(41007, 2, (void *) buffer) != 2) {
        return -1;
    }
    //read different voltage
    if (modbus->ReadRegisters(41018, 6, (void *) (buffer + 2)) != 6) {
        return -1;
    }
    heater->Heater_Current = buffer[0];
    heater->Heater_Voltage = buffer[1];
    heater->control_27v = buffer[2];
    heater->control_12v = buffer[3];
    heater->control_minus_5v = buffer[4];
    heater->internal_3_3v = buffer[5];
    heater->internal_3_3va = buffer[6];
    heater->internal_5v = buffer[7];

    return 0;
}

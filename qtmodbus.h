#ifndef QTMODBUS_H
#define QTMODBUS_H
#include "modbus/modbus.h"

#define COILS_START 00001
#define DISCRETE_START 10001
#define INPUT_REG_START 30001 //переделать потом, так как между секциями есть интервал в 2 адреса
#define HOLDING_REG_START 40001
#define MAX_ADDR 49999

//НЕТ ПОДДЕРЖКИ ASCII - ИСПРАВИТЬ!
//Init - то же самое, что и connect!! ИСПРАВИТЬ!!

//enum MODBUS_ADU_TYPE { ASCII, RTU, TCP };

class qtmodbus
{
private:
    int adu_type;
    modbus_t *ctx;

public:
    qtmodbus(int adu_type);
    int COM_Init(const char *device, int baud_rate, char polarity, char dataBits, char stopBits);
    int TCP_Init(const char *ip, int port);

    int WriteRegisters(int addr, int nb, const void *data);
    int ReadRegisters(int addr, int nb, void *dest);
};

#endif // QTMODBUS_H

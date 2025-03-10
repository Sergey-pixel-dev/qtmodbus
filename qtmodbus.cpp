#include "qtmodbus.h"

qtmodbus::qtmodbus(int adu_type)
{
    this->adu_type = adu_type;
    this->ctx = NULL;
}

int qtmodbus::COM_Init(
    const char *device, int baud_rate, char polarity, char data_bits, char stop_bits)
{
    errno = 0;
    if (this->adu_type != 0 && this->adu_type != 1) {
        return 1;
    }
    this->ctx = modbus_new_rtu(device, baud_rate, polarity, data_bits, stop_bits);
    if (ctx == NULL) {
        return errno;
    }
    return 0;
}

int qtmodbus::TCP_Init(const char *ip, int port)
{
    errno = 0;
    if (this->adu_type != 2)
        return 1;

    this->ctx = modbus_new_tcp(ip, port);
    if (ctx == NULL)
        return 2;
    return 0;
}
//ПРОБЛЕМА - ВОВЗРАЩАЕТ КОЛ-ВО ЗАПИСАННЫХ, НО НЕ ВОЗВРАЩАЕТ НОМЕР ОШИБКИ
//ТАК КАК КОЛ-ВО ЗАПИСАННЫХ == НОМЕР ОШИБКИ, ДЛЯ ТОГО, КТО ВЫЗЫВАЕТ ФУНКЦИЮ
//ПОДУМАТЬ, КАК ОБРАБОТАТЬ ОШИБКИ
int qtmodbus::WriteRegisters(int addr, int nb, const void *src)
{
    if (addr < 0 || addr > MAX_ADDR || addr >= DISCRETE_START && addr < HOLDING_REG_START) {
        return -1;
    }
    if (addr < DISCRETE_START) {
        modbus_write_bits(this->ctx, addr, nb, (uint8_t *) src);
    }

    return modbus_write_registers(this->ctx, addr, nb, (uint16_t *) src);
}

int qtmodbus::ReadRegisters(int addr, int nb, void *dest)
{
    if (addr < 0 || addr > MAX_ADDR) {
        return -1;
    } else if (addr < DISCRETE_START) {
        return modbus_read_bits(this->ctx, addr, nb, (uint8_t *) dest);
    } else if (addr < INPUT_REG_START) {
        return modbus_read_input_bits(this->ctx, addr, nb, (uint8_t *) dest);
    } else if (addr < HOLDING_REG_START)
        return modbus_read_input_registers(this->ctx, addr, nb, (uint16_t *) dest);
    return modbus_read_registers(this->ctx, addr, nb, (uint16_t *) dest);
}

int qtmodbus::Connect()
{
    errno = 0;
    modbus_connect(this->ctx);
    return errno;
}

void qtmodbus::Close()
{
    if (this->ctx == NULL)
        return;
    modbus_close(this->ctx);
    modbus_free(this->ctx);
}

int qtmodbus::SetSlave(int addr)
{
    errno = 0;
    modbus_set_slave(this->ctx, addr);
    return errno;
}

const char *qtmodbus::GetErrMsg(int err)
{
    return modbus_strerror(err);
}

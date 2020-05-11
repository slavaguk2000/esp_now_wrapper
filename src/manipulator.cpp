#include "manipulator.h"
#include "wrapper.h"
#include "common.h"
#include <Servo.h>

Manipulator mn;
Servo srx, sry;  
#define SERVOX_PIN 8
#define SERVOY_PIN 9

void recieve_data(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
    mn.recieve_foreign_command(mac_addr, data, data_len);
}

int check_borders(int value, int correction){
    value += correction;
    if (value < SER_MIN) value = SER_MIN;
    if (value > SER_MAX) value = SER_MAX;
    return value;
}

void Manipulator::recieve_foreign_command(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
    if (data_len == COMMAND_LEN && !memcmp(joy_mac, mac_addr, MAC_SIZE)
        && data[0] == KEY[0]
        && data[1] == KEY[1]
        && data[4] == KEY[2]
    ){
        x = check_borders(x, data[2]);
        y = check_borders(y, data[3]);
    }
}

void Manipulator::setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    WR->add_recieve_function(recieve_data);
    srx.attach(SERVOX_PIN);
    sry.attach(SERVOY_PIN);
}

void Manipulator::loop()
{
    srx.write(x);
    sry.write(y);
    delay(1);
}


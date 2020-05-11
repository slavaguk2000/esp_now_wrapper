#include "joystick.h"
#include "wrapper.h"
#include "common.h"

#define PIN_X A3
#define PIN_Y A4
#define MIDDLE_X 523
#define MIDDLE_Y 532
#define SENSITIVITY 1
#define TIMEOUT 10

Joystick js;

void Joystick::send_command(int x, int y)
{
    uint8_t commnad[] = {KEY[0], KEY[1], x, y, KEY[2]};
    WR->send_broadcast(&commnad, sizeof(commnad));
}

void Joystick::setup()
{
    pinMode(PIN_X, INPUT);
    pinMode(PIN_Y, INPUT);
}

void Joystick::loop()
{
    int x = (analogRead(PIN_X) - MIDDLE_X) * SENSITIVITY / 100;     
    int y = (analogRead(PIN_Y) - MIDDLE_Y) * SENSITIVITY / 100;     
    if (x || y) send_command(x, y);
    delay(TIMEOUT);
}


#ifndef JOYSTICK
#define JOYSTICK

#include <stdint.h>

class Joystick{
public:
    void setup();
    void loop();
private:
    void send_command(int, int);
};

#endif //JOYSTICK

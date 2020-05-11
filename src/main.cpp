#include "joystick.h"
#include "manipulator.h"

extern Joystick js;
extern Manipulator mn;

void setup()
{
    js.setup();
    //mn.setup();
}

void loop()
{
    js.loop();
    //mn.loop();
}


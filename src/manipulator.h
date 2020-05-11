#ifndef MANIPULATOR
#define MANIPULATOR

#include <stdint.h>

#define SER_MAX 180
#define SER_MIN 0

class Manipulator{
public:
    void setup();
    void loop();
    void recieve_foreign_command(const uint8_t *mac_addr, const uint8_t *data, int data_len);
private:
    uint8_t joy_mac[MAC_SIZE] = {0x24, 0x6F, 0x28, 0x9D, 0x42, 0x14};
    int x = (SER_MAX - SER_MIN) * 10 / 2;
    int y = (SER_MAX - SER_MIN) * 10 / 2;
};

#endif //MANIPULATOR

#ifndef VIBROBOT
#define VIBROBOT

#include <stdint.h>

const int MAC_SIZE = 6;

class Vibrobot{
public:
    void setup();
    void loop();
    void recieve_foreign_command(const uint8_t *mac_addr, const uint8_t *data, int data_len);
private:
    void timeout();
    void send_leds_changed();
    void set_leds();
    void reset_demo();
    const int client_status_TTL = 2;
    int is_client;
    uint16_t counter = 0;
    uint8_t red, green, blue, i = 5;
    uint8_t my_mac[MAC_SIZE];
};

#endif //VIBROBOT

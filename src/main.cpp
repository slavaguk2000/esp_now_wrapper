#include <esp_now.h>
#include <WiFi.h>
uint8_t my_mac1[] = {0x24, 0x6F, 0x28, 0x9D, 0x62, 0xFC};
uint8_t my_mac2[] = {0x24, 0x6F, 0x28, 0x9D, 0x42, 0x14};
uint8_t mac[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

#include "initializer.h"
#include "wrapper.h"

void setup_send()
{ 
    Serial.begin(9600);
//    Initialiser::initialise();
    
}

void loop_send() {
    char h_str[] = "HEllo, WOrld";
    Serial.println(WR->send_broadcast(h_str, sizeof(h_str)));
    delay(1000);
}

void get_message(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
    for(int i = 0; i < 6; i ++)
    {
        Serial.print(mac_addr[i]);
        Serial.print("-");
    }
    Serial.print(": ");
    for(int i = 0; i < data_len; i++)
    {
        Serial.print((char)data[i]);
    }
}

void setup_recieve()
{ 
    Serial.begin(9600);
    WR->add_recieve_function(get_message);
//    Initialiser::initialise();
    
}
void loop_recieve() {
    delay(5000);
    Serial.println("5 sec");
}

void setup()
{
    // setup_send();
    setup_recieve();
}

void loop()
{
    // loop_send();
    loop_recieve();
}
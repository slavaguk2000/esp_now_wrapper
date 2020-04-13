#include <esp_now.h>
#include <WiFi.h>
#include "wrapper.h"
#include "vibrobot.h"

extern Vibrobot vb;

void setup_send()
{ 
    Serial.begin(9600);    
}

void loop_send() {
    int a = 2;
    Serial.println(WR->send_broadcast(&a, sizeof(a)));
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
        Serial.print((int)data[i]);
        Serial.print(" ");
    }
    Serial.println();
}

void setup_recieve()
{ 
 
    WR->add_recieve_function(get_message);
//    Initialiser::initialise();
    
}
void loop_recieve() {
    delay(5000);
    Serial.println("5 sec");
}
void setup()
{
    vb.setup();
    //  setup_send();
    // setup_recieve();
}

void loop()
{
    vb.loop();
    //  loop_send();
    // loop_recieve();
}

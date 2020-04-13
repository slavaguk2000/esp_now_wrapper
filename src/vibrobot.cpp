#include "vibrobot.h"
#include <esp_now.h>
#include <WiFi.h>
#include "wrapper.h"

#include <Adafruit_NeoPixel.h>

#define PIN 26

const int del_time = 2000;

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(4, PIN, NEO_GRB + NEO_KHZ800);

Vibrobot vb;

void Vibrobot::send_leds_changed()
{
    uint8_t commnad[] = {i, red, green, blue};
    WR->send_broadcast(&commnad, sizeof(commnad));
}

void recieve_data(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
    vb.recieve_foreign_command(mac_addr, data, data_len);
}


void Vibrobot::reset_demo()
{
	i = 5;
	red = green = blue = 20;
}

void Vibrobot::recieve_foreign_command(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
    if (data_len == 4 && memcmp(my_mac, mac_addr, MAC_SIZE) < 0){
        is_client = client_status_TTL;
        i = data[0];
        red = data[1];
        green = data[2];
        blue = data[3];     
        counter = del_time;      
    }
}

void Vibrobot::set_leds()
{
    send_leds_changed();
    pixels.setPixelColor(i % 4, pixels.Color(red, 0, 0)); 
	pixels.setPixelColor((i-1) % 4, pixels.Color(0, green, 0));
	pixels.setPixelColor((i-2) % 4, pixels.Color(0, 0, blue));
	pixels.setPixelColor((i-3) % 4, pixels.Color(red, green, blue));
	pixels.show();
    digitalWrite(LED_BUILTIN, i%2?HIGH:LOW);
}

void Vibrobot::setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    is_client = false;
    memcpy(my_mac, WR->get_my_mac(), MAC_SIZE);
    WR->add_recieve_function(recieve_data);
    pixels.begin(); // This initializes the NeoPixel library.
	pixels.setBrightness(20);
	reset_demo();
}

void Vibrobot::loop()
{
    if (counter >= del_time){
        counter = 0;
        if (is_client){
            is_client--;
            if (is_client < 0) is_client = false;
        }
        else{
            i++;
            red++;
            green++;
            blue++;
            if(i > 120) {
                reset_demo();
            }
        }  
        set_leds();  
    }    
    counter++;
    delay(1);
}


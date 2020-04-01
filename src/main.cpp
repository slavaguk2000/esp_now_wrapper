#include <esp_now.h>
#include <WiFi.h>

uint8_t mac[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

void send(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    Serial.println(status);
}


void setup()
{ 

    WiFi.mode(WIFI_STA);
    Serial.begin(115200);
    WiFi.setTxPower(WIFI_POWER_2dBm);
    
    if (esp_now_init() != ESP_OK) 
    Serial.println("init fail");  
    esp_now_peer_info_t broadcast_peer = {
        {0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
        {1, 2, 3, 4},
        0,
        ESP_IF_WIFI_STA,                 
        false, 
        nullptr
    };

   if(esp_now_add_peer(&broadcast_peer) != ESP_OK){
        Serial.println("add peer fail");
    }
    esp_now_peer_info_t peer = {
        {0x24, 0x6F, 0x28, 0x9D, 0x42, 0x14},
        {1, 2, 3, 4},
        0,
        ESP_IF_WIFI_STA,                 
        false, 
        nullptr
    };

  if(esp_now_add_peer(&peer) != ESP_OK){
    Serial.println("add peer fail");
  }
   if (esp_now_register_send_cb(&send) != 0) 
  Serial.println("ERRRRROOROROROOROR"); 
}


void loop() {

    uint8_t data = 4;
    if(esp_now_send(mac, &data, 4)  !=ESP_OK){
        Serial.println("send fail");
        return;
    }

    delay(1000);
}
#include <esp_now.h>
#include "wrapper.h"
#include <list>
#include <iostream>

const uint8_t broadcast_mac[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

Wrapper::Wrapper()//broadcast_peer is embed directly without add in recieveList
{
    WiFi.mode(WIFI_STA);
    esp_now_init();
    esp_now_peer_info_t broadcast_peer = {
        {0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
        {1, 2, 3, 4},
        0,
        ESP_IF_WIFI_STA,                 
        false, 
        nullptr
    };
    esp_now_add_peer(&broadcast_peer);
}

Wrapper::~Wrapper()//should be deleted all recivers before deinit?
{
    esp_now_deinit();
}

int send_broadcast(void* data, int len)
{

}


int Wrapper::send_unicast(Reciever reciever, void* data, int len)
{
    
    typedef std::list<Reciever> rec;
    rec::iterator it = std::lower_bound(recievers.begin(), recievers.end(), reciever,
    [](Reciever left, Reciever right) -> bool {
        uint8_t* left_arr = left.getMac();
        uint8_t* right_arr = right.getMac();
        for (int i = 0; i < 6; i++) {
            if (left_arr[i] != right_arr[i])
                return left_arr[i] < right_arr[i];
        }
        return 1;
    });
    recievers.insert(it, reciever);
    esp_now_add_peer();
}


int send_broadcast(void* data, int len)
{
    if(esp_now_send(broadcast_mac, &data, 4)  !=ESP_OK){
    Serial.println("send fail");
    return;
}


}
int send_unicast(Reciever reciever, void* data, int len);
int add_recieve_function(recieve_callback callback);
int delete_recieve_function(recieve_callback callback);
int add_reciever(Reciever reciever);
int delete_reciever(Reciever reciever);
int delete_reciever(uint8_t index);
int getRecieversCount();
int contains(uint8_t index);    


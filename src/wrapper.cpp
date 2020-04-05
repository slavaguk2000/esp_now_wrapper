#include <esp_now.h>
#include "wrapper.h"
#include <list>
#include <iostream>
#include <WiFi.h>
#include <algorithm>

const uint8_t broadcast_mac[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

Wrapper::Wrapper()
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


int Wrapper::send_unicast(Reciever reciever, const void* data, int len)
{
    return esp_now_send(reciever.getMac(), (const uint8_t*)data, len);
}

int Wrapper::send_unicast(int index, void* data, int len)
{
    Reciever reciever = getReciverById(index);
    return send_unicast(reciever, data, len);
}


int Wrapper::send_broadcast(const void* data, int len)
{
    return esp_now_send(broadcast_mac, (const uint8_t*)data, len);
}

int Wrapper::add_recieve_function(recieve_callback callback)
{
    return esp_now_register_recv_cb(callback);
}
int Wrapper::delete_recieve_function() 
{
    return esp_now_unregister_recv_cb();
}

int Wrapper::getRecieversCount()
{
    return recievers.size();
}

Reciever Wrapper::getReciverById(uint8_t index)
{
    std::list<Reciever>::iterator it = std::find_if(recievers.begin(), recievers.end(),
        [index](Reciever reciever) {return reciever.getId() == index; });
    return *it;
}

bool Wrapper::contains(uint8_t index)
{
    auto it = std::find_if(recievers.begin(), recievers.end(), 
        [index](Reciever reciever) {return reciever.getId() == index;});
    return it != recievers.end();
}

uint8_t* Wrapper::getMyMac()
{
    return myMac;
}

uint8_t* Wrapper::getMyKey()
{
    return myKey;
}


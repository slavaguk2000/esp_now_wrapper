#include <esp_now.h>
#include "wrapper.h"
#include <list>
#include <iostream>
#include <WiFi.h>
#include <algorithm>

Wrapper* Wrapper::instance = 0;
const uint8_t broadcast_mac[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

Wrapper::Wrapper()
{
    WiFi.mode(WIFI_STA);
    esp_now_init();
    esp_now_peer_info_t broadcast_peer = {
        {0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
        {},
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


int Wrapper::send_unicast(Reciever* reciever, const void* data, int len)
{
    return esp_now_send(reciever->get_mac(), (const uint8_t*)data, len);
}

int Wrapper::send_unicast(int index, void* data, int len)
{
    try {
        return send_unicast(recievers.at(index), data, len);
    }
    catch (...)
    {
        return ESP_ERR_ESPNOW_ARG;
    }
}
Wrapper* Wrapper::get_instance()
{
    if (!instance)
        instance = new Wrapper();
    return instance;
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

int Wrapper::get_recievers_count()
{
    return recievers.size();
}

bool Wrapper::contains(uint8_t index)
{
    return recievers.count(index);
}

uint8_t* Wrapper::get_my_mac()
{
    return my_mac;
}

uint8_t* Wrapper::get_my_key()
{
    return my_key;
}

int Wrapper::modify_reciever(Reciever* reciever)
{
    esp_now_peer_info_t peer_info = reciever->get_info(); 
    return esp_now_mod_peer(&peer_info);
}

Reciever* Wrapper::get_reciver_by_id(uint8_t index)
{
    return recievers[index];
}

int get_free_id(const std::map<uint8_t, Reciever*> recievers)
{
    int id = 0;
    while (!recievers.count(id)) id++;
    return id;
}

int Wrapper::add_reciever(Reciever* reciever, uint8_t id)
{
    if (!recievers.count(id)) id = get_free_id(recievers);
    recievers[id] = reciever;
    return id;
}

void Wrapper::clear_recievers()
{
    recievers.clear();
}

int Wrapper::delete_reciever(Reciever* reciever)
{
    for (auto pair : recievers) {
        if (pair.second == reciever) return delete_reciever(pair.first);
    }
    return 0;
}



int Wrapper::delete_reciever(uint8_t index)
{
    return recievers.erase(index);
}



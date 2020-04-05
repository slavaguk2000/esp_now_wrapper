#include "reciever.h"
#include <stdio.h>
#include <string.h>
#include "reciever.h"
#include <esp_now.h>

void init(esp_now_peer_info_t& info, uint8_t* mac, void* key, int channel = 0, bool encrypt = false, void *priv = nullptr)
{
    memcpy(info.peer_addr, mac, 6);
    memcpy(info.lmk, key, 16);
    info.channel = channel;
    info.encrypt = encrypt;
    info.priv = priv;
    info.ifidx = ESP_IF_WIFI_STA;
}

Reciever::Reciever(uint8_t* mac, void* key, int channel, bool encrypt, void *priv)
{
    id = next_id++;
    init(info, mac, key, channel, encrypt, priv);
}

Reciever::Reciever(uint8_t* mac, int channel)
{
    id = next_id++;
    uint8_t key[16] = { 0 };
    init(info, mac, key, channel);
}

int Reciever::getId()
{
    return id;
}

uint8_t* Reciever::getMac(){
    return mac;
}

void* Reciever::getKey()
{
    return key;
}

int Reciever::getChannel()
{
    return channel;
}
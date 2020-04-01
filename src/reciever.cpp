#include "reciever.h"
#include <stdio.h>
#include <string.h>
#include "reciever.h"
#include <esp_now.h>

int Reciever::getChannel()
{
    
}

void init(esp_now_peer_info_t& info, void* mac, void* key, int channel = 0, bool encrypt = false, void *priv = nullptr)
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
    init(info, mac, key, channel, encrypt, priv);
}

Reciever::Reciever(void* mac, int channel)
{
    uint8_t key[16] = { 0 };
    init(info, mac, key, channel);
}
 
uint8_t* Reciever::getMac(){
    return mac;
}

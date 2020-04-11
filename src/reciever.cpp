#include "reciever.h"
#include "wrapper.h"
#include <stdio.h>
#include <string.h>
#include <esp_now.h>

void init(esp_now_peer_info_t& info, const uint8_t* mac, const void* key, const int channel = 0, const bool encrypt = false, void *priv = nullptr)
{
    memcpy(info.peer_addr, mac, 6);
    memcpy(info.lmk, key, 16);
    info.channel = channel;
    info.encrypt = encrypt;
    info.priv = priv;
    info.ifidx = ESP_IF_WIFI_STA;
}

Reciever::Reciever(const uint8_t* mac, const void* key, const int channel, const bool encrypt, void *priv)
{
    init(info, mac, key, channel, encrypt, priv);
}

esp_now_peer_info Reciever::get_info() const 
{
    return info;
}

Reciever::Reciever(const uint8_t* mac, const int channel)
{
    uint8_t key[16] = { 0 };
    init(info, mac, key, channel);
}

const uint8_t* Reciever::get_mac() const 
{
    return info.peer_addr;
}

const void* Reciever::get_key() const 
{
    return info.lmk;
}

int Reciever::set_key(const void* k)
{
    if (!info.encrypt) return ESP_ERR_INVALID_STATE;
    memcpy(info.lmk, k, 16);
    return Wrapper::get_instance()->modify_reciever(this);
}

const int Reciever::get_channel() const 
{
    return info.channel;
}

int Reciever::set_channel(const int ch)
{
    info.channel = ch;
    return Wrapper::get_instance()->modify_reciever(this);
}

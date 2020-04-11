#ifndef RECIEVER
#define RECIEVER
#include <esp_now.h>

class Reciever {
public:
    Reciever(const uint8_t* mac, const int channel = 0);
    Reciever(const uint8_t* mac, const void* key, const int channel = 0, const bool encrypt = false, void* priv = nullptr);
    esp_now_peer_info get_info() const;
    const uint8_t* get_mac() const;
    const void* get_key() const;
    int set_key(const void* key);
    const int get_channel() const;
    int set_channel(const int ch);

    ~Reciever();
private:
    esp_now_peer_info info;
};

#endif //RECIEVER
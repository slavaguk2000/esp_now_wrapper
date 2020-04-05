#ifndef RECIEVER
#define RECIEVER
#include <esp_now.h>

class Reciever {
public:
    Reciever(uint8_t* mac, int channel = 0);
    Reciever(uint8_t* mac, void* key, int channel = 0, bool encrypt = false, void* priv = nullptr);

    int getId();
    uint8_t* getMac();
    void* getKey();
    int setKey(void* key);
    int getChannel();
    int setChannel(int ch);

    ~Reciever();
private:
    static uint8_t next_id;
    uint8_t id;
    uint8_t mac[6];
    uint8_t key[16];
    uint8_t channel;
    esp_now_peer_info info;
};

#endif //RECIEVER
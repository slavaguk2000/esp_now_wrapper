#if !defined(RECIEVER)
#define RECIEVER
#include <esp_now.h>

class Reciever{
public:
    Reciever(void* mac, int channel = 0);
    Reciever(void* mac, void* key, int channel = 0, bool encrypt = false, void *priv = nullptr);    
    int setKey(void* key = nullptr);
    void* getKey();
    int setChannel(int ch);
    int getChannel();
    uint8_t* getMac();
    int getId();
    ~Reciever();
private:
    int id;
    uint8_t* mac();
    esp_now_peer_info info;
}

#endif
#ifndef WRAPPER
#define WRAPPER

#include "reciever.h"
#include <list>

typedef void (*recieve_callback)(const uint8_t *mac_addr, const uint8_t *data, int data_len);

class Wrapper {
public:
    Wrapper();
    ~Wrapper();
    int send_broadcast(const void* data, int len);
    int send_unicast(Reciever reciever, const void* data, int len);
    int send_unicast(int index, void* data, int len);
    int add_recieve_function(recieve_callback callback);
    int delete_recieve_function();
    int getRecieversCount();
    bool contains(uint8_t index);
    uint8_t* getMyMac();
    uint8_t* getMyKey();
    /*************************************/
    Reciever getReciverById(uint8_t index);
    int add_reciever(Reciever reciever);//chech broadcast before add
    int delete_reciever(Reciever reciever);//chech contains before delete
    int delete_reciever(uint8_t index);// -||-
private:
    uint8_t myMac[6];
    uint8_t myKey[16];
    std::list<Reciever> recievers;
};

#endif //WRAPPER
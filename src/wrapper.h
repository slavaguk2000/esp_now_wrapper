#include "reciever.h"
#include <list>

typedef void (*recieve_callback)(const uint8_t *mac_addr, const uint8_t *data, int data_len);


class Wrapper{
public:
    Wrapper();
    ~Wrapper();
    int send_broadcast(void* data, int len);
    int send_unicast(Reciever reciever, void* data, int len);
    int add_recieve_function(recieve_callback callback);
    int delete_recieve_function(recieve_callback callback);
    int add_reciever(Reciever reciever);
    int delete_reciever(Reciever reciever);
    int delete_reciever(uint8_t index);
    int getRecieversCount();
    int contains(uint8_t index);
    uint8_t* getMyMac();
private:
    uint8_t myMac[6];
    uint8_t key[16];
    std::list<Reciever> recievers;
}
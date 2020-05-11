#ifndef WRAPPER
#define WRAPPER

#include <esp_now.h>
#include <WiFi.h>
#include "reciever.h"
#include <map>

#define WR Wrapper::get_instance()

typedef void (*recieve_callback)(const uint8_t *mac_addr, const uint8_t *data, int data_len);

class Wrapper {
public:
    static Wrapper* get_instance();
    int send_broadcast(const void* data, int len);
    int send_unicast(Reciever* reciever, const void* data, int len);
    int send_unicast(int index, void* data, int len);
    int add_recieve_function(recieve_callback callback);
    int delete_recieve_function();
    int get_recievers_count();
    bool contains(uint8_t index);
    uint8_t* get_my_mac();
    uint8_t* get_my_key();
    /*************************************/
    int modify_reciever(Reciever* reciever);
    Reciever* get_reciver_by_id(uint8_t index);
    int add_reciever(Reciever* reciever, uint8_t id = 0);
    void clear_recievers();
    int delete_reciever(Reciever* reciever); //chech contains before delete
    int delete_reciever(uint8_t index);// -||-
private:
    static Wrapper* instance;
    uint8_t my_mac[6];
    uint8_t my_key[16];
    std::map<uint8_t, Reciever*> recievers;
    Wrapper();
    ~Wrapper();
    Wrapper(Wrapper const&) = delete;
    Wrapper& operator= (Wrapper const&) = delete;
};

#endif //WRAPPER

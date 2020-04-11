#include "mac_addr_list.h"
#include "wrapper.h"
#include "reciever.h"
#include "initializer.h"


void Initialiser::initialise()
{
	for (int i = 0; i < sizeof(macs)/sizeof(*macs); i++) {
		Wrapper::get_instance()->add_reciever(new Reciever(macs[i]));
	}
}

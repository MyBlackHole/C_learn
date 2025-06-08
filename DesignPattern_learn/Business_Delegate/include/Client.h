#ifndef CLIENT_H_
#define CLIENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "BusinessDelegate.h"

typedef struct Client Client;

Client *client_create(BusinessDelegate *business_delegate);

void client_destroy(Client **client);

void client_do_task(Client *client);

#ifdef __cplusplus
}
#endif
#endif // CLIENT_H_

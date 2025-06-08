#ifndef CLIENT_H_
#define CLIENT_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Client Client;

Client *client_create(void);

void client_destroy(Client **client);

void client_set_data(Client *client, const char *data1, const char *data2);

void client_print_data(Client *client);

#ifdef __cplusplus
}
#endif
#endif // CLIENT_H_

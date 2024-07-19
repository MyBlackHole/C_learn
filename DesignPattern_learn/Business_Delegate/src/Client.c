#include "Client.h"

#include "ctools.h"

struct Client {
	BusinessDelegate *business_delegate;
};

Client *client_create(BusinessDelegate *business_delegate)
{
	Client *client = (Client *)calloc(1, sizeof(Client));
	if (NULL == client)
		return NULL;
	client->business_delegate = business_delegate;
	return client;
}

void client_destroy(Client **client)
{
	if (NULL == client || NULL == *client)
		return;
	freep((void **)client);
}

void client_do_task(Client *client)
{
	if (NULL == client)
		return;
	business_delegate_do_task(client->business_delegate);
}

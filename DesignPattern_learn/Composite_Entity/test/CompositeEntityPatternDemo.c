#include <stdio.h>

#include "Client.h"

int main(int argc, char const *argv[])
{
	Client *client = client_create();
	client_set_data(client, "Test", "Data");
	client_print_data(client);
	client_set_data(client, "Second Test", "Data1");
	client_print_data(client);
	client_destroy(&client);
	return 0;
}

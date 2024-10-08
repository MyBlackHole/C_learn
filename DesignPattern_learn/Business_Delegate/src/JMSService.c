#include <stdio.h>

#include "BusinessServiceStruct.h"
#include "ctools.h"

static void do_processing(struct BusinessService *business_service)
{
	printf("Processing task by invoking JMS Service\n");
}

struct BusinessService *business_service_create_jmsservice(void)
{
	struct BusinessService *business_service =
		(struct BusinessService *)calloc(
			1, sizeof(struct BusinessService));
	if (NULL == business_service)
		return NULL;

	business_service->do_processing = do_processing;
	return business_service;
}

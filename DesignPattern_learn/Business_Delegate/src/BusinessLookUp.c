#include "BusinessLookUp.h"

#include "ctools.h"

#include <strings.h>

struct BusinessLookUp {};

BusinessLookUp *business_look_up_create(void)
{
	BusinessLookUp *business_look_up =
		(BusinessLookUp *)calloc(1, sizeof(BusinessLookUp));

	return business_look_up;
}

void business_look_up_destroy(BusinessLookUp **business_look_up)
{
	if (NULL == business_look_up || NULL == *business_look_up)
		return;
	freep((void **)business_look_up);
}

BusinessService *
business_look_up_get_business_service(BusinessLookUp *business_look_up,
				      const char *service_type)
{
	if (0 == strcasecmp(service_type, "EJB")) {
		return business_service_create_ejbservice();
	} else {
		return business_service_create_jmsservice();
	}
}

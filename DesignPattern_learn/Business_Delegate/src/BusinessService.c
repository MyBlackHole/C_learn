#include "BusinessService.h"

#include "BusinessServiceStruct.h"
#include "ctools.h"

void business_service_do_processing(BusinessService *business_service)
{
	if (NULL == business_service)
		return;
	if (NULL != business_service->do_processing) {
		business_service->do_processing(business_service);
	}
}

void business_service_destroy(BusinessService **business_service)
{
	if (NULL == business_service || NULL == *business_service)
		return;
	if (NULL != (*business_service)->destroy) {
		(*business_service)->destroy(*business_service);
	}
	freep((void **)business_service);
}

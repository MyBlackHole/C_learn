#ifndef BUSINESS_SERVICE_H_
#define BUSINESS_SERVICE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BusinessService BusinessService;

BusinessService *business_service_create_ejbservice(void);

BusinessService *business_service_create_jmsservice(void);

void business_service_do_processing(BusinessService *business_service);

void business_service_destroy(BusinessService **business_service);

#ifdef __cplusplus
}
#endif
#endif // BUSINESS_SERVICE_H_

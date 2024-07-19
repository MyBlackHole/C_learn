#ifndef BUSINESS_SERVICE_STRUCT_H_
#define BUSINESS_SERVICE_STRUCT_H_

#ifdef __cplusplus
extern "C" {
#endif

struct BusinessService {
	void *priv;

	void (*do_processing)(struct BusinessService *business_service);
	void (*destroy)(struct BusinessService *business_service);
};

#ifdef __cplusplus
}
#endif
#endif // BUSINESS_SERVICE_STRUCT_H_

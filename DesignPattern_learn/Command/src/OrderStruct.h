#ifndef ORDER_STRUCT_H_
#define ORDER_STRUCT_H_

#ifdef __cplusplus
extern "C" {
#endif

struct Order {
	void *priv;

	void (*execute)(struct Order *order);
	void (*destroy)(struct Order *order);
};

#ifdef __cplusplus
}
#endif
#endif // ORDER_STRUCT_H_

#ifndef ITEM_STRUCT_H_
#define ITEM_STRUCT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Packing.h"

struct Item {
	void *priv;
	void *child; /**< 子类 */

	void (*child_destory)(void *child); /**< 子类析构函数 */
	const char *(*name)(struct Item *item);
	struct Packing *(*packing)(struct Item *item);
	float (*price)(struct Item *item);
	void (*destroy)(struct Item *item);
};

#ifdef __cplusplus
}
#endif
#endif // ITEM_STRUCT_H_

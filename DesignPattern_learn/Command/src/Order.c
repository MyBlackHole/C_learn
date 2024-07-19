#include "Order.h"

#include "OrderStruct.h"
#include "Stock.h"
#include "ctools.h"

void order_destroy(Order *order)
{
	if (NULL == order)
		return;
	if (NULL != order->destroy)
		order->destroy(order);
	free(order);
}

void order_excute(Order *order)
{
	if (NULL == order)
		return;
	if (NULL != order->execute)
		order->execute(order);
}

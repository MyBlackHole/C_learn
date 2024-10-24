#include "OrderStruct.h"
#include "Stock.h"
#include "ctools.h"

typedef struct {
	Stock *abc_stock;
} priv_t;

static void init(struct Order *order, Stock *stock)
{
	if (NULL == order)
		return;

	priv_t *priv = (priv_t *)calloc(1, sizeof(priv_t));
	if (NULL == priv)
		return;

	priv->abc_stock = stock;
	order->priv = priv;
}

static void destroy(struct Order *order)
{
	if (NULL == order || NULL == order->priv)
		return;
	freep((void **)&order->priv);
}

static void execute(struct Order *order)
{
	if (NULL == order || NULL == order->priv)
		return;
	priv_t *priv = (priv_t *)order->priv;
	stock_buy(priv->abc_stock);
}

struct Order *buy_stock_order_create(Stock *stock)
{
	struct Order *order = (struct Order *)calloc(1, sizeof(struct Order));
	if (NULL == order)
		return NULL;

	init(order, stock);
	order->execute = execute;
	order->destroy = destroy;
	return order;
}

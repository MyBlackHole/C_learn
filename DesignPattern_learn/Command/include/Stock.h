#ifndef STOCK_H_
#define STOCK_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Stock Stock;

Stock *stock_create(void);
void stock_destroy(Stock **stock);
void stock_buy(Stock *stock);
void stock_sell(Stock *stock);

#ifdef __cplusplus
}
#endif
#endif // STOCK_H_

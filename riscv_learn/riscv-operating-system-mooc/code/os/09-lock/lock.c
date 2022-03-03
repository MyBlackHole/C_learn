#include "os.h"

static reg_t x;

extern void amoswap_w_aq(reg_t *x);
extern void amoswap_w_rl(reg_t *x);

int spin_lock() {
  amoswap_w_aq(&x);
  // w_mstatus(r_mstatus() & ~MSTATUS_MIE);
  return 0;
}

int spin_unlock() {
  amoswap_w_rl(&x);
  // w_mstatus(r_mstatus() | MSTATUS_MIE);
  return 0;
}

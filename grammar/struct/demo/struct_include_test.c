
struct ev_loop {
	int ev_rt_now;
#define ev_rt_now ((loop)->ev_rt_now)
#define VAR(name, decl) decl;
#include "struct_include_test.h"
#undef VAR
};

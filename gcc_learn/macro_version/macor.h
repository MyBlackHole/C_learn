#include "version.h"

#define KERNEL_VERSION(a, b, c) \
	(((a) << 16) + ((b) << 8) + ((c) > 255 ? 255 : (c)))

#define SIMPLEFS_AT_LEAST(major, minor, rev) \
	LINUX_VERSION_CODE >= KERNEL_VERSION(major, minor, rev)
#define SIMPLEFS_LESS_EQUAL(major, minor, rev) \
	LINUX_VERSION_CODE <= KERNEL_VERSION(major, minor, rev)

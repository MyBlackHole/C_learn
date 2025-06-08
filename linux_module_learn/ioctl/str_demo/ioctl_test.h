#ifndef __HEAD_H__
#define __HEAD_H__

#define CNAME "ioctl_test"

typedef struct {
	int width;
	int high;
} image_t;

#define UACCESS_BUF _IOW('a', 1, char[128])
#define UACCESS_STRUCT _IOW('a', 1, image_t)

#endif

#ifndef __PATH_H
#define __PATH_H

char *get_file_real_path(int dfd, const char __user *filename, char *buf,
			 const int buflen);

#endif /* __PATH_H */

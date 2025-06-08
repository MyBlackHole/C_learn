#ifndef IOT_433_H
#define IOT_433_H

int iot_init_tty(int fd);
int iot_send(int fd, int map_index, int data_index);

#endif

#ifndef __NVS_SRC_HIDRAW_H__
#define __NVS_SRC_HIDRAW_H__

#include <linux/hidraw.h>

int hidraw_open(const char *dev_name);

void hidraw_close(int fd);

int hidraw_get_report(int fd, void *buffer, unsigned len);

int hidraw_send_report(int fd, const void *buffer, unsigned len);

int hidraw_get_descriptor(int fd, struct hidraw_report_descriptor *desc);

#endif

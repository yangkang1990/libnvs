#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "hidraw.h"

#define DEVPATH_MAX_SIZE 64

int hidraw_open(const char *dev_name)
{
	char dev_path[DEVPATH_MAX_SIZE];
	int fd;

	snprintf(dev_path, DEVPATH_MAX_SIZE, "/dev/%s", dev_name);
	printf("[yk]hidraw_open:%s\n", dev_path);
	fd = open(dev_path, O_RDWR);

	return fd;
}

void hidraw_close(int fd)
{
	close(fd);
}

int hidraw_get_report(int fd, void *buffer, unsigned len)
{
	return read(fd, buffer, len);
}

int hidraw_send_report(int fd, const void *buffer, unsigned len)
{
	return write(fd, buffer, len);
}


int hidraw_get_descriptor(int fd, struct hidraw_report_descriptor *desc)
{
	int ret;

	ret = ioctl(fd, HIDIOCGRDESCSIZE, &desc->size);
	if (ret < 0)
		return ret;

	ret = ioctl(fd, HIDIOCGRDESC, desc);
	if (ret < 0)
		return ret;

	return 0;
}


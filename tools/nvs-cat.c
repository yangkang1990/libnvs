#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <stdlib.h>

#include "../include/nvs.h"

static struct nvs_device *dev;

static void termination_handler(int signum)
{
	if (dev)
		nvs_close(dev);
	_exit(0);
}

static int install_termination_handler(void)
{
	struct sigaction sa;
	int ret;

	sa.sa_handler = termination_handler;
	sigemptyset (&sa.sa_mask);
	sa.sa_flags = 0;

	ret = sigaction(SIGINT, &sa, NULL);
	if (ret)
		return ret;

	ret = sigaction(SIGHUP, &sa, NULL);
	if (ret)
		return ret;

	ret = sigaction(SIGTERM, &sa, NULL);

	return ret;
}

int main(int argc, char **argv)
{
	uint8_t buffer[NVS_MAX_FRAME_SIZE];
	ssize_t written;
	int size;
	int fd;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <hidraw device>\n", argv[0]);
		fprintf(stderr, "Example: %s hidraw0\n", argv[0]);
		return -1;
	}

	if (install_termination_handler()) {
		perror("install_termination_handler");
		return -1;
	}

	dev = nvs_open(argv[1]);
	if (!dev) {
		perror("nvs_open");
		return -1;
	}
	printf("generate the file /tmp/voice.adpcm");
	fd = open("/tmp/voice.adpcm",O_WRONLY|O_CREAT);
	while (1) {
		size = nvs_get_audio(dev, buffer);
		if (size < 0 && size != -EAGAIN) {
			nvs_close(dev);
			return size;
		}
		printf("size=%d\n", size);
		written = 0;
		while (written < size)
			written += write(fd, buffer + written, size - written);
		
	}
	close(fd);
}

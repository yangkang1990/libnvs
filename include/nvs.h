#ifndef __LIBNVS_NVS_H__
#define __LIBNVS_NVS_H__

#ifdef __cplusplus
extern "C" {
#endif

#define NVS_MAX_FRAME_SIZE 4000

#include <inttypes.h>

struct nvs_device;

struct nvs_device *nvs_open(const char *dev_name);

void nvs_close(struct nvs_device *dev);

int nvs_get_audio(struct nvs_device *dev, uint8_t *buffer);

int nvs_get_fd(struct nvs_device *dev);

int nvs_check_descriptor(const char *dev_name, unsigned int *sampling_rate);

#ifdef __cplusplus
}
#endif
#endif

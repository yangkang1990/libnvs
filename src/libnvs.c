#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <adpcm.h>

#include "../include/nvs.h"
#include "hidraw.h"
#include "protocol.h"
#include "decoder.h"

#define NVS_API __attribute__((visibility ("default")))

struct nvs_codec {
	unsigned int		sampling_rate;
	unsigned int		report_id;

	const uint8_t		*descriptor;
	unsigned int		descriptor_size;

	const uint8_t		*mask;
	unsigned int		mask_size;

	struct nvs_decoder *	(*decoder_init)(void);
};

struct nvs_device {
	const struct nvs_codec	*codec;
	struct nvs_decoder	*decoder;
	int			fd;
};

static const uint8_t bv32_desc[] = {
	0x06, 0x00, 0xFF, 0x09, 0x00, 0xA1, 0x01, 0x85, 0x01, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x14, 0x09, 0x00, 0x81, 0x02, 0x95, 0x01, 0x75,
	0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

static const uint8_t adpcm_8k_h256_desc[] = {
	0x06, 0x00, 0xFF, 0x09, 0x10, 0xA1, 0x01, 0x85, 0x02, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x14, 0x09, 0x00, 0x81, 0x02, 0x85, 0x01, 0x95,
	0x01, 0x75, 0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

static const uint8_t adpcm_8k_h128_desc[] = {
	0x06, 0x00, 0xFF, 0x09, 0x11, 0xA1, 0x01, 0x85, 0x02, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x14, 0x09, 0x00, 0x81, 0x02, 0x85, 0x01, 0x95,
	0x01, 0x75, 0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

static const uint8_t adpcm_8k_h64_desc[] = {
	0x06, 0x00, 0xFF, 0x09, 0x12, 0xA1, 0x01, 0x85, 0x02, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x14, 0x09, 0x00, 0x81, 0x02, 0x85, 0x01, 0x95,
	0x01, 0x75, 0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

static const uint8_t adpcm_16k_h256_desc[] = {
	0x06, 0x00, 0xFF, 0x09, 0x00, 0xA1, 0x01, 0x85, 0x02, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x14, 0x09, 0x00, 0x81, 0x02, 0x85, 0x01, 0x95,
	0x01, 0x75, 0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

static const uint8_t adpcm_16k_h128_desc[] = {
	0x06, 0x00, 0xFF, 0x09, 0x01, 0xA1, 0x01, 0x85, 0x02, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x14, 0x09, 0x00, 0x81, 0x02, 0x85, 0x01, 0x95,
	0x01, 0x75, 0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

static const uint8_t adpcm_16k_h64_desc[] = {
	0x06, 0x00, 0xFF, 0x09, 0x02, 0xA1, 0x01, 0x85, 0x02, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x14, 0x09, 0x00, 0x81, 0x02, 0x85, 0x01, 0x95,
	0x01, 0x75, 0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

static const uint8_t adpcm_16k_h256_desc_rmf_tx20xu[] = {
	0x06, 0x00, 0xFF, 0x09, 0x04, 0xA1, 0x01, 0x85, 0x02, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x14, 0x09, 0x00, 0x81, 0x02, 0x85, 0x01, 0x95,
	0x01, 0x75, 0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

static const uint8_t adpcm_24k_h256_desc[] = {
	0x06, 0x00, 0xFF, 0x09, 0x20, 0xA1, 0x01, 0x85, 0x02, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x14, 0x09, 0x00, 0x81, 0x02, 0x85, 0x01, 0x95,
	0x01, 0x75, 0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

static const uint8_t adpcm_24k_h128_desc[] = {
	0x06, 0x00, 0xFF, 0x09, 0x21, 0xA1, 0x01, 0x85, 0x02, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x14, 0x09, 0x00, 0x81, 0x02, 0x85, 0x01, 0x95,
	0x01, 0x75, 0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

static const uint8_t adpcm_24k_h64_desc[] = {
	0x06, 0x00, 0xFF, 0x09, 0x22, 0xA1, 0x01, 0x85, 0x02, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x14, 0x09, 0x00, 0x81, 0x02, 0x85, 0x01, 0x95,
	0x01, 0x75, 0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

static const uint8_t adpcm_32k_h256_desc[] = {
	0x06, 0x00, 0xFF, 0x09, 0x30, 0xA1, 0x01, 0x85, 0x02, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x14, 0x09, 0x00, 0x81, 0x02, 0x85, 0x01, 0x95,
	0x01, 0x75, 0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

static const uint8_t adpcm_32k_h128_desc[] = {
	0x06, 0x00, 0xFF, 0x09, 0x31, 0xA1, 0x01, 0x85, 0x02, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x14, 0x09, 0x00, 0x81, 0x02, 0x85, 0x01, 0x95,
	0x01, 0x75, 0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

static const uint8_t adpcm_32k_h64_desc[] = {
	0x06, 0x00, 0xFF, 0x09, 0x32, 0xA1, 0x01, 0x85, 0x02, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x14, 0x09, 0x00, 0x81, 0x02, 0x85, 0x01, 0x95,
	0x01, 0x75, 0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

static const uint8_t opus_8k_desc[] = {
	0x06, 0x00, 0xFF, 0x09, 0x10, 0xA1, 0x01, 0x85, 0x03, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x00, 0x09, 0x00, 0x81, 0x02, 0x85, 0x01, 0x95,
	0x01, 0x75, 0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

static const uint8_t opus_16k_desc[] = {
	0x06, 0x00, 0xFF, 0x09, 0x00, 0xA1, 0x01, 0x85, 0x03, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x00, 0x09, 0x00, 0x81, 0x02, 0x85, 0x01, 0x95,
	0x01, 0x75, 0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

static const uint8_t opus_24k_desc[] = {
	0x06, 0x00, 0xFF, 0x09, 0x20, 0xA1, 0x01, 0x85, 0x03, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x00, 0x09, 0x00, 0x81, 0x02, 0x85, 0x01, 0x95,
	0x01, 0x75, 0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

static const uint8_t sbc_16k_msbc_desc[] = {
	0x06, 0x00, 0xFF, 0x09, 0x00, 0xA1, 0x01, 0x85, 0x04, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x00, 0x09, 0x00, 0x81, 0x02, 0x85, 0x01, 0x95,
	0x01, 0x75, 0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

static const uint8_t sbc_32k_msbc_desc[] = {
	0x06, 0x00, 0xFF, 0x09, 0x30, 0xA1, 0x01, 0x85, 0x04, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x00, 0x09, 0x00, 0x81, 0x02, 0x85, 0x01, 0x95,
	0x01, 0x75, 0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

static const uint8_t sbc_16k_a2dp_desc[] = {
	0x06, 0x00, 0xFF, 0x09, 0x01, 0xA1, 0x01, 0x85, 0x04, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x00, 0x09, 0x00, 0x81, 0x02, 0x85, 0x01, 0x95,
	0x01, 0x75, 0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

static const uint8_t sbc_32k_a2dp_desc[] = {
	0x06, 0x00, 0xFF, 0x09, 0x31, 0xA1, 0x01, 0x85, 0x04, 0x15, 0x00, 0x25,
	0xFF, 0x75, 0x08, 0x95, 0x00, 0x09, 0x00, 0x81, 0x02, 0x85, 0x01, 0x95,
	0x01, 0x75, 0x08, 0x09, 0x00, 0x91, 0x02, 0xC0 };

/*
 * Mask out report count in order to match descriptors
 * of the remotes supporting large MTU.
 */
static const uint8_t opus_sbc_desc_mask[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

static struct nvs_decoder *adpcm_h256_init(void)
{
	return decoder_adpcm_init(ADPCM_HEADER_SIZE + 256);
}

static struct nvs_decoder *adpcm_h128_init(void)
{
	return decoder_adpcm_init(ADPCM_HEADER_SIZE + 128);
}

static struct nvs_decoder *adpcm_h64_init(void)
{
	return decoder_adpcm_init(ADPCM_HEADER_SIZE + 64);
}

static struct nvs_decoder *opus_8k_init(void)
{
	return decoder_opus_init(8000);
}

static struct nvs_decoder *opus_16k_init(void)
{
	return decoder_opus_init(16000);
}

static struct nvs_decoder *opus_24k_init(void)
{
	return decoder_opus_init(24000);
}

static const struct nvs_codec nvs_codecs[] = {
	{
		/* BV32 */
		.sampling_rate		= 16125,
		.report_id		= 1,
		.descriptor		= bv32_desc,
		.descriptor_size	= sizeof(bv32_desc),
		.decoder_init		= decoder_bv32_init,
	}, {
		/* ADPCM 8kHz H256 */
		.sampling_rate		= 7936,
		.report_id		= 2,
		.descriptor		= adpcm_8k_h256_desc,
		.descriptor_size	= sizeof(adpcm_8k_h256_desc),
		.decoder_init		= adpcm_h256_init,
	}, {
		/* ADPCM 8kHz H128 */
		.sampling_rate		= 7936,
		.report_id		= 2,
		.descriptor		= adpcm_8k_h128_desc,
		.descriptor_size	= sizeof(adpcm_8k_h128_desc),
		.decoder_init		= adpcm_h128_init,
	}, {
		/* ADPCM 8kHz H64 */
		.sampling_rate		= 7936,
		.report_id		= 2,
		.descriptor		= adpcm_8k_h64_desc,
		.descriptor_size	= sizeof(adpcm_8k_h64_desc),
		.decoder_init		= adpcm_h64_init,
	}, {
		/* ADPCM 16kHz H256 (SR3 for NRF51 compatible mode) */
		.sampling_rate		= 16000,
		.report_id		= 2,
		.descriptor		= adpcm_16k_h256_desc,
		.descriptor_size	= sizeof(adpcm_16k_h256_desc),
		.decoder_init		= adpcm_h256_init,
	}, {
		/* ADPCM 16kHz H128 (SR3 for NRF51 compatible mode) */
		.sampling_rate		= 16000,
		.report_id		= 2,
		.descriptor		= adpcm_16k_h128_desc,
		.descriptor_size	= sizeof(adpcm_16k_h128_desc),
		.decoder_init		= adpcm_h128_init,
	}, {
		/* ADPCM 16kHz H64 (SR3 for NRF51 compatible mode) */
		.sampling_rate		= 16000,
		.report_id		= 2,
		.descriptor		= adpcm_16k_h64_desc,
		.descriptor_size	= sizeof(adpcm_16k_h64_desc),
		.decoder_init		= adpcm_h64_init,
	}, {
		/* ADPCM 16kHz H256 for RMF-TX20XU */
		.sampling_rate		= 16000,
		.report_id		= 2,
		.descriptor		= adpcm_16k_h256_desc_rmf_tx20xu,
		.descriptor_size	= sizeof(adpcm_16k_h256_desc_rmf_tx20xu),
		.decoder_init		= adpcm_h256_init,
	}, {
		/* ADPCM 24kHz H256 */
		.sampling_rate		= 23819,
		.report_id		= 2,
		.descriptor		= adpcm_24k_h256_desc,
		.descriptor_size	= sizeof(adpcm_24k_h256_desc),
		.decoder_init		= adpcm_h256_init,
	}, {
		/* ADPCM 24kHz H128 */
		.sampling_rate		= 23819,
		.report_id		= 2,
		.descriptor		= adpcm_24k_h128_desc,
		.descriptor_size	= sizeof(adpcm_24k_h128_desc),
		.decoder_init		= adpcm_h128_init,
	}, {
		/* ADPCM 24kHz H64 */
		.sampling_rate		= 23819,
		.report_id		= 2,
		.descriptor		= adpcm_24k_h64_desc,
		.descriptor_size	= sizeof(adpcm_24k_h64_desc),
		.decoder_init		= adpcm_h64_init,
	}, {
		/* ADPCM 32kHz H256 */
		.sampling_rate		= 31250,
		.report_id		= 2,
		.descriptor		= adpcm_32k_h256_desc,
		.descriptor_size	= sizeof(adpcm_32k_h256_desc),
		.decoder_init		= adpcm_h256_init,
	}, {
		/* ADPCM 32kHz H128 */
		.sampling_rate		= 31250,
		.report_id		= 2,
		.descriptor		= adpcm_32k_h128_desc,
		.descriptor_size	= sizeof(adpcm_32k_h128_desc),
		.decoder_init		= adpcm_h128_init,
	}, {
		/* ADPCM 32kHz H64 */
		.sampling_rate		= 31250,
		.report_id		= 2,
		.descriptor		= adpcm_32k_h64_desc,
		.descriptor_size	= sizeof(adpcm_32k_h64_desc),
		.decoder_init		= adpcm_h64_init,
	}, {
		/* OPUS 8kHz */
		.sampling_rate		= 7936,
		.report_id		= 3,
		.descriptor		= opus_8k_desc,
		.descriptor_size	= sizeof(opus_8k_desc),
		.mask			= opus_sbc_desc_mask,
		.mask_size		= sizeof(opus_sbc_desc_mask),
		.decoder_init		= opus_8k_init,
	}, {
		/* OPUS 16kHz */
		.sampling_rate		= 16125,
		.report_id		= 3,
		.descriptor		= opus_16k_desc,
		.descriptor_size	= sizeof(opus_16k_desc),
		.mask			= opus_sbc_desc_mask,
		.mask_size		= sizeof(opus_sbc_desc_mask),
		.decoder_init		= opus_16k_init,
	}, {
		/* OPUS 24kHz */
		.sampling_rate		= 23819,
		.report_id		= 3,
		.descriptor		= opus_24k_desc,
		.descriptor_size	= sizeof(opus_24k_desc),
		.mask			= opus_sbc_desc_mask,
		.mask_size		= sizeof(opus_sbc_desc_mask),
		.decoder_init		= opus_24k_init,
	}, {
		/* SBC 16kHz mSBC */
		.sampling_rate		= 16125,
		.report_id		= 4,
		.descriptor		= sbc_16k_msbc_desc,
		.descriptor_size	= sizeof(sbc_16k_msbc_desc),
		.mask			= opus_sbc_desc_mask,
		.mask_size		= sizeof(opus_sbc_desc_mask),
		.decoder_init		= decoder_msbc_init,
	}, {
		/* SBC 32kHz mSBC */
		.sampling_rate		= 31250,
		.report_id		= 4,
		.descriptor		= sbc_32k_msbc_desc,
		.descriptor_size	= sizeof(sbc_32k_msbc_desc),
		.mask			= opus_sbc_desc_mask,
		.mask_size		= sizeof(opus_sbc_desc_mask),
		.decoder_init		= decoder_msbc_init,
	}, {
		/* SBC 16kHz A2DP */
		.sampling_rate		= 16125,
		.report_id		= 4,
		.descriptor		= sbc_16k_a2dp_desc,
		.descriptor_size	= sizeof(sbc_16k_a2dp_desc),
		.mask			= opus_sbc_desc_mask,
		.mask_size		= sizeof(opus_sbc_desc_mask),
		.decoder_init		= decoder_sbc_init,
	}, {
		/* SBC 32kHz A2DP */
		.sampling_rate		= 31250,
		.report_id		= 4,
		.descriptor		= sbc_32k_a2dp_desc,
		.descriptor_size	= sizeof(sbc_32k_a2dp_desc),
		.mask			= opus_sbc_desc_mask,
		.mask_size		= sizeof(opus_sbc_desc_mask),
		.decoder_init		= decoder_sbc_init,
	}
};

static const struct nvs_codec *find_codec(const struct hidraw_report_descriptor *desc)
{
	const struct nvs_codec *codec = NULL;
	unsigned int idx, i;

	for (idx = 0; idx < (sizeof(nvs_codecs) / sizeof(nvs_codecs[0])); idx++) {
		const struct nvs_codec *c = &nvs_codecs[idx];

		if (desc->size < c->descriptor_size)
			continue;

		for (i = 0; i < c->descriptor_size; i++) {
			uint8_t value = desc->value[i];
			uint8_t reference = c->descriptor[i];

			if ((c->mask != NULL) && (i < c->mask_size))
				value &= c->mask[i];

			if (value != reference)
				break;
		}

		if (i == c->descriptor_size) {
			codec = c;
			break;
		}
	}

	return codec;
}

NVS_API struct nvs_device *nvs_open(const char *dev_name)
{
	struct hidraw_report_descriptor desc;
	struct nvs_output_report report;
	struct nvs_device *dev;
	int ret;

	dev = malloc(sizeof(struct nvs_device));
	if (!dev)
		return NULL;
	
	dev->fd = hidraw_open(dev_name);
	if (dev->fd < 0)
		goto free_dev;

	ret = hidraw_get_descriptor(dev->fd, &desc);
	if (ret < 0)
		goto close_dev;

	dev->codec = find_codec(&desc);
	if (dev->codec) {
		dev->decoder = dev->codec->decoder_init();
	} else {
		dev->decoder = NULL;
	}

	if (!dev->decoder)
		goto close_dev;

	put_cmd(&report, NVS_CMD_START);
	ret = hidraw_send_report(dev->fd, &report, sizeof(report));
	if (ret < 0)
		goto deinit_decoder;

	return dev;

deinit_decoder:
	dev->decoder->decoder_deinit(dev->decoder);
close_dev:
	hidraw_close(dev->fd);
free_dev:
	free(dev);
	return NULL;
}

NVS_API void nvs_close(struct nvs_device *dev)
{
	struct nvs_output_report report;

	put_cmd(&report, NVS_CMD_STOP);
	hidraw_send_report(dev->fd, &report, sizeof(report));

	dev->decoder->decoder_deinit(dev->decoder);
	hidraw_close(dev->fd);
	free(dev);
}

NVS_API int nvs_get_audio(struct nvs_device *dev, uint8_t *buffer)
{
	struct nvs_input_report report;
	int size;

	size = hidraw_get_report(dev->fd, &report, sizeof(report));
	if (size < 0)
		return size;

	if (dev->codec->report_id != report.report_id)
		return -EAGAIN;

	return dev->decoder->decode_pkt(dev->decoder, report.audio,
					size - sizeof(report.report_id),
					(int16_t *)buffer);
}

NVS_API int nvs_get_fd(struct nvs_device *dev)
{
	return dev->fd;
}

#define DESCPATH_MAX_SIZE 64

static int read_descriptor_sysfs(const char *dev_name,
				 struct hidraw_report_descriptor *desc)
{
	char desc_path[DESCPATH_MAX_SIZE];
	int fd, nread;

	snprintf(desc_path, DESCPATH_MAX_SIZE,
		 "/sys/class/hidraw/%s/device/report_descriptor",
		 dev_name);

	fd = open(desc_path, O_RDONLY);
	if (fd < 0)
		return fd;

	desc->size = 0;
	while (1) {
		nread = read(fd, &desc->value[desc->size],
			     HID_MAX_DESCRIPTOR_SIZE - desc->size);
		if (nread <= 0)
			break;
		desc->size += nread;
	}

	close(fd);

	return nread;
}

NVS_API int nvs_check_descriptor(const char *dev_name, unsigned int *sampling_rate)
{
	struct hidraw_report_descriptor desc;
	const struct nvs_codec *codec;
	int ret;

	ret = read_descriptor_sysfs(dev_name, &desc);
	if (ret < 0)
		return ret;

	codec = find_codec(&desc);
	if (!codec)
		return 0;

	if (sampling_rate)
		*sampling_rate = codec->sampling_rate;

	return 1;
}

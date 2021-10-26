#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "nvs.h"
#include "decoder.h"
#include "upsampler/cmsis_q_types.h"
#include "upsampler/upsampler_v1.h"

struct adpcm_upsampled_decoder {
	struct nvs_decoder funcs;
	struct nvs_decoder *adpcm;
};

static int adpcm_upsampled_decode_pkt(struct nvs_decoder *d,
			   const uint8_t *encoded,
			   int size,
			   int16_t *raw)
{
	struct adpcm_upsampled_decoder *dec = (struct adpcm_upsampled_decoder *)d;
	uint8_t buffer[NVS_MAX_FRAME_SIZE];
	int r;

	r = dec->adpcm->decode_pkt(dec->adpcm, encoded, size, (int16_t *)buffer);
	if (r > 0) {
		uint8_t discard[NVS_MAX_FRAME_SIZE];
		r = up2_sampler((q15_t *)buffer, r / sizeof(q15_t), (q15_t *)raw, (q15_t *)discard, sizeof(discard) / sizeof(q15_t));
		if (r > 0)
			r *= sizeof(q15_t);
	}

	return r;
}

static void adpcm_upsampled_deinit(struct nvs_decoder *d)
{
	struct adpcm_upsampled_decoder *dec = (struct adpcm_upsampled_decoder *)d;

	dec->adpcm->decoder_deinit(dec->adpcm);
	free(dec);
}

struct nvs_decoder *decoder_adpcm_upsampled_init(unsigned int frame_size)
{
	struct adpcm_upsampled_decoder *dec;

	dec = malloc(sizeof(*dec));
	if (!dec)
		return NULL;

	dec->adpcm = decoder_adpcm_init(frame_size);
	if (!dec->adpcm) {
		free(dec);
		return NULL;
	}

	dec->funcs.decode_pkt = adpcm_upsampled_decode_pkt;
	dec->funcs.decoder_deinit = adpcm_upsampled_deinit;

	return (struct nvs_decoder *)dec;
}

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <adpcm.h>

#include "decoder.h"

#define ADPCM_MAX_FRAME_SIZE (ADPCM_HEADER_SIZE + 256)

struct adpcm_decoder {
	struct nvs_decoder funcs;
	adpcm_decode_state_t *state;
	unsigned int num_of_20byte_pkts;
	unsigned int last_pkt_size;
	unsigned int pkts;
	uint8_t buffer[ADPCM_MAX_FRAME_SIZE];
};

static int adpcm_decode_pkt(struct nvs_decoder *d,
			   const uint8_t *encoded,
			   int size,
			   int16_t *raw)
{
	struct adpcm_decoder *dec = (struct adpcm_decoder *) d;
	//printf("[yk]adpcm_decode_pkt in\n");
	/* We must receive "num_of_20byte_pkts" 20-bytes packets followed by a "last_pkt_size" packet */
	if (size == 20) {
		if (dec->pkts >= dec->num_of_20byte_pkts)
			dec->pkts = 0;

		memcpy(dec->buffer + (dec->pkts * 20), encoded, size);
		dec->pkts += 1;
		return 0;
	} else {
		if (size == dec->last_pkt_size) {
			if (dec->pkts != dec->num_of_20byte_pkts) {
				dec->pkts = 0;
				return 0;
			}

			memcpy(dec->buffer + (dec->pkts * 20), encoded, size);
			dec->pkts = 0;

			return adpcm_decode(dec->state, raw, dec->buffer,
					    (dec->num_of_20byte_pkts * 20) + dec->last_pkt_size);
		} else {
			errno = EPROTO;
			return -1;
		}
	}

	/* Not Reached */
}

static void adpcm_deinit(struct nvs_decoder *d)
{
	struct adpcm_decoder *dec = (struct adpcm_decoder *) d;

	adpcm_decode_free(dec->state);
	dec->state = NULL;

	free(dec);
}

struct nvs_decoder *decoder_adpcm_init(unsigned int frame_size)
{
	struct adpcm_decoder *dec;

	if (frame_size > ADPCM_MAX_FRAME_SIZE)
		return NULL;

	dec = malloc(sizeof(struct adpcm_decoder));
	if (!dec)
		return NULL;

	dec->state = adpcm_decode_alloc();
	if (!dec->state)
		goto adpcm_error;

	dec->funcs.decode_pkt = adpcm_decode_pkt;
	dec->funcs.decoder_deinit = adpcm_deinit;
	dec->num_of_20byte_pkts = frame_size / 20;
	dec->last_pkt_size = frame_size % 20;
	dec->pkts = 0;

	return (struct nvs_decoder *) dec;

adpcm_error:
	free(dec);
	return NULL;
}

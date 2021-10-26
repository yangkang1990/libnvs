#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <broadvoice/broadvoice.h>

#include "decoder.h"

struct bv32_decoder {
	struct nvs_decoder funcs;
	bv32_decode_state_t *state;
};

static int bv32_decode_pkt(struct nvs_decoder *d,
			   const uint8_t *encoded,
			   int size,
			   int16_t *raw)
{
	struct bv32_decoder *dec = (struct bv32_decoder *) d;

	if (size != 20) {
		errno = EPROTO;
		return -1;
	}

	bv32_decode(dec->state, raw, encoded);

	return BV32_FRAME_LEN * sizeof(int16_t);
}

static void bv32_deinit(struct nvs_decoder *d)
{
	struct bv32_decoder *dec = (struct bv32_decoder *) d;

	bv32_decode_free(dec->state);
	dec->state = NULL;

	free(dec);
}

struct nvs_decoder *decoder_bv32_init()
{
	struct bv32_decoder *dec = malloc(sizeof(struct bv32_decoder));
	if (!dec)
		goto malloc_error;

	dec->state = bv32_decode_alloc();
	if (!dec->state)
		goto bv32_error;

	dec->funcs.decode_pkt = bv32_decode_pkt;
	dec->funcs.decoder_deinit = bv32_deinit;

	return (struct nvs_decoder *) dec;

bv32_error:
	free(dec);
malloc_error:
	return NULL;
}

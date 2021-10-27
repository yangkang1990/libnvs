#include <errno.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../include/nvs.h"

#include "decoder.h"

// Macro returning division result rounded up.
#define CEIL_DIV(A, B)  (((A) + (B) - 1) / (B))

// Ref. A2DP specification v1.3.1, page 70,
//      12.9 Calculation of Bit Rate and Frame Length
// Since MONO is the only mode used here, the size is calculated for one
// channel.
#define SBC_FRAME_SIZE(subbands, blocks, bitpool) \
	(4 + (4 * subbands) / 8 + CEIL_DIV(blocks * (uint16_t)bitpool, 8))
// Ref. HFP specification v1.7.0, page 115,
//      5.7.4 mSBC coding
#define MSBC_FRAME_SIZE  SBC_FRAME_SIZE(8, 15, 26)

#define MAX_SBC_FRAME_SIZE  SBC_FRAME_SIZE(8, 16, 250)

struct sbc_decoder {
	struct nvs_decoder funcs;
	bool     msbc;
	uint16_t frame_size;
	uint16_t bytes_received;
	uint8_t  buffer[MAX_SBC_FRAME_SIZE];
};

static uint16_t calculate_frame_size(const uint8_t *header)
{
	return 0;
}

static int decode_pkt(struct nvs_decoder *d,
		      const uint8_t *encoded,
		      int size,
		      int16_t *raw)
{
	return 0;
}

static void decoder_deinit(struct nvs_decoder *d)
{
	return;
}

static struct sbc_decoder *decoder_init(void)
{
	return NULL;
}

struct nvs_decoder *decoder_msbc_init(void)
{
	return NULL;
}

struct nvs_decoder *decoder_sbc_init(void)
{
	return NULL;
}


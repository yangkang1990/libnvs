#include <errno.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sbc/sbc.h>
#include <nvs.h>

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
	sbc_t    sbc;
	bool     msbc;
	uint16_t frame_size;
	uint16_t bytes_received;
	uint8_t  buffer[MAX_SBC_FRAME_SIZE];
};

static uint16_t calculate_frame_size(const uint8_t *header)
{
	uint8_t subbands;
	uint8_t blocks;
	uint8_t bitpool;

	subbands = (header[1] & 0x01) ? 8 : 4;
	switch ((header[1] >> 4) & 0x03)
	{
	case SBC_BLK_4:
		blocks = 4;
		break;
	case SBC_BLK_8:
		blocks = 8;
		break;
	case SBC_BLK_12:
		blocks = 12;
		break;
	case SBC_BLK_16:
		blocks = 16;
		break;
	}
	bitpool = header[2];

	return SBC_FRAME_SIZE(subbands, blocks, bitpool);
}

static int decode_pkt(struct nvs_decoder *d,
		      const uint8_t *encoded,
		      int size,
		      int16_t *raw)
{
	struct sbc_decoder *dec = (struct sbc_decoder *) d;

	if (dec->frame_size == 0)
	{
		if (dec->msbc)
		{
			dec->frame_size = MSBC_FRAME_SIZE;
		}
		else
		{
			dec->frame_size = calculate_frame_size(encoded);
		}
		dec->bytes_received = 0;
	}
	if (size > (MAX_SBC_FRAME_SIZE - dec->bytes_received))
	{
		size = (MAX_SBC_FRAME_SIZE - dec->bytes_received);
	}
	memcpy(&dec->buffer[dec->bytes_received], encoded, size);
	dec->bytes_received += size;
	if (dec->bytes_received < dec->frame_size)
	{
		return 0;
	}
	dec->frame_size = 0;

	size_t written;
	int status = sbc_decode(&dec->sbc, dec->buffer, dec->bytes_received,
				raw, NVS_MAX_FRAME_SIZE, &written);
	if (status < 0)
	{
		errno = EPROTO;
		return -1;
	}

	return written;
}

static void decoder_deinit(struct nvs_decoder *d)
{
	struct sbc_decoder *dec = (struct sbc_decoder *) d;

	free(dec);
}

static struct sbc_decoder *decoder_init(void)
{
	struct sbc_decoder *dec;

	dec = malloc(sizeof(struct sbc_decoder));
	if (!dec)
		return NULL;

	dec->funcs.decode_pkt     = decode_pkt;
	dec->funcs.decoder_deinit = decoder_deinit;
	dec->frame_size = 0;

	return dec;
}

struct nvs_decoder *decoder_msbc_init(void)
{
	struct sbc_decoder *dec = decoder_init();
	if (dec)
	{
		dec->msbc = true;
		if (sbc_init_msbc(&dec->sbc, 0) < 0)
		{
			free(dec);
			return NULL;
		}
	}
	return (struct nvs_decoder *) dec;
}

struct nvs_decoder *decoder_sbc_init(void)
{
	struct sbc_decoder *dec = decoder_init();
	if (dec)
	{
		dec->msbc = false;
		if (sbc_init(&dec->sbc, 0) < 0)
		{
			free(dec);
			return NULL;
		}
	}
	return (struct nvs_decoder *) dec;
}


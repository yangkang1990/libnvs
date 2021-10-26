#include <endian.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <opus/opus.h>
#include <nvs.h>

#include "decoder.h"

#define OPUS_MAX_FRAME_SIZE	3840

struct opus_decoder {
	struct nvs_decoder funcs;
	OpusDecoder *state;
	unsigned int frame_size;
	unsigned int bytes_received;
	uint8_t buffer[OPUS_MAX_FRAME_SIZE];
};

struct opus_packet_header {
	uint16_t frame_size;
} __attribute__((__packed__));

static int opus_decode_pkt(struct nvs_decoder *d,
			   const uint8_t *encoded,
			   int size,
			   int16_t *raw)
{
	struct opus_decoder *dec = (struct opus_decoder *)d;
	int status;

	if (dec->bytes_received == 0) {
		const struct opus_packet_header *hdr = (struct opus_packet_header *)encoded;

		/* Check packet length */
		if (size <= sizeof(*hdr))
			return 0;

		/* Check frame size */
		if ((be16toh(hdr->frame_size) < 1) || (be16toh(hdr->frame_size) > OPUS_MAX_FRAME_SIZE))
			return 0;

		/* Check Opus Configuration ID */
		if (((encoded[sizeof(*hdr)] >> 2) != ( 0 << 1)) && /* SLIK NB 10ms */
		    ((encoded[sizeof(*hdr)] >> 2) != ( 1 << 1)) && /* SLIK NB 20ms */
		    ((encoded[sizeof(*hdr)] >> 2) != ( 2 << 1)) && /* SLIK NB 40ms */
		    ((encoded[sizeof(*hdr)] >> 2) != ( 3 << 1)) && /* SLIK NB 60ms */
		    ((encoded[sizeof(*hdr)] >> 2) != ( 8 << 1)) && /* SLIK WB 10ms */
		    ((encoded[sizeof(*hdr)] >> 2) != ( 9 << 1)) && /* SILK WB 20ms */
		    ((encoded[sizeof(*hdr)] >> 2) != (10 << 1)) && /* SILK WB 40ms */
		    ((encoded[sizeof(*hdr)] >> 2) != (11 << 1)) && /* SILK WB 60ms */
		    ((encoded[sizeof(*hdr)] >> 2) != (17 << 1)) && /* CELT NB 5ms */
		    ((encoded[sizeof(*hdr)] >> 2) != (18 << 1)) && /* CELT NB 10ms */
		    ((encoded[sizeof(*hdr)] >> 2) != (19 << 1)) && /* CELT NB 20ms */
		    ((encoded[sizeof(*hdr)] >> 2) != (21 << 1)) && /* CELT WB 5ms */
		    ((encoded[sizeof(*hdr)] >> 2) != (22 << 1)) && /* CELT WB 10ms */
		    ((encoded[sizeof(*hdr)] >> 2) != (23 << 1)) && /* CELT WB 20ms */
		    ((encoded[sizeof(*hdr)] >> 2) != (25 << 1)) && /* CELT SWB 5ms */
		    ((encoded[sizeof(*hdr)] >> 2) != (26 << 1)) && /* CELT SWB 10ms */
		    ((encoded[sizeof(*hdr)] >> 2) != (27 << 1)))   /* CELT SWB 20ms */
			return 0;

		dec->frame_size = be16toh(hdr->frame_size);
		encoded += sizeof(*hdr);
		size -= sizeof(*hdr);

		/* Check data length */
		if (size > dec->frame_size) {
			errno = EPROTO;
			return -1;
		}

		memcpy(&dec->buffer[dec->bytes_received], encoded, size);
		dec->bytes_received += size;
	} else {
		if (((dec->bytes_received + size) > dec->frame_size) ||
		    ((size != 20) && ((dec->bytes_received + size) != dec->frame_size))) {
			/* Synchronization lost */
			dec->bytes_received = 0;
			return 0;
		}

		memcpy(&dec->buffer[dec->bytes_received], encoded, size);
		dec->bytes_received += size;
	}

	if (dec->bytes_received != dec->frame_size)
		return 0;

	dec->bytes_received = 0;

	status = opus_decode(dec->state, dec->buffer, dec->frame_size, raw, NVS_MAX_FRAME_SIZE / sizeof(*raw),  0);
	if (status < 0)
	{
		errno = EPROTO;
		return -1;
	}

	return (status * sizeof(*raw));
}

static void opus_deinit(struct nvs_decoder *d)
{
	struct opus_decoder *dec = (struct opus_decoder *)d;

	opus_decoder_destroy(dec->state);
	free(dec);
}

struct nvs_decoder *decoder_opus_init(unsigned int sample_rate)
{
	struct opus_decoder *dec;
	int error;

	dec = malloc(sizeof(struct opus_decoder));
	if (!dec)
		return NULL;

	dec->state = opus_decoder_create(sample_rate, 1, &error);
	if (!dec->state || error != OPUS_OK)
		goto opus_error;

	dec->funcs.decode_pkt = opus_decode_pkt;
	dec->funcs.decoder_deinit = opus_deinit;

	dec->bytes_received = 0;

	return (struct nvs_decoder *)dec;

opus_error:
	free(dec);
	return NULL;
}

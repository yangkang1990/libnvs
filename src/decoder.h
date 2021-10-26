#ifndef __NVS_SRC_DECODER_H__
#define __NVS_SRC_DECODER_H__

struct nvs_decoder {
	int (*decode_pkt)(struct nvs_decoder *dec,
			  const uint8_t *encoded,
			  int size,
			  int16_t *raw);
	void (*decoder_deinit)(struct nvs_decoder *dec);
};

struct nvs_decoder *decoder_adpcm_init(unsigned int frame_size);
struct nvs_decoder *decoder_adpcm_upsampled_init(unsigned int frame_size);
struct nvs_decoder *decoder_bv32_init();
struct nvs_decoder *decoder_opus_init(unsigned int sample_rate);
struct nvs_decoder *decoder_msbc_init(void);
struct nvs_decoder *decoder_sbc_init(void);

#endif

#ifndef __NVS_SRC_PROTOCOL_H__
#define __NVS_SRC_PROTOCOL_H__

#define NVS_ENCODED_AUDIO_MAX_SIZE	256
#define NVS_OUTPUT_REPORT_ID		1

#define NVS_CMD_STOP			0
#define NVS_CMD_START			1

struct nvs_input_report {
	uint8_t report_id;
	uint8_t audio[NVS_ENCODED_AUDIO_MAX_SIZE];
};

struct nvs_output_report {
	uint8_t report_id;
	uint8_t cmd;
};

static void put_cmd(struct nvs_output_report *report, uint8_t cmd)
{
	report->report_id = NVS_OUTPUT_REPORT_ID;
	report->cmd = cmd;
}

#endif

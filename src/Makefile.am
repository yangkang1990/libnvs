lib_LTLIBRARIES = libnvs.la

INCLUDES = -I$(top_builddir)/include
LIBS = $(ADPCM_LIBS) $(BROADVOICE_LIBS) $(OPUS_LIBS) $(SBC_LIBS)

libnvs_la_SOURCES = \
		libnvs.c \
		hidraw.c \
		adpcm_decoder.c \
		adpcm_upsampled_decoder.c \
		bv32_decoder.c \
		opus_decoder.c \
		sbc_decoder.c \
		upsampler/upsampler_v1.c

libnvs_la_CFLAGS = -fvisibility=hidden -Wall
libnvs_la_LDFLAGS = -version-info 1:0:0

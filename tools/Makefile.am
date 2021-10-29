bin_PROGRAMS = nvs-cat nvs-4mod

INCLUDES = -I$(top_builddir)/include -Iwav_pcm

nvs_cat_LDADD = $(top_builddir)/src/libnvs.la
nvs_cat_SOURCES = nvs-cat.c
nvs_cat_CFLAGS = -Wall


nvs_4mod_LDADD = $(top_builddir)/src/libnvs.la -linput -levdev -ludev -lpthread
nvs_4mod_SOURCES = nvs-4mod.c wav_pcm.c
nvs_4mod_CFLAGS = -Wall 



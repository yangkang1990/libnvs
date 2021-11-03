/*
 * Copyright © 2014 Red Hat, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <libudev.h>
#include "linux/input.h"
#include <sys/ioctl.h>

#include <libinput.h>
#include <libevdev-1.0/libevdev/libevdev.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "../include/nvs.h"
#include <pthread.h>
#include "wav_pcm.h"



/*proc*/
#include <dirent.h>
#include <sys/types.h>


//#include "shared.h"

uint32_t start_time;
static const uint32_t screen_width = 100;
static const uint32_t screen_height = 100;
//struct tools_context context;
static unsigned int stop = 0;


static char event_dev[64] = {0};
static int  do_record = 0;
static pthread_condattr_t input_event_attr;
static pthread_cond_t  input_event_cond = PTHREAD_COND_INITIALIZER;
static pthread_t input_event_thread;
static pthread_mutex_t input_event_lock = PTHREAD_MUTEX_INITIALIZER;


#define BLE_HDI_NODE "hidraw0"
//#define ADPCM_SAMPLE_RATE 	(7936)
#define ADPCM_SAMPLE_RATE 	(8000)
#define ADPCM_CHANNEL_NUM	(1)
#define ADPCM_BITS_DEPTH    (16)
#define ADPCM_FILENAME 	"/opt/www/nanovoice.adpcm"
#define WAV_FILENAME 	"/opt/www/nanovoice.wav"


static void
print_event_header(struct libinput_event *ev)
{
	struct libinput_device *dev = libinput_event_get_device(ev);
	const char *type = NULL;

	switch(libinput_event_get_type(ev)) {
	case LIBINPUT_EVENT_NONE:
		abort();
	case LIBINPUT_EVENT_DEVICE_ADDED:
		type = "DEVICE_ADDED";
		break;
	case LIBINPUT_EVENT_DEVICE_REMOVED:
		type = "DEVICE_REMOVED";
		break;
	case LIBINPUT_EVENT_KEYBOARD_KEY:
		type = "KEYBOARD_KEY";
		memset(event_dev, 0x00, 64);
		//memcpy(event_dev, libinput_device_get_sysname(dev), sizeof(libinput_device_get_sysname(dev)));
		snprintf(event_dev, 64, "input/%s", libinput_device_get_sysname(dev));
		printf("event_dev=%s\n", event_dev);
		break;
	case LIBINPUT_EVENT_POINTER_MOTION:
		type = "POINTER_MOTION";
		break;
	case LIBINPUT_EVENT_POINTER_MOTION_ABSOLUTE:
		type = "POINTER_MOTION_ABSOLUTE";
		break;
	case LIBINPUT_EVENT_POINTER_BUTTON:
		type = "POINTER_BUTTON";
		break;
	case LIBINPUT_EVENT_POINTER_AXIS:
		type = "POINTER_AXIS";
		break;
	case LIBINPUT_EVENT_TOUCH_DOWN:
		type = "TOUCH_DOWN";
		break;
	case LIBINPUT_EVENT_TOUCH_MOTION:
		type = "TOUCH_MOTION";
		break;
	case LIBINPUT_EVENT_TOUCH_UP:
		type = "TOUCH_UP";
		break;
	case LIBINPUT_EVENT_TOUCH_CANCEL:
		type = "TOUCH_CANCEL";
		break;
	case LIBINPUT_EVENT_TOUCH_FRAME:
		type = "TOUCH_FRAME";
		break;
	case LIBINPUT_EVENT_GESTURE_SWIPE_BEGIN:
		type = "GESTURE_SWIPE_BEGIN";
		break;
	case LIBINPUT_EVENT_GESTURE_SWIPE_UPDATE:
		type = "GESTURE_SWIPE_UPDATE";
		break;
	case LIBINPUT_EVENT_GESTURE_SWIPE_END:
		type = "GESTURE_SWIPE_END";
		break;
	case LIBINPUT_EVENT_GESTURE_PINCH_BEGIN:
		type = "GESTURE_PINCH_BEGIN";
		break;
	case LIBINPUT_EVENT_GESTURE_PINCH_UPDATE:
		type = "GESTURE_PINCH_UPDATE";
		break;
	case LIBINPUT_EVENT_GESTURE_PINCH_END:
		type = "GESTURE_PINCH_END";
		break;
	}

	printf("yk:%-7s	%s	", libinput_device_get_sysname(dev), type);
}

static void
print_event_time(uint32_t time)
{
	printf("%+6.2fs	", (time - start_time) / 1000.0);
}

static void
print_device_notify(struct libinput_event *ev)
{
	struct libinput_device *dev = libinput_event_get_device(ev);
	struct libinput_seat *seat = libinput_device_get_seat(dev);
	struct libinput_device_group *group;
	double w, h;
	uint32_t scroll_methods, click_methods;
	static int next_group_id = 0;
	intptr_t group_id;

	group = libinput_device_get_device_group(dev);
	group_id = (intptr_t)libinput_device_group_get_user_data(group);
	if (!group_id) {
		group_id = ++next_group_id;
		libinput_device_group_set_user_data(group, (void*)group_id);
	}

	printf("%-33s %5s %7s group%d",
	       libinput_device_get_name(dev),
	       libinput_seat_get_physical_name(seat),
	       libinput_seat_get_logical_name(seat),
	       (int)group_id);

	printf(" cap:");
	if (libinput_device_has_capability(dev,
					   LIBINPUT_DEVICE_CAP_KEYBOARD))
		printf("k");
	if (libinput_device_has_capability(dev,
					   LIBINPUT_DEVICE_CAP_POINTER))
		printf("p");
	if (libinput_device_has_capability(dev,
					   LIBINPUT_DEVICE_CAP_TOUCH))
		printf("t");
	if (libinput_device_has_capability(dev,
					   LIBINPUT_DEVICE_CAP_GESTURE))
		printf("g");

	if (libinput_device_get_size(dev, &w, &h) == 0)
		printf("\tsize %.2f/%.2fmm", w, h);

	if (libinput_device_config_tap_get_finger_count(dev)) {
	    printf(" tap");
	    if (libinput_device_config_tap_get_drag_lock_enabled(dev))
		    printf("(dl on)");
	    else
		    printf("(dl off)");
	}
	if (libinput_device_config_left_handed_is_available(dev))
	    printf(" left");
	if (libinput_device_config_scroll_has_natural_scroll(dev))
	    printf(" scroll-nat");
	if (libinput_device_config_calibration_has_matrix(dev))
	    printf(" calib");

	scroll_methods = libinput_device_config_scroll_get_methods(dev);
	if (scroll_methods != LIBINPUT_CONFIG_SCROLL_NO_SCROLL) {
		printf(" scroll");
		if (scroll_methods & LIBINPUT_CONFIG_SCROLL_2FG)
			printf("-2fg");
		if (scroll_methods & LIBINPUT_CONFIG_SCROLL_EDGE)
			printf("-edge");
		if (scroll_methods & LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN)
			printf("-button");
	}

	click_methods = libinput_device_config_click_get_methods(dev);
	if (click_methods != LIBINPUT_CONFIG_CLICK_METHOD_NONE) {
		printf(" click");
		if (click_methods & LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS)
			printf("-buttonareas");
		if (click_methods & LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER)
			printf("-clickfinger");
	}

	if (libinput_device_config_dwt_is_available(dev)) {
		if (libinput_device_config_dwt_get_enabled(dev) ==
		    LIBINPUT_CONFIG_DWT_ENABLED)
			printf(" dwt-on");
		else
			printf(" dwt-off)");
	}

	printf("\n");

}

static void
print_key_event(struct libinput_event *ev)
{
	struct libinput_event_keyboard *k = libinput_event_get_keyboard_event(ev);
	enum libinput_key_state state;
	uint32_t key;
	const char *keyname;

	print_event_time(libinput_event_keyboard_get_time(k));
	state = libinput_event_keyboard_get_key_state(k);

	key = libinput_event_keyboard_get_key(k);
	keyname = libevdev_event_code_get_name(EV_KEY, key);
	printf("%s (%d) %s\n",
	       keyname ? keyname : "???",
	       key,
	       state == LIBINPUT_KEY_STATE_PRESSED ? "pressed" : "released");

	if((!strcmp(keyname,"KEY_SEARCH"))&&(state == LIBINPUT_KEY_STATE_PRESSED))
	{
		printf("send input_event_cond\n");
		do_record = 1;
		pthread_cond_broadcast(&input_event_cond);
	}
	else if((!strcmp(keyname,"KEY_SEARCH"))&&(state == LIBINPUT_KEY_STATE_RELEASED))
	{
		printf("send stop input_event_cond\n");
		do_record = 0;
	}
}

static void
print_motion_event(struct libinput_event *ev)
{
	struct libinput_event_pointer *p = libinput_event_get_pointer_event(ev);
	double x = libinput_event_pointer_get_dx(p);
	double y = libinput_event_pointer_get_dy(p);

	print_event_time(libinput_event_pointer_get_time(p));

	printf("%6.2f/%6.2f\n", x, y);
}

static void
print_absmotion_event(struct libinput_event *ev)
{
	struct libinput_event_pointer *p = libinput_event_get_pointer_event(ev);
	double x = libinput_event_pointer_get_absolute_x_transformed(
		p, screen_width);
	double y = libinput_event_pointer_get_absolute_y_transformed(
		p, screen_height);

	print_event_time(libinput_event_pointer_get_time(p));
	printf("%6.2f/%6.2f\n", x, y);
}

static void
print_button_event(struct libinput_event *ev)
{
	struct libinput_event_pointer *p = libinput_event_get_pointer_event(ev);
	enum libinput_button_state state;
	const char *buttonname;
	int button;

	print_event_time(libinput_event_pointer_get_time(p));

	button = libinput_event_pointer_get_button(p);
	buttonname = libevdev_event_code_get_name(EV_KEY, button);

	state = libinput_event_pointer_get_button_state(p);
	printf("%s (%d) %s, seat count: %u\n",
	       buttonname ? buttonname : "???",
	       button,
	       state == LIBINPUT_BUTTON_STATE_PRESSED ? "pressed" : "released",
	       libinput_event_pointer_get_seat_button_count(p));
}

static void
print_axis_event(struct libinput_event *ev)
{
	struct libinput_event_pointer *p = libinput_event_get_pointer_event(ev);
	double v = 0, h = 0;
	const char *have_vert = "",
		   *have_horiz = "";

	if (libinput_event_pointer_has_axis(p,
				LIBINPUT_POINTER_AXIS_SCROLL_VERTICAL)) {
		v = libinput_event_pointer_get_axis_value(p,
			      LIBINPUT_POINTER_AXIS_SCROLL_VERTICAL);
		have_vert = "*";
	}
	if (libinput_event_pointer_has_axis(p,
				LIBINPUT_POINTER_AXIS_SCROLL_HORIZONTAL)) {
		h = libinput_event_pointer_get_axis_value(p,
			      LIBINPUT_POINTER_AXIS_SCROLL_HORIZONTAL);
		have_horiz = "*";
	}
	print_event_time(libinput_event_pointer_get_time(p));
	printf("vert %.2f%s horiz %.2f%s\n", v, have_vert, h, have_horiz);
}

static void
print_touch_event_without_coords(struct libinput_event *ev)
{
	struct libinput_event_touch *t = libinput_event_get_touch_event(ev);

	print_event_time(libinput_event_touch_get_time(t));
	printf("\n");
}

static void
print_touch_event_with_coords(struct libinput_event *ev)
{
	struct libinput_event_touch *t = libinput_event_get_touch_event(ev);
	double x = libinput_event_touch_get_x_transformed(t, screen_width);
	double y = libinput_event_touch_get_y_transformed(t, screen_height);
	double xmm = libinput_event_touch_get_x(t);
	double ymm = libinput_event_touch_get_y(t);

	print_event_time(libinput_event_touch_get_time(t));

	printf("%d (%d) %5.2f/%5.2f (%5.2f/%5.2fmm)\n",
	       libinput_event_touch_get_slot(t),
	       libinput_event_touch_get_seat_slot(t),
	       x, y,
	       xmm, ymm);
}

static void
print_gesture_event_without_coords(struct libinput_event *ev)
{
	struct libinput_event_gesture *t = libinput_event_get_gesture_event(ev);
	int finger_count = libinput_event_gesture_get_finger_count(t);
	int cancelled = 0;
	enum libinput_event_type type;

	type = libinput_event_get_type(ev);

	if (type == LIBINPUT_EVENT_GESTURE_SWIPE_END ||
	    type == LIBINPUT_EVENT_GESTURE_PINCH_END)
	    cancelled = libinput_event_gesture_get_cancelled(t);

	print_event_time(libinput_event_gesture_get_time(t));
	printf("%d%s\n", finger_count, cancelled ? " cancelled" : "");
}

static void
print_gesture_event_with_coords(struct libinput_event *ev)
{
	struct libinput_event_gesture *t = libinput_event_get_gesture_event(ev);
	double dx = libinput_event_gesture_get_dx(t);
	double dy = libinput_event_gesture_get_dy(t);
	double dx_unaccel = libinput_event_gesture_get_dx_unaccelerated(t);
	double dy_unaccel = libinput_event_gesture_get_dy_unaccelerated(t);

	print_event_time(libinput_event_gesture_get_time(t));

	printf("%d %5.2f/%5.2f (%5.2f/%5.2f unaccelerated)",
	       libinput_event_gesture_get_finger_count(t),
	       dx, dy, dx_unaccel, dy_unaccel);

	if (libinput_event_get_type(ev) ==
	    LIBINPUT_EVENT_GESTURE_PINCH_UPDATE) {
		double scale = libinput_event_gesture_get_scale(t);
		double angle = libinput_event_gesture_get_angle_delta(t);

		printf(" %5.2f @ %5.2f\n", scale, angle);
	} else {
		printf("\n");
	}
}

static int
handle_and_print_events(struct libinput *li)
{
	int rc = -1;
	struct libinput_event *ev;

	libinput_dispatch(li);
	while ((ev = libinput_get_event(li))) {
		print_event_header(ev);

		switch (libinput_event_get_type(ev)) {
		case LIBINPUT_EVENT_NONE:
			abort();
		case LIBINPUT_EVENT_DEVICE_ADDED:
		case LIBINPUT_EVENT_DEVICE_REMOVED:
			print_device_notify(ev);
			//tools_device_apply_config(libinput_event_get_device(ev),
			//			  &context.options);
			break;
		case LIBINPUT_EVENT_KEYBOARD_KEY:
			print_key_event(ev);
			break;
		case LIBINPUT_EVENT_POINTER_MOTION:
			print_motion_event(ev);
			break;
		case LIBINPUT_EVENT_POINTER_MOTION_ABSOLUTE:
			print_absmotion_event(ev);
			break;
		case LIBINPUT_EVENT_POINTER_BUTTON:
			print_button_event(ev);
			break;
		case LIBINPUT_EVENT_POINTER_AXIS:
			print_axis_event(ev);
			break;
		case LIBINPUT_EVENT_TOUCH_DOWN:
			print_touch_event_with_coords(ev);
			break;
		case LIBINPUT_EVENT_TOUCH_MOTION:
			print_touch_event_with_coords(ev);
			break;
		case LIBINPUT_EVENT_TOUCH_UP:
			print_touch_event_without_coords(ev);
			break;
		case LIBINPUT_EVENT_TOUCH_CANCEL:
			print_touch_event_without_coords(ev);
			break;
		case LIBINPUT_EVENT_TOUCH_FRAME:
			print_touch_event_without_coords(ev);
			break;
		case LIBINPUT_EVENT_GESTURE_SWIPE_BEGIN:
			print_gesture_event_without_coords(ev);
			break;
		case LIBINPUT_EVENT_GESTURE_SWIPE_UPDATE:
			print_gesture_event_with_coords(ev);
			break;
		case LIBINPUT_EVENT_GESTURE_SWIPE_END:
			print_gesture_event_without_coords(ev);
			break;
		case LIBINPUT_EVENT_GESTURE_PINCH_BEGIN:
			print_gesture_event_without_coords(ev);
			break;
		case LIBINPUT_EVENT_GESTURE_PINCH_UPDATE:
			print_gesture_event_with_coords(ev);
			break;
		case LIBINPUT_EVENT_GESTURE_PINCH_END:
			print_gesture_event_without_coords(ev);
			break;
		}

		libinput_event_destroy(ev);
		libinput_dispatch(li);
		rc = 0;
	}
	return rc;
}

static void
sighandler(int signal, siginfo_t *siginfo, void *userdata)
{
	stop = 1;
}

static void
mainloop(struct libinput *li)
{
	struct pollfd fds;
	struct sigaction act;

	fds.fd = libinput_get_fd(li);
	fds.events = POLLIN;
	fds.revents = 0;

	memset(&act, 0, sizeof(act));
	act.sa_sigaction = sighandler;
	act.sa_flags = SA_SIGINFO;

	if (sigaction(SIGINT, &act, NULL) == -1) {
		fprintf(stderr, "Failed to set up signal handling (%s)\n",
				strerror(errno));
		return;
	}


	/* Handle already-pending device added events */
	if (handle_and_print_events(li))
		fprintf(stderr, "Expected device added events on startup but got none. "
				"Maybe you don't have the right permissions?\n");

	while (!stop && poll(&fds, 1, -1) > -1)
		handle_and_print_events(li);
	
	
}

static int open_restricted(const char *path, int flags, void *user_data)
{
	//const struct tools_context *context = user_data;
	int fd = open(path, flags);
#if 0
	if (fd < 0)
		fprintf(stderr, "Failed to open %s (%s)\n",
			path, strerror(errno));
	else if (context->options.grab &&
		 ioctl(fd, EVIOCGRAB, (void*)1) == -1)
		fprintf(stderr, "Grab requested, but failed for %s (%s)\n",
			path, strerror(errno));
#endif
	return fd < 0 ? -errno : fd;
}

static void close_restricted(int fd, void *user_data)
{
	close(fd);
}

const struct libinput_interface interface = {
	.open_restricted = open_restricted,
	.close_restricted = close_restricted,
};

static void log_handler(struct libinput *li,
	    enum libinput_log_priority priority,
	    const char *format,
	    va_list args)
{
	vprintf(format, args);
}


static struct libinput * open_backend(void)
{
		struct libinput *li;
		struct udev *udev = udev_new();
		int verbose = 1;
		const char *seat = "seat0";
	
		if (!udev) {
			fprintf(stderr, "Failed to initialize udev\n");
			return NULL;
		}
	
		li = libinput_udev_create_context(&interface, NULL, udev);
		if (!li) {
			fprintf(stderr, "Failed to initialize context from udev\n");
			goto out;
		}
	
		if (verbose) {
			libinput_log_set_handler(li, log_handler);
			libinput_log_set_priority(li, LIBINPUT_LOG_PRIORITY_DEBUG);
		}
		if(seat!=NULL)
			printf("seat is %s\n", seat);
		else
			printf("seat is null\n");
		if (libinput_udev_assign_seat(li, seat)) {
			fprintf(stderr, "Failed to set seat\n");
			libinput_unref(li);
			li = NULL;
			goto out;
		}
	
	out:
		udev_unref(udev);
		return li;

}


int input_test(void)
{
	struct libinput *li;
	struct timespec tp;

	clock_gettime(CLOCK_MONOTONIC, &tp);
	start_time = tp.tv_sec * 1000 + tp.tv_nsec / 1000000;

	li = open_backend();
	mainloop(li);

	libinput_unref(li);	
}

#if  0
int
main(int argc, char **argv)
{
	struct libinput *li;
	struct timespec tp;

	clock_gettime(CLOCK_MONOTONIC, &tp);
	start_time = tp.tv_sec * 1000 + tp.tv_nsec / 1000000;

	tools_init_context(&context);

	if (tools_parse_args(argc, argv, &context))
		return 1;

	li = tools_open_backend(&context);
	if (!li)
		return 1;

	mainloop(li);

	libinput_unref(li);

	return 0;
}
#endif

static struct nvs_device *dev;

void termination_handler(int signum)
{
	if (dev)
		nvs_close(dev);
	_exit(0);
}

int install_termination_handler(void)
{
	struct sigaction sa;
	int ret;

	sa.sa_handler = termination_handler;
	sigemptyset (&sa.sa_mask);
	sa.sa_flags = 0;

	ret = sigaction(SIGINT, &sa, NULL);
	if (ret)
		return ret;

	ret = sigaction(SIGHUP, &sa, NULL);
	if (ret)
		return ret;

	ret = sigaction(SIGTERM, &sa, NULL);

	return ret;
}


int  AM_TIME_GetTimeSpecTimeout(int timeout, struct timespec *ts)
{
    struct timespec ots;
    int left, diff;

    clock_gettime(CLOCK_MONOTONIC, &ots);

    ts->tv_sec  = ots.tv_sec + timeout/1000;
    ts->tv_nsec = ots.tv_nsec;

    left = timeout % 1000;
    left *= 1000000;
    diff = 1000000000-ots.tv_nsec;

    if(diff<=left)
    {
        ts->tv_sec++;
        ts->tv_nsec = left-diff;
    }
    else
    {
        ts->tv_nsec += left;
    }

    return 0;
}



static void* input_event_thread_entry(void *arg)
{
	uint8_t buffer[NVS_MAX_FRAME_SIZE];
	ssize_t written;
	int size, rc;
	int fd;
	
	printf("[yk_notify]input_event_thread_entry\n");	
	
	while(1)
	{
		struct timespec ts;
		pthread_mutex_lock(&input_event_lock);
		AM_TIME_GetTimeSpecTimeout(1000000, &ts);
		printf("[yk_notify]received cond wait\n");	
		//pthread_cond_timedwait(&input_event_cond, &input_event_lock, &ts);
		pthread_cond_wait(&input_event_cond, &input_event_lock);
		printf("[yk_notify]received cond\n");		
		pthread_mutex_unlock(&input_event_lock);

		printf("[yk_notify]nvs_open\n");	
		dev = nvs_open(BLE_HDI_NODE);
		if (!dev) {
			perror("nvs_open");
			return -1;
		}
		
		if(access(ADPCM_FILENAME,F_OK)==0)
		{
	       if(remove(ADPCM_FILENAME) == 0)
	          printf("Old File %s  deleted.\n", ADPCM_FILENAME);
	        else
	          fprintf(stderr, "Error deleting the file %s.\n", ADPCM_FILENAME);		
		}
		
		fd = open(ADPCM_FILENAME,O_WRONLY|O_CREAT);
		while (do_record) {
			memset(buffer, 0x00, NVS_MAX_FRAME_SIZE);
			size = nvs_get_audio(dev, buffer);
			if (size < 0 && size != -EAGAIN) {
				nvs_close(dev);
				return size;
			}
			//printf("nvs_get_audio size=%d\n", size);
			written = 0;
			while (written < size)
				written += write(fd, buffer + written, size - written);
			
		}
		printf("[yk_notify]close voice file\n");	
		close(fd);
		nvs_close(dev);
		printf("[yk_notify]nvs_close\n");
		
		pcm_to_wav(WAV_FILENAME, ADPCM_FILENAME, ADPCM_SAMPLE_RATE, ADPCM_CHANNEL_NUM, ADPCM_BITS_DEPTH);
		printf("[yk_notify]wav voice file %s generated\n", WAV_FILENAME);	
	}

}



int pcm_to_wav(char* fOut, char* fIn, size_t sample_rate,size_t num_channels,size_t bit_depth)
{
	size_t pcm_size;
	FILE *ifp, *ofp;
	
	if((!fIn) && ((access(fIn,F_OK))!=0))
	{
		printf("file not exist!\n");
		return -1;
	}
		
	if(!fOut)
	{
		printf("invalid param!\n");
	}
	else if(access(fOut,F_OK)==0)
	{
       if(remove(fOut) == 0)
          printf("Old File %s  deleted.\n", fOut);
        else
          fprintf(stderr, "Error deleting the file %s.\n", fOut);		
	}

	ifp = fopen(fIn, "rb+");			
	ofp = fopen(fOut, "wb+");			
	fseek(ifp, 0, SEEK_END);			
	pcm_size = ftell(ifp);			
	fseek(ifp, 0, SEEK_SET);
	write_header(ofp, pcm_size, num_channels, sample_rate, bit_depth);
	write_to_stream(ifp, ofp, pcm_size);
	fclose(ifp);
	fclose(ofp);
	return 0;	
	
}

int proc_find(const char* name) 
{
    DIR* dir;
    struct dirent* ent;
    char* endptr;
    char buf[512];
	int ret = -1;

    if (!(dir = opendir("/proc"))) {
        perror("can't open /proc");
        return -1;
    }

    while((ent = readdir(dir)) != NULL) {
        /* if endptr is not a null character, the directory is not
         * entirely numeric, so ignore it */
        long lpid = strtol(ent->d_name, &endptr, 10);
        if (*endptr != '\0') {
            continue;
        }

        /* try to open the cmdline file */
        snprintf(buf, sizeof(buf), "/proc/%ld/cmdline", lpid);
        FILE* fp = fopen(buf, "r");

        if (fp) {
            if (fgets(buf, sizeof(buf), fp) != NULL) {
#if 0				
                /* check the first token in the file, the program name */
                char* first = strtok(buf, " ");
                if (!strcmp(first, name)) {
                    fclose(fp);
                    closedir(dir);
                    return (pid_t)lpid;
                }
#endif	
				if(!strstr(buf, name))
				{
					printf("[yk]global app is running");
                    fclose(fp);
                    closedir(dir);
                    return 0;
				}
            }
            fclose(fp);
        }

    }

    closedir(dir);
    return -1;
}


int main(int argc, char **argv)
{
	int rc;
	struct libinput *li;
	struct timespec tp;

	setvbuf(stdout, NULL, _IOLBF, 0);
	clock_gettime(CLOCK_MONOTONIC, &tp);
	start_time = tp.tv_sec * 1000 + tp.tv_nsec / 1000000;

#if 0
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <hidraw device> <input event>\n", argv[0]);
		fprintf(stderr, "Example: %s hidraw0 event5\n", argv[0]);
		return -1;
	}
#endif	
	printf("demo in\n");
	//if (install_termination_handler()) {
	//	perror("install_termination_handler");
	//	return -1;
	//} 

#if 0

	while(1)
	{

		if(proc_find("GlobalApp")==0)
		{
			if(access("/dev/hidraw0",F_OK)==0)
			{
				sleep(2);
				break;	
			}		
			else
			{
				sleep(2);
			}
		}
		else
		{
			sleep(2);
		}		
	}
#else
	while(1)
	{
		if(access("/dev/hidraw0",F_OK)==0)
		{
			break;	
		}		
		else
		{
			sleep(1);
		}
	}

#endif
	

	printf("event test begin"); 
	pthread_condattr_init(&input_event_attr);
	pthread_condattr_setclock(&input_event_attr, CLOCK_MONOTONIC);
	pthread_cond_init(&input_event_cond, &input_event_attr);	
	
    rc = pthread_create(&input_event_thread, NULL, input_event_thread_entry, NULL);
	pthread_setname_np(input_event_thread, "input_event_thread_entry");


	/*************************/
	li = open_backend();
	mainloop(li);
	
	libinput_unref(li);	
	pthread_join(input_event_thread, NULL);
	printf("event test end");	

	
	//input_test();


}


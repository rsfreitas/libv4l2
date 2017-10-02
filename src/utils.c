
/*
 * Description:
 *
 * Author: Rodrigo Freitas
 * Created at: Fri Feb 10 09:06:20 2017
 * Project: libv4l2
 *
 * Copyright (C) 2017 Rodrigo Freitas
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#include <stdlib.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "libv4l2.h"

int _ioctl(int fd, int request, void *argp)
{
    int r;

    do {
        r = ioctl(fd, request, argp);
    } while ((r == -1) && (errno == EINTR));

    return r;
}

int v4l2_format_to_videodev(enum v4l2_image_format format)
{
    switch (format) {
        case V4L2_IMAGE_FMT_GRAY:
            return V4L2_PIX_FMT_GREY;

        case V4L2_IMAGE_FMT_BGR24:
            return V4L2_PIX_FMT_BGR24;

        case V4L2_IMAGE_FMT_YUV420:
            return V4L2_PIX_FMT_YUV420;

        case V4L2_IMAGE_FMT_YUYV:
            return V4L2_PIX_FMT_YUYV;

        default:
            break;
    }

    return -1;
}

int v4l2_setting_to_videodev(enum v4l2_setting setting)
{
    switch (setting) {
        case V4L2_SETTING_BRIGHTNESS:
            return V4L2_CID_BRIGHTNESS;

        case V4L2_SETTING_CONTRAST:
            return V4L2_CID_CONTRAST;

        case V4L2_SETTING_SATURATION:
            return V4L2_CID_SATURATION;

        case V4L2_SETTING_HUE:
            return V4L2_CID_HUE;

        default:
            break;
    }

    return -1;
}

bool is_supported_setting(enum v4l2_setting setting)
{
    switch (setting) {
        case V4L2_SETTING_BRIGHTNESS:
        case V4L2_SETTING_CONTRAST:
        case V4L2_SETTING_SATURATION:
        case V4L2_SETTING_HUE:
            return true;

        default:
            break;
    }

    return false;
}

bool is_supported_format(enum v4l2_image_format format)
{
    switch (format) {
        case V4L2_IMAGE_FMT_GRAY:
        case V4L2_IMAGE_FMT_BGR24:
        case V4L2_IMAGE_FMT_YUV420:
        case V4L2_IMAGE_FMT_YUYV:
            return true;

        default:
            break;
    }

    return false;
}

bool is_supported_model(enum v4l2_model model)
{
    switch (model) {
        case V4L2_MODEL_BT878_CARD:
        case V4L2_MODEL_USB_WEBCAM:
        case V4L2_MODEL_RPI_CAMERA:
            return true;

        default:
            break;
    }

    return false;
}

/** Unused function */
bool is_supported_channel(enum v4l2_channel channel)
{
    switch (channel) {
        case V4L2_CHANNEL_TUNER:
        case V4L2_CHANNEL_COMPOSITE:
        case V4L2_CHANNEL_SVIDEO:
            return true;

        default:
            break;
    }

    return false;
}

static int open_video_device(const char *device)
{
    struct stat st;

    if (stat(device, &st) == -1)
        return -1;

    if (!S_ISCHR(st.st_mode))
        return -1;

    return open(device, O_RDWR | O_NONBLOCK);
}

int close_video_device(int fd)
{
    return close(fd);
}

int v4l2_open_device(struct v4l2_s *v4l2, const char *device, bool loopback)
{
    struct v4l2_capability cap;

    v4l2->fd = open_video_device(device);

    if (v4l2->fd < 0) {
        errno_set(V4L2_OPEN_FAILED);
        return -1;
    }

    if (loopback == false) {
        if (_ioctl(v4l2->fd, VIDIOC_QUERYCAP, &cap) == -1) {
            errno_set(V4L2_QUERYCAP_ERROR);
            return -1;
        }

        if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
            errno_set(V4L2_NO_CAP_VIDEO_CAPTURE);
            return -1;
        }

        if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
            errno_set(V4L2_NO_CAP_STREAMING);
            return -1;
        }

        v4l2->capabilities = cap.capabilities;
        v4l2->version = cap.version;
        v4l2->card = strdup((const char *)cap.card);
        v4l2->driver = strdup((const char *)cap.driver);
        v4l2->bus_info = strdup((const char *)cap.bus_info);
    }

    v4l2->device = strdup(device);

    return 0;
}

static int v4l2_stop_device(struct v4l2_s *v4l2)
{
    if (v4l2->device_initialized == false)
        return 0;

    return 0;
}

static void destroy_v4l2(const struct cl_ref_s *ref)
{
    struct v4l2_s *v = cl_container_of(ref, struct v4l2_s, ref);

    if (NULL == v)
        return;

    grab_stop(v);

    if (v->mmap_initialized == true)
        mmap_uninit(v);

    /* uninit device */
    if (v->device_initialized == true)
        v4l2_stop_device(v);

    if (v->device != NULL)
        free(v->device);

    if (v->card != NULL)
        free(v->card);

    if (v->bus_info != NULL)
        free(v->bus_info);

    if (v->driver != NULL)
        free(v->driver);

    if (v->fd != -1)
        close_video_device(v->fd);

    if (v->parent != NULL)
        v4l2_unref(v->parent);

    if (v->loopback_thread != NULL)
        loopback_stop(v);

    free(v);
    v = NULL;
}

struct v4l2_s *new_v4l2_s(void)
{
    struct v4l2_s *v = NULL;

    v = calloc(1, sizeof(struct v4l2_s));

    if (NULL == v) {
        errno_set(V4L2_ERROR_MALLOC);
        return NULL;
    }

    v->fd = -1;
    v->device_initialized = false;
    v->parent = NULL;
    v->loopback_thread = NULL;

    /* Initialize reference count */
    v->ref.count = 1;
    v->ref.free = destroy_v4l2;

    return v;
}

void lock_init(struct v4l2_s *v4l2)
{
    pthread_rwlockattr_t attr;

    if (NULL == v4l2)
        return;

    /* Creates the read/write lock to the loopback devices */
    pthread_rwlockattr_init(&attr);
    pthread_rwlockattr_setkind_np(&attr,
                                  PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);

    pthread_rwlock_init(&v4l2->lock, &attr);

    /* Creates the continuous grabbing mutex/condition */
    pthread_mutex_init(&v4l2->grab_mutex, NULL);
    pthread_cond_init(&v4l2->grab_cond, NULL);
}

void lock_uninit(struct v4l2_s *v4l2)
{
    if (NULL == v4l2)
        return;

    pthread_cond_destroy(&v4l2->grab_cond);
    pthread_mutex_destroy(&v4l2->grab_mutex);
    pthread_rwlock_destroy(&v4l2->lock);
}

void read_lock(struct v4l2_s *v4l2)
{
    if (NULL == v4l2)
        return;

    pthread_rwlock_rdlock(&v4l2->lock);
}

void read_unlock(struct v4l2_s *v4l2)
{
    if (NULL == v4l2)
        return;

    pthread_rwlock_unlock(&v4l2->lock);
}

void write_lock(struct v4l2_s *v4l2)
{
    if (NULL == v4l2)
        return;

    pthread_rwlock_wrlock(&v4l2->lock);
}

void write_unlock(struct v4l2_s *v4l2)
{
    if (NULL == v4l2)
        return;

    pthread_rwlock_unlock(&v4l2->lock);
}

bool is_setting_value_valid(int value)
{
    if ((value >= 0) && (value <= DEFAULT_MAX_CTRL_RANGE))
        return true;

    return false;
}


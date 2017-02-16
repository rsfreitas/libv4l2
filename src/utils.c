
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

#include "libv4l2.h"

static void destroy_v4l2(const struct cref_s *ref)
{
    struct v4l2_s *v = cl_container_of(ref, struct v4l2_s, ref);

    if (NULL == v)
        return;

    free(v);
}

struct v4l2_s *new_v4l2_s(void)
{
    struct v4l2_s *v = NULL;

    v = calloc(1, sizeof(struct v4l2_s));

    if (NULL == v) {
        errno_set(V4L2_ERROR_MALLOC);
        return NULL;
    }

    /* Initialize reference count */
    v->ref.count = 1;
    v->ref.free = destroy_v4l2;

    return v;
}

int _ioctl(int fd, int request, void *argp)
{
    int r;

    do {
        r = ioctl(fd, request, argp);
    } while ((r == -1) && (errno == EINTR));

    return r;
}

int v4l2_format_to_videodev2(enum v4l2_image_format format)
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


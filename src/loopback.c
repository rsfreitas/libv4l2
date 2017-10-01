
/*
 * Description:
 *
 * Author: Rodrigo Freitas
 * Created at: Sat Sep 30 18:13:09 2017
 * Project: libv4l2
 *
 * Copyright (c) 2017 All rights reserved
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

#include <unistd.h>

#include "libv4l2.h"

/*
 *
 * Internal functions
 *
 */

static int v4l2_init_loopback_device(struct v4l2_s *loopback,
    const struct v4l2_s *source)
{
	struct v4l2_format fmt;
	struct v4l2_streamparm setfps;

    MEMSET(fmt);
    fmt.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    fmt.fmt.pix.width = source->current_image.width;
    fmt.fmt.pix.height = source->current_image.height;
    fmt.fmt.pix.pixelformat = v4l2_format_to_videodev(source->current_image.format);
    fmt.fmt.pix.field = V4L2_FIELD_ANY;

    if (_ioctl(loopback->fd, VIDIOC_S_FMT, &fmt) < 0) {
        errno_set(V4L2_ERROR_SET_FMT);
	    return 1;
    }

    MEMSET(setfps);
    setfps.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    setfps.parm.capture.timeperframe.numerator = 1;
    setfps.parm.capture.timeperframe.denominator = DEFAULT_LOOPBACK_FPS;

    if (_ioctl(loopback->fd, VIDIOC_S_PARM, &setfps) == -1) {
        errno_set(V4L2_ERROR_SET_STREAMING_PARAM);
        return 1;
    }

	return 0;
}

static int loopback_write_frame(struct v4l2_s *loopback,
    const struct v4l2_image_s *image)
{
    return write(loopback->fd, image->data, image->data_size);
}

/*
 *
 * Exported API
 *
 */

__PUB_API__ v4l2_t *v4l2_loopback_open(const char *device, const v4l2_t *source)
{
    struct v4l2_s *v4l2 = NULL;

    errno_clear();

    if ((NULL == device) || (NULL == source)) {
        errno_set(V4L2_NULL_ARG);
        return NULL;
    }

    v4l2 = new_v4l2_s();

    if (NULL == v4l2)
        return NULL;

    if (v4l2_open_device(v4l2, device, true) < 0)
        return NULL;

    if (v4l2_init_loopback_device(v4l2, source) < 0)
        return NULL;

    return v4l2;
}

__PUB_API__ int v4l2_loopback_write_frame(v4l2_t *loopback,
    const v4l2_image_t *image)
{
    errno_clear();

    if ((NULL == loopback) || (NULL == image)) {
        errno_set(V4L2_NULL_ARG);
        return -1;
    }

    return loopback_write_frame(loopback, image);
}


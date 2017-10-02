
/*
 * Description:
 *
 * Author: Rodrigo Freitas
 * Created at: Fri Feb 10 09:14:12 2017
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

#include "libv4l2.h"

static int v4l2_get_control(struct v4l2_s *v4l2, enum v4l2_setting setting)
{
    struct v4l2_control control;

    MEMSET(control);
    control.id = v4l2_setting_to_videodev(setting);

    if (_ioctl(v4l2->fd, VIDIOC_G_CTRL, &control) == -1) {
        errno_set(V4L2_ERROR_GETTING_VALUE);
        return -1;
    }

    return (control.value * DEFAULT_MAX_CTRL_RANGE) / v4l2->max_ctrl_range;
}

static int v4l2_set_control(struct v4l2_s *v4l2, enum v4l2_setting setting,
    int value)
{
    struct v4l2_control control;

    control.id = v4l2_setting_to_videodev(setting);
    control.value = (v4l2->max_ctrl_range * value) / DEFAULT_MAX_CTRL_RANGE;

    if (_ioctl(v4l2->fd, VIDIOC_S_CTRL, &control) == -1) {
        errno_set(V4L2_ERROR_SETTING_VALUE);
        return -1;
    }

    return 0;
}

static int get_default_video_input(int fd)
{
    int input = -1;

    if (_ioctl(fd, VIDIOC_G_INPUT, &input) == -1) {
        errno_set(V4L2_NO_INPUT);
        return -1;
    }

    return input;
}

static bool video_input_is_valid(int fd, enum v4l2_channel channel)
{
    struct v4l2_input input;

    MEMSET(input);
    input.index = channel;

    if (_ioctl(fd, VIDIOC_ENUMINPUT, &input) == -1)
        return false;

    if (input.type == V4L2_INPUT_TYPE_CAMERA)
        return true;

    return false;
}

static int v4l2_set_input(struct v4l2_s *v4l2, enum v4l2_model model,
    enum v4l2_channel channel)
{
    int input_index = -1;
    v4l2_std_id std_id;

    if (video_input_is_valid(v4l2->fd, channel))
        input_index = channel;
    else
        input_index = get_default_video_input(v4l2->fd);

    if (_ioctl(v4l2->fd, VIDIOC_S_INPUT, &input_index) == -1) {
        errno_set(V4L2_SET_INPUT_ERROR);
        return -1;
    }

    if ((model != V4L2_MODEL_USB_WEBCAM) &&
        (model != V4L2_MODEL_RPI_CAMERA))
    {
        std_id = V4L2_NTSC_STANDARD;

        if (_ioctl(v4l2->fd, VIDIOC_S_STD, &std_id) == -1) {
            errno_set(V4L2_SET_STD_ERROR);
            return -1;
        }
    }

    v4l2->channel = channel;
    v4l2->model = model;

    return 0;
}

static int v4l2_init_device(struct v4l2_s *v4l2, int width, int height,
    enum v4l2_image_format format)
{
    struct v4l2_cropcap cropcap;
    struct v4l2_crop crop;
    struct v4l2_format fmt;
    struct v4l2_queryctrl ctrl;
    int max_ctrl_range = DEFAULT_MAX_CTRL_RANGE;

    MEMSET(cropcap);
    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if (_ioctl(v4l2->fd, VIDIOC_CROPCAP, &cropcap) == 0) {
        crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        crop.c = cropcap.defrect;

        /* Ignore if an error occurs */
        _ioctl(v4l2->fd, VIDIOC_S_CROP, &crop);
    }

    MEMSET(fmt);
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if (_ioctl(v4l2->fd, VIDIOC_G_FMT, &fmt) == -1) {
        errno_set(V4L2_ERROR_GET_FMT);
        return -1;
    }

    fmt.fmt.pix.width = width;
    fmt.fmt.pix.height = height;
    fmt.fmt.pix.pixelformat = v4l2_format_to_videodev(format);
    fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

    if (_ioctl(v4l2->fd, VIDIOC_S_FMT, &fmt) == -1) {
        errno_set(V4L2_ERROR_SET_FMT);
        return -1;
    }

    if (mmap_init(v4l2) < 0)
        return -1;

    /* Gets a setting so we can discover our max_ctrl_range */
    if (v4l2->model != V4L2_MODEL_USB_WEBCAM) {
        MEMSET(ctrl);
        ctrl.id = V4L2_CID_BRIGHTNESS;

        if (_ioctl(v4l2->fd, VIDIOC_QUERYCTRL, &ctrl) == -1) {
            errno_set(V4L2_QUERYCTRL_ERROR);
            return -1;
        }

        max_ctrl_range = ctrl.maximum;
    }

    /* Initialize our object internals */
    v4l2->max_ctrl_range = max_ctrl_range;
    v4l2->current_image.width = fmt.fmt.pix.width;
    v4l2->current_image.height = fmt.fmt.pix.height;
    v4l2->current_image.format = format;
    v4l2->current_image.data_size = fmt.fmt.pix.sizeimage;

    v4l2->device_initialized = true;

    return 0;
}

/*
 *
 * API
 *
 */

__PUB_API__ v4l2_t *v4l2_ref(v4l2_t *v4l2)
{
    struct v4l2_s *v = (struct v4l2_s *)v4l2;

    errno_clear();

    if (NULL == v4l2) {
        errno_set(V4L2_NULL_ARG);
        return NULL;
    }

    cl_ref_inc(&v->ref);

    return v4l2;
}

__PUB_API__ int v4l2_unref(v4l2_t *v4l2)
{
    struct v4l2_s *v = (struct v4l2_s *)v4l2;

    errno_clear();

    if (NULL == v4l2) {
        errno_set(V4L2_NULL_ARG);
        return -1;
    }

    cl_ref_dec(&v->ref);

    return 0;
}

__PUB_API__ v4l2_t *v4l2_open(const char *device, int width, int height,
    enum v4l2_image_format format, enum v4l2_model model,
    enum v4l2_channel channel)
{
    struct v4l2_s *v4l2 = NULL;
    int error;

    errno_clear();

    if (NULL == device) {
        errno_set(V4L2_NULL_ARG);
        return NULL;
    }

    if (is_supported_format(format) == false) {
        errno_set(V4L2_UNSUPPORTED_FORMAT);
        return NULL;
    }

    if (is_supported_model(model) == false) {
        errno_set(V4L2_UNSUPPORTED_MODEL);
        return NULL;
    }

    if (is_supported_channel(channel) == false) {
        errno_set(V4L2_UNSUPPORTED_CHANNEL);
        return NULL;
    }

    v4l2 = new_v4l2_s();

    if (NULL == v4l2)
        return NULL;

    if (v4l2_open_device(v4l2, device, false) < 0)
        goto error_block;

    if (v4l2_set_input(v4l2, model, channel) < 0)
        goto error_block;

    if (v4l2_init_device(v4l2, width, height, format) < 0)
        goto error_block;

    if (grab_start(v4l2) < 0)
        goto error_block;

    return v4l2;

error_block:
    error = v4l2_get_last_error();
    v4l2_unref(v4l2);
    errno_set(error);

    return NULL;
}

__PUB_API__ int v4l2_close(v4l2_t *v4l2)
{
    return v4l2_unref(v4l2);
}

__PUB_API__ v4l2_image_t *v4l2_grab_image(v4l2_t *v4l2, bool dup)
{
    errno_clear();

    if (NULL == v4l2) {
        errno_set(V4L2_NULL_ARG);
        return NULL;
    }

    return grab_image(v4l2, dup);
}

__PUB_API__ int v4l2_set_setting(const v4l2_t *v4l2, enum v4l2_setting setting,
    int value)
{
    struct v4l2_s *v = v4l2_ref((v4l2_t *)v4l2);
    int ret = -1, error;

    errno_clear();

    if (NULL == v4l2) {
        errno_set(V4L2_NULL_ARG);
        return -1;
    }

    if (is_supported_setting(setting) == false) {
        errno_set(V4L2_UNSUPPORTED_SETTING);
        goto end_block;
    }

    if (is_setting_value_valid(value) == false) {
        errno_set(V4L2_INVALID_VALUE);
        goto end_block;
    }

    ret = v4l2_set_control(v, setting, value);

end_block:
    error = v4l2_get_last_error();
    v4l2_unref(v);
    errno_set(error);

    return ret;
}

__PUB_API__ int v4l2_get_setting(const v4l2_t *v4l2, enum v4l2_setting setting)
{
    struct v4l2_s *v = v4l2_ref((v4l2_t *)v4l2);
    int value = -1, error;

    errno_clear();

    if (NULL == v4l2) {
        errno_set(V4L2_NULL_ARG);
        return -1;
    }

    if (is_supported_setting(setting) == false) {
        errno_set(V4L2_UNSUPPORTED_SETTING);
        goto end_block;
    }

    value = v4l2_get_control(v, setting);

end_block:
    error = v4l2_get_last_error();
    v4l2_unref(v);
    errno_set(error);

    return value;
}



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

#ifndef _LIBV4L2_H
#define _LIBV4L2_H          1

#ifndef _STDBOOL_H
# include <stdbool.h>
#endif

/** Settings */
enum v4l2_setting {
    V4L2_SETTING_UNKNOWN,
    V4L2_SETTING_BRIGHTNESS,
    V4L2_SETTING_CONTRAST,
    V4L2_SETTING_SATURATION,
    V4L2_SETTING_HUE
};

/** Image formats */
enum v4l2_image_format {
    V4L2_IMAGE_FMT_UNKNOWN,
    V4L2_IMAGE_FMT_GRAY,
    V4L2_IMAGE_FMT_BGR24,
    V4L2_IMAGE_FMT_YUV420,
    V4L2_IMAGE_FMT_YUYV
};

/** Capture card models */
enum v4l2_model {
    V4L2_MODEL_UNKNOWN,
    V4L2_MODEL_BT878_CARD,
    V4L2_MODEL_USB_WEBCAM,
    V4L2_MODEL_RPI_CAMERA
};

/** Capture card channel */
enum v4l2_channel {
    V4L2_CHANNEL_UNKNOWN = -1,
    V4L2_CHANNEL_TUNER,
    V4L2_CHANNEL_COMPOSITE,
    V4L2_CHANNEL_SVIDEO
};

/** Object to handle a v4l2 devide */
typedef void                v4l2_t;

/** Captured image object */
typedef void                v4l2_image_t;

#ifdef LIBV4L2_COMPILE
# define MAJOR_VERSION      0
# define MINOR_VERSION      1
# define RELEASE            6

# include "v4l2_lib/v_internal.h"
#endif

#include "v4l2_lib/v_error.h"
#include "v4l2_lib/v_image.h"
#include "v4l2_lib/v_info.h"
#include "v4l2_lib/v_loopback.h"
#include "v4l2_lib/v_v4l2.h"

#endif


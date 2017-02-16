
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

#ifndef _LIBV4L2_V_ERROR_H
#define _LIBV4L2_V_ERROR_H          1

#ifndef LIBV4L2_COMPILE
# ifndef _LIBV4L2_H
#  error "Never use <v_error.h> directly; include <libv4l2.h> instead."
# endif
#endif

enum v4l2_error_code {
    V4L2_ERROR_NO_ERROR,

    V4L2_ERROR_MALLOC,
    V4L2_NULL_ARG,
    V4L2_ERROR_SETTING_VALUE,
    V4L2_ERROR_GETTING_VALUE,
    V4L2_UNSUPPORTED_SETTING,
    V4L2_UNSUPPORTED_MMAP,
    V4L2_INSUFFICIENT_BUFFERS,
    V4L2_QUERYBUF_ERROR,
    V4L2_MMAP_FAILED,
    V4L2_MUNMAP_FAILED,
    V4L2_ERROR_EXCHANGING_BUFFER,
    V4L2_STREAM_ON_START_ERROR,
    V4L2_QUERYCAP_ERROR,
    V4L2_NO_CAP_VIDEO_CAPTURE,
    V4L2_NO_CAP_STREAMING,
    V4L2_OPEN_FAILED,
    V4L2_ERROR_SET_FMT,
    V4L2_ERROR_GET_FMT,
    V4L2_QUERYCTRL_ERROR,
    V4L2_NO_INPUT,
    V4L2_SET_INPUT_ERROR,
    V4L2_SET_STD_ERROR,
    V4L2_UNSUPPORTED_FORMAT,
    V4L2_UNSUPPORTED_MODEL,
    V4L2_UNSUPPORTED_CHANNEL,

    V4L2_ERROR_MAX_ERROR_CODE
};

enum v4l2_error_code v4l2_get_last_error(void);
const char *v4l2_strerror(enum v4l2_error_code code);

#endif


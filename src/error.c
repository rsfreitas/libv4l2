
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

#include "libv4l2.h"

static const char *__description[] = {
    tr_noop("Ok"),
    tr_noop("Error allocating memory internally"),
    tr_noop("Invalid argument"),
    tr_noop("Error setting value into the card"),
    tr_noop("Error getting value from the card"),
    tr_noop("Unsupported card setting"),
    tr_noop("Unsupported memory mapping"),
    tr_noop("Insufficiente number of internal buffers"),
    tr_noop("Unable to query buffer status"),
    tr_noop("Memory mapping failed"),
    tr_noop("Memory unmapping failed"),
    tr_noop("Unable to exchange a buffer with the driver"),
    tr_noop("Error starting I/O streaming"),
    tr_noop("Unable to query device capabilities"),
    tr_noop("The device does not support single planar API"),
    tr_noop("The device does not support I/O streaming"),
    tr_noop("Failed to open device"),
    tr_noop("Error setting the data format"),
    tr_noop("Error getting the data format"),
    tr_noop("Unable to query controls"),
    tr_noop("Unable to query current video input"),
    tr_noop("Unable to set the video input"),
    tr_noop("Error selecting the video standard for current input"),
    tr_noop("Unsupported image format"),
    tr_noop("Unsupported card model"),
    tr_noop("Unsupported input channel")
};

static const char *__unknown_error = tr_noop("Unknown error");
#define __errno        (*cerrno_storage())

void errno_clear(void)
{
    __errno = V4L2_ERROR_NO_ERROR;
}

void errno_set(enum v4l2_error_code code)
{
    __errno = code;
}

enum v4l2_error_code v4l2_get_last_error(void)
{
    return __errno;
}

const char *v4l2_strerror(enum v4l2_error_code code)
{
    if (code >= V4L2_ERROR_MAX_ERROR_CODE)
        return __unknown_error;

    return __description[code];
}


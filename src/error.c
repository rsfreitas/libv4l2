
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
    cl_tr_noop("Ok"),
    cl_tr_noop("Error allocating memory internally"),
    cl_tr_noop("Invalid argument"),
    cl_tr_noop("Error setting value into the card"),
    cl_tr_noop("Error getting value from the card"),
    cl_tr_noop("Unsupported card setting"),
    cl_tr_noop("Unsupported memory mapping"),
    cl_tr_noop("Insufficiente number of internal buffers"),
    cl_tr_noop("Unable to query buffer status"),
    cl_tr_noop("Memory mapping failed"),
    cl_tr_noop("Memory unmapping failed"),
    cl_tr_noop("Unable to exchange a buffer with the driver"),
    cl_tr_noop("Error starting I/O streaming"),
    cl_tr_noop("Unable to query device capabilities"),
    cl_tr_noop("The device does not support single planar API"),
    cl_tr_noop("The device does not support I/O streaming"),
    cl_tr_noop("Failed to open device"),
    cl_tr_noop("Error setting the data format"),
    cl_tr_noop("Error getting the data format"),
    cl_tr_noop("Unable to query controls"),
    cl_tr_noop("Unable to query current video input"),
    cl_tr_noop("Unable to set the video input"),
    cl_tr_noop("Error selecting the video standard for current input"),
    cl_tr_noop("Unsupported image format"),
    cl_tr_noop("Unsupported card model"),
    cl_tr_noop("Unsupported input channel"),
    cl_tr_noop("Error creating image grabbing thread"),
    cl_tr_noop("Error while starting image grabbing thread"),
    cl_tr_noop("Grabbing thread inactive"),
    cl_tr_noop("Error setting streaming parameters")
};

static const char *__unknown_error = cl_tr_noop("Unknown error");
#define __errno        (*cl_errno_storage())

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


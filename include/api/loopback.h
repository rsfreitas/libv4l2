
/*
 * Description:
 *
 * Author: Rodrigo Freitas
 * Created at: Sun Oct  1 10:58:04 2017
 * Project: libv4l2
 *
 * Copyright (C) 2017 Rodrigo Freitas All rights reserved
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

#ifndef _LIBV4L2_API_LOOPBACK_H
#define _LIBV4L2_API_LOOPBACK_H

#ifndef LIBV4L2_COMPILE
# ifndef _LIBV4L2_H
#  error "Never use <loopback.h> directly; include <libv4l2.h> instead."
# endif
#endif

/**
 * @name v4l2_loopback_open
 * @brief Opens a loopback device for writing.
 *
 * This function will open a loopback device, created by the v4l2loopback kernel
 * module, for writing frames into it.
 *
 * @param [in] device: The define name.
 * @param [in] source: The original video4linux2 opened device.
 * @param [in] auto_replication: A boolean flag to initialize the internal frame
 *                               replication to the opened loopback device.
 *
 * @return On success returns a v4l2_t object to be used as a loopback device or
 *         NULL otherwise.
 */
v4l2_t *v4l2_loopback_open(const char *device, const v4l2_t *source,
                           bool auto_replication);

/**
 * @name v4l2_loopback_write_frame
 * @brief Writes a frame into the loopback device.
 *
 * @param [in,out] loopback: The loopback device.
 * @param [in] image: The captured image frame.
 *
 * @return On success returns 0 or -1 otherwise.
 */
int v4l2_loopback_write_frame(v4l2_t *loopback, const v4l2_image_t *image);

#endif


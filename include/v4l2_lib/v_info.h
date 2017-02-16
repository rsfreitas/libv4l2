
/*
 * Description:
 *
 * Author: Rodrigo Freitas
 * Created at: Thu Feb 16 16:15:34 2017
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

#ifndef _LIBV4L2_V_INFO_H
#define _LIBV4L2_V_INFO_H          1

#ifndef LIBV4L2_COMPILE
# ifndef _LIBV4L2_H
#  error "Never use <v_info.h> directly; include <libv4l2.h> instead."
# endif
#endif

const char *v4l2_device_name(const v4l2_t *v4l2);
const char *v4l2_card_name(const v4l2_t *v4l2);
const char *v4l2_driver_name(const v4l2_t *v4l2);
const char *v4l2_bus_info(const v4l2_t *v4l2);

#endif


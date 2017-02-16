
/*
 * Description:
 *
 * Author: Rodrigo Freitas
 * Created at: Thu Feb 16 13:46:33 2017
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

#ifndef _LIBV4L2_V_V4L2_H
#define _LIBV4L2_V_V4L2_H          1

#ifndef LIBV4L2_COMPILE
# ifndef _LIBV4L2_H
#  error "Never use <v_v4l2.h> directly; include <libv4l2.h> instead."
# endif
#endif

v4l2_t *v4l2_ref(v4l2_t *v4l2);
int v4l2_unref(v4l2_t *v4l2);
v4l2_t *v4l2_open(const char *device, int width, int height,
                  enum v4l2_image_format format, enum v4l2_model model,
                  enum v4l2_channel channel);

int v4l2_close(v4l2_t *v4l2);
v4l2_image_t *v4l2_grab_image(v4l2_t *v4l2, bool dup);
int v4l2_set_setting(v4l2_t *v4l2, enum v4l2_setting setting, int value);
int v4l2_get_setting(v4l2_t *v4l2, enum v4l2_setting setting);

#endif


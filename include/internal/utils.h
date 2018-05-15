
/*
 * Description:
 *
 * Author: Rodrigo Freitas
 * Created at: Fri Feb 10 09:06:20 2017
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

#ifndef _LIBV4L2_INTERNAL_UTILS_H
#define _LIBV4L2_INTERNAL_UTILS_H

int _ioctl(int fd, int request, void *argp);
int v4l2_format_to_videodev(enum v4l2_image_format format);
int v4l2_setting_to_videodev(enum v4l2_setting setting);
bool is_supported_setting(enum v4l2_setting setting);
bool is_supported_format(enum v4l2_image_format format);
bool is_supported_model(enum v4l2_model model);
bool is_supported_channel(enum v4l2_channel channel);
int close_video_device(int fd);
int v4l2_open_device(struct v4l2_s *v4l2, const char *device, bool loopback);
struct v4l2_s *new_v4l2_s(void);
void lock_init(struct v4l2_s *v4l2);
void lock_uninit(struct v4l2_s *v4l2);
void read_lock(struct v4l2_s *v4l2);
void read_unlock(struct v4l2_s *v4l2);
void write_lock(struct v4l2_s *v4l2);
void write_unlock(struct v4l2_s *v4l2);
bool is_setting_value_valid(int value);

#endif



/*
 * Description:
 *
 * Author: Rodrigo Freitas
 * Created at: Wed Feb 15 21:38:22 2017
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

#ifndef _LIBV4L2_INTERNAL_IMAGE_H
#define _LIBV4L2_INTERNAL_IMAGE_H

struct v4l2_image_s *new_v4l2_image_s(enum v4l2_image_format format,
                                      int width, int height);

#endif


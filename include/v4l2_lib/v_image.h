
/*
 * Description:
 *
 * Author: Rodrigo Freitas
 * Created at: Wed Feb 15 21:38:22 2017
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

#ifndef _LIBV4L2_V_IMAGE_H
#define _LIBV4L2_V_IMAGE_H          1

#ifndef LIBV4L2_COMPILE
# ifndef _LIBV4L2_H
#  error "Never use <v_image.h> directly; include <libv4l2.h> instead."
# endif
#endif

#ifdef LIBV4L2_COMPILE
struct v4l2_image_s *new_v4l2_image_s(enum v4l2_image_format format,
                                      int width, int height);
#endif

/**
 * @name v4l2_image_ref
 * @brief Increases the reference count for a v4l2_image_t object.
 *
 * @param [in] image: The v4l2_image_t object.
 *
 * @return On success returns the object itself with its reference count
 *         increased or NULL otherwise.
 */
v4l2_image_t *v4l2_image_ref(v4l2_image_t *image);

/**
 * @name v4l2_image_unref
 * @brief Decreases the reference count for a v4l2_image_t object.
 *
 * When its reference count drops to 0, the item is finalized and its memory
 * is released.
 *
 * @param [in] image: The v4l2_image_t object.
 *
 * @return On success returns 0 or -1 otherwise.
 */
int v4l2_image_unref(v4l2_image_t *image);

/**
 * @name v4l2_image_size
 * @brief Gets the image byte size.
 *
 * @param [in] image: The v4l2_image_t object.
 *
 * @return On success returns the image size in bytes or 0 otherwise.
 */
unsigned int v4l2_image_size(const v4l2_image_t *image);

/**
 * @name v4l2_image_width
 * @brief Gets the image width.
 *
 * @param [in] image: The v4l2_image_t object.
 *
 * @return On success returns the image width or -1 otherwise.
 */
int v4l2_image_width(const v4l2_image_t *image);

/**
 * @name v4l2_image_height
 * @brief Gets the image height.
 *
 * @param [in] image: The v4l2_image_t object.
 *
 * @return On success returns the image height or -1 otherwise.
 */
int v4l2_image_height(const v4l2_image_t *image);

/**
 * @name v4l2_image_format
 * @brief Gets the image color format.
 *
 * @param [in] image: The v4l2_image_t object.
 *
 * @return On success returns the image format or -1 otherwise.
 */
enum v4l2_image_format v4l2_image_format(const v4l2_image_t *image);

/**
 * @name v4l2_image_data
 * @brief Gets the image content.
 *
 * @param [in] image: The v4l2_image_t object.
 *
 * @return On success returns a pointer to the image content or NULL otherwise.
 */
const unsigned char *v4l2_image_data(const v4l2_image_t *image);

#endif


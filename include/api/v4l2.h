
/*
 * Description:
 *
 * Author: Rodrigo Freitas
 * Created at: Thu Feb 16 13:46:33 2017
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

#ifndef _LIBV4L2_API_V4L2_H
#define _LIBV4L2_API_V4L2_H

#ifndef LIBV4L2_COMPILE
# ifndef _LIBV4L2_H
#  error "Never use <v4l2.h> directly; include <libv4l2.h> instead."
# endif
#endif

/**
 * @name v4l2_ref
 * @brief Increases the reference count for a v4l2_t object.
 *
 * @param [in,out] v4l2: The v4l2_t object.
 *
 * @return On success returns the object itself with its reference count
 *         increased or NULL otherwise.
 */
v4l2_t *v4l2_ref(v4l2_t *v4l2);

/**
 * @name v4l2_unref
 * @brief Decreases the reference count for a v4l2_t object.
 *
 * When its reference count drops to 0, the item is finalized and its memory
 * is released.
 *
 * @param [in,out] v4l2: The v4l2_t object.
 *
 * @return On success returns 0 or -1 otherwise.
 */
int v4l2_unref(v4l2_t *v4l2);

/**
 * @name v4l2_open
 * @brief Opens a video device for streaming capture images.
 *
 * This function will put a thread to do a continuous image grabbing so one
 * may request an image later.
 *
 * @param [in] device: The device name (i.e. /dev/video0).
 * @param [in] width: The requested width of the grabbed images.
 * @param [in] height: The requested height of the grabbed images.
 * @param [in] format: The image format.
 * @param [in] model: The card model.
 * @param [in] channel: The card channel to capture the images.
 *
 * @return On success returns a v4l2_t object or NULL otherwise.
 */
v4l2_t *v4l2_open(const char *device, int width, int height,
                  enum v4l2_image_format format, enum v4l2_model model,
                  enum v4l2_channel channel);

/**
 * @name v4l2_close
 * @brief Closes a video device.
 *
 * @param [in] v4l2: The v4l2_t object.
 *
 * @return On success returns 0 or -1 otherwise.
 */
int v4l2_close(v4l2_t *v4l2);

/**
 * @name v4l2_grab_image
 * @brief Grabs an image from a video device.
 *
 * @param [in,out] v4l2: The v4l2_t object.
 * @param [in] dup: A boolean flag to set if the returned image will be a copy
 *                  or not.
 *
 * @return On success returns a v4l2_image_t object with an image or NULL
 *         otherwise.
 */
v4l2_image_t *v4l2_grab_image(v4l2_t *v4l2, bool dup);

/**
 * @name v4l2_set_setting
 * @brief Sets a setting into the card.
 *
 * @value should be in the 0-255 range.
 *
 * @param [in] v4l2: The v4l2_t object.
 * @param [in] setting: The requested setting.
 * @param [in] value: The new value.
 *
 * @return On success returns 0 or -1 otherwise.
 */
int v4l2_set_setting(const v4l2_t *v4l2, enum v4l2_setting setting, int value);

/**
 * @name v4l2_get_setting
 * @brief Gets the current setting value from the card.
 *
 * The setting value returned should be in the 0-255 range.
 *
 * @param [in] v4l2: The v4l2_t object.
 * @param [in] setting: The requested setting.
 *
 * @return On success returns the current value or -1 otherwise.
 */
int v4l2_get_setting(const v4l2_t *v4l2, enum v4l2_setting setting);

#endif


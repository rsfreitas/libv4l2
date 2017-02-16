
/*
 * Description:
 *
 * Author: Rodrigo Freitas
 * Created at: Thu Feb 16 16:09:11 2017
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

__PUB_API__ const char *v4l2_device_name(const v4l2_t *v4l2)
{
    struct v4l2_s *v = v4l2_ref((v4l2_t *)v4l2);
    char *ptr = NULL;

    errno_clear();

    if (NULL == v4l2) {
        errno_set(V4L2_NULL_ARG);
        return NULL;
    }

    ptr = v->device;
    v4l2_unref(v);

    return ptr;
}

__PUB_API__ const char *v4l2_card_name(const v4l2_t *v4l2)
{
    struct v4l2_s *v = v4l2_ref((v4l2_t *)v4l2);
    char *ptr = NULL;

    errno_clear();

    if (NULL == v4l2) {
        errno_set(V4L2_NULL_ARG);
        return NULL;
    }

    ptr = v->card;
    v4l2_unref(v);

    return ptr;
}

__PUB_API__ const char *v4l2_driver_name(const v4l2_t *v4l2)
{
    struct v4l2_s *v = v4l2_ref((v4l2_t *)v4l2);
    char *ptr = NULL;

    errno_clear();

    if (NULL == v4l2) {
        errno_set(V4L2_NULL_ARG);
        return NULL;
    }

    ptr = v->driver;
    v4l2_unref(v);

    return ptr;
}

__PUB_API__ const char *v4l2_bus_info(const v4l2_t *v4l2)
{
    struct v4l2_s *v = v4l2_ref((v4l2_t *)v4l2);
    char *ptr = NULL;

    errno_clear();

    if (NULL == v4l2) {
        errno_set(V4L2_NULL_ARG);
        return NULL;
    }

    ptr = v->bus_info;
    v4l2_unref(v);

    return ptr;
}


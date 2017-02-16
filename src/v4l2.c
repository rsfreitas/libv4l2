
/*
 * Description:
 *
 * Author: Rodrigo Freitas
 * Created at: Fri Feb 10 09:14:12 2017
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

static const int __desired_video_buffers = 4;

__PUB_API__ v4l2_t *v4l2_ref(v4l2_t *v4l2)
{
    struct v4l2_s *v = (struct v4l2_s *)v4l2;

    errno_clear();

    if (NULL == v4l2) {
        errno_set(V4L2_NULL_ARG);
        return NULL;
    }

    cref_inc(&v->ref);

    return v4l2;
}

__PUB_API__ int v4l2_unref(v4l2_t *v4l2)
{
    struct v4l2_s *v = (struct v4l2_s *)v4l2;

    errno_clear();

    if (NULL == v4l2) {
        errno_set(V4L2_NULL_ARG);
        return -1;
    }

    cref_dec(&v->ref);

    return 0;
}

__PUB_API__ v4l2_t *v4l2_open(const char *device, int width, int height,
    enum v4l2_image_format format, enum v4l2_model model)
{
    struct v4l2_s *v4l2 = NULL;

    errno_clear();

    if (NULL == device) {
        errno_set(V4L2_NULL_ARG);
        return NULL;
    }

    return v4l2;
}

__PUB_API__ int v4l2_close(v4l2_t *v4l2)
{
    return v4l2_unref(v4l2);
}

__PUB_API__ void v4l2_grab_image(void)
{
}

__PUB_API__ void v4l2_set_setting(void)
{
}

__PUB_API__ void v4l2_get_setting(void)
{
}


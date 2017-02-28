
/*
 * Description:
 *
 * Author: Rodrigo Freitas
 * Created at: Wed Feb 15 21:21:24 2017
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

#include <stdlib.h>

#include "libv4l2.h"

static void destroy_v4l2_image_s(const struct cref_s *ref)
{
    struct v4l2_image_s *i = cl_container_of(ref, struct v4l2_image_s, ref);

    if (NULL == i)
        return;

    if ((i->data != NULL) && i->free_data)
        free(i->data);

    free(i);
}

struct v4l2_image_s *new_v4l2_image_s(enum v4l2_image_format format,
    int width, int height)
{
    struct v4l2_image_s *i = NULL;

    i = calloc(1, sizeof(struct v4l2_image_s));

    if (NULL == i) {
        errno_set(V4L2_ERROR_MALLOC);
        return NULL;
    }

    i->width = width;
    i->height = height;
    i->format = format;
    i->data = NULL;
    i->free_data = false;

    /* Initialize reference count */
    i->ref.count = 1;
    i->ref.free = destroy_v4l2_image_s;

    return i;
}

__PUB_API__ v4l2_image_t *v4l2_image_ref(v4l2_image_t *image)
{
    struct v4l2_image_s *i = (struct v4l2_image_s *)image;

    errno_clear();

    if (NULL == image) {
        errno_set(V4L2_NULL_ARG);
        return NULL;
    }

    cref_inc(&i->ref);

    return image;
}

__PUB_API__ int v4l2_image_unref(v4l2_image_t *image)
{
    struct v4l2_image_s *i = (struct v4l2_image_s *)image;

    errno_clear();

    if (NULL == image) {
        errno_set(V4L2_NULL_ARG);
        return -1;
    }

    cref_dec(&i->ref);

    return 0;
}

__PUB_API__ unsigned int v4l2_image_size(const v4l2_image_t *image)
{
    struct v4l2_image_s *i = v4l2_image_ref((v4l2_image_t *)image);
    unsigned int size;

    errno_clear();

    if (NULL == image) {
        errno_set(V4L2_NULL_ARG);
        return 0;
    }

    size = i->data_size;
    v4l2_image_unref(i);

    return size;
}

__PUB_API__ int v4l2_image_width(const v4l2_image_t *image)
{
    struct v4l2_image_s *i = v4l2_image_ref((v4l2_image_t *)image);
    int w;

    errno_clear();

    if (NULL == image) {
        errno_set(V4L2_NULL_ARG);
        return -1;
    }

    w = i->width;
    v4l2_image_unref(i);

    return w;
}

__PUB_API__ int v4l2_image_height(const v4l2_image_t *image)
{
    struct v4l2_image_s *i = v4l2_image_ref((v4l2_image_t *)image);
    int h;

    errno_clear();

    if (NULL == image) {
        errno_set(V4L2_NULL_ARG);
        return -1;
    }

    h = i->height;
    v4l2_image_unref(i);

    return h;
}

__PUB_API__ enum v4l2_image_format v4l2_image_format(const v4l2_image_t *image)
{
    struct v4l2_image_s *i = v4l2_image_ref((v4l2_image_t *)image);
    enum v4l2_image_format fmt = V4L2_IMAGE_FMT_UNKNOWN;

    errno_clear();

    if (NULL == image) {
        errno_set(V4L2_NULL_ARG);
        return -1;
    }

    fmt = i->format;
    v4l2_image_unref(i);

    return fmt;
}

__PUB_API__ const unsigned char *v4l2_image_data(const v4l2_image_t *image)
{
    struct v4l2_image_s *i = v4l2_image_ref((v4l2_image_t *)image);
    unsigned char *ptr = NULL;

    errno_clear();

    if (NULL == image) {
        errno_set(V4L2_NULL_ARG);
        return NULL;
    }

    ptr = i->data;
    v4l2_image_unref(i);

    return ptr;
}


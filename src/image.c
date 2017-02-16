
/*
 * Description:
 *
 * Author: Rodrigo Freitas
 * Created at: Wed Feb 15 21:21:24 2017
 * Project: libv4l2
 *
 * Copyright (c) 2017 All rights reserved
 */

#include <stdlib.h>

#include "libv4l2.h"

static void destroy_v4l2_image_s(const struct cref_s *ref)
{
    struct v4l2_image_s *i = cl_container_of(ref, struct v4l2_image_s, ref);

    if (NULL == i)
        return;

    free(i);
}

static struct v4l2_image_s *new_v4l2_image_s(enum v4l2_image_format format,
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


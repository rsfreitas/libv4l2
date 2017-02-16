
/*
 * Description:
 *
 * Author: Rodrigo Freitas
 * Created at: Wed Feb 15 21:21:01 2017
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
#include <sys/mman.h>

#include "libv4l2.h"

static const int __desired_video_buffers = 4;

static int mmap_start(struct v4l2_s *v4l2)
{
    struct v4l2_buffer buf;
    enum v4l2_buf_type type;
    int i;

    for (i = 0; i < v4l2->number_of_buffers; i++) {
        MEMSET(buf);
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;

        if (_ioctl(v4l2->fd, VIDIOC_QBUF, &buf) == -1) {
            errno_set(V4L2_ERROR_EXCHANGING_BUFFER);
            return -1;
        }
    }

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if (_ioctl(v4l2->fd, VIDIOC_STREAMON, &type) == -1) {
        errno_set(V4L2_STREAM_ON_START_ERROR);
        return -1;
    }

    return 0;
}

int mmap_init(struct v4l2_s *v4l2)
{
    struct v4l2_requestbuffers req;
    struct v4l2_buffer buf;
    unsigned int i;

    MEMSET(req);
    req.count = __desired_video_buffers;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (_ioctl(v4l2->fd, VIDIOC_REQBUFS, &req) == -1) {
        errno_set(V4L2_UNSUPPORTED_MMAP);
        return -1;
    }

    if (req.count < 2) {
        errno_set(V4L2_INSUFFICIENT_BUFFERS);
        return -1;
    }

    v4l2->number_of_buffers = req.count;
    v4l2->buffers = calloc(req.count, sizeof(struct v4l2_buffer_s));

    if (NULL == v4l2->buffers) {
        errno_set(V4L2_ERROR_MALLOC);
        return -1;
    }

    for (i = 0; i < req.count; i++) {
        MEMSET(buf);
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;

        if (_ioctl(v4l2->fd, VIDIOC_QUERYBUF, &buf) == -1) {
            errno_set(V4L2_QUERYBUF_ERROR);
            return -1;
        }

        v4l2->buffers[i].length = buf.length;
        v4l2->buffers[i].start = mmap(NULL, buf.length,
                                      PROT_READ | PROT_WRITE, MAP_SHARED,
                                      v4l2->fd, buf.m.offset);

        if (v4l2->buffers[i].start == MAP_FAILED) {
            errno_set(V4L2_MMAP_FAILED);
            return -1;
        }
    }

    if (mmap_start(v4l2) < 0)
        return -1;

    v4l2->mmap_initialized = true;

    return 0;
}

int mmap_uninit(struct v4l2_s *v4l2)
{
    int i;

    for (i = 0; i < v4l2->number_of_buffers; i++)
        if (munmap(v4l2->buffers[i].start, v4l2->buffers[i].length) == -1) {
            errno_set(V4L2_MUNMAP_FAILED);
            return -1;
        }

    free(v4l2->buffers);

    return 0;
}



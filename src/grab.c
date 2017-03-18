
/*
 * Description:
 *
 * Author: Rodrigo Freitas
 * Created at: Thu Feb 16 14:50:32 2017
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

#include <errno.h>

#include "libv4l2.h"

static int select_frame_data(struct v4l2_s *v4l2)
{
    fd_set fds;
    struct timeval tv;
    int ret;

    FD_ZERO(&fds);
    FD_SET(v4l2->fd, &fds);

    tv.tv_sec = 1;
    tv.tv_usec = 0;

    ret = select(v4l2->fd + 1, &fds, NULL, NULL, &tv);

    if (ret == -1)
        return -1;
    else if (ret == 0)
        return -2; /* timeout */

    return 0;
}

static void *grab_thread(cl_thread_t *arg)
{
    struct v4l2_s *v4l2 = cl_thread_get_user_data(arg);
    struct v4l2_buffer buf;
    int ret;

    cl_thread_set_state(arg, CL_THREAD_ST_CREATED);
    v4l2->captured_buffer_index = 0;
    cl_thread_set_state(arg, CL_THREAD_ST_INITIALIZED);

    while (v4l2->thread_active) {
        cl_msleep(1);
        ret = select_frame_data(v4l2);

        if (ret == -2)
            continue;
        else if (ret)
            goto end_thread;

        MEMSET(buf);
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;

        if (_ioctl(v4l2->fd, VIDIOC_DQBUF, &buf) < 0)
            if (errno != EIO) {
                /* TODO: Signal this to the user */
                goto end_thread;
            }

        pthread_mutex_lock(&v4l2->grab_mutex);

        v4l2->current_image.data_size = v4l2->buffers[buf.index].length;
        v4l2->captured_buffer_index = buf.index;

        /* We have a new frame */
        v4l2->have_new_frame = true;
        v4l2->framecount++;

        pthread_cond_signal(&v4l2->grab_cond);
        pthread_mutex_unlock(&v4l2->grab_mutex);

        if (_ioctl(v4l2->fd, VIDIOC_QBUF, &buf) == -1) {
            /* TODO: Signal this to the user */
            goto end_thread;
        }
    }

end_thread:
    return NULL;
}

int grab_start(struct v4l2_s *v4l2)
{
    v4l2->have_new_frame = false;
    v4l2->framecount = 0;
    v4l2->thread_active = true;

    pthread_mutex_init(&v4l2->grab_mutex, NULL);
    pthread_cond_init(&v4l2->grab_cond, NULL);

    v4l2->grab_thread = cl_thread_spawn(CL_THREAD_JOINABLE, grab_thread, v4l2);

    if (NULL == v4l2->grab_thread) {
        v4l2->thread_active = false;
        errno_set(V4L2_GRAB_THREAD_CREATION_ERROR);
        return -1;
    }

    if (cl_thread_wait_startup(v4l2->grab_thread) != 0) {
        v4l2->thread_active = false;
        errno_set(V4L2_GRAB_THREAD_START_ERROR);
        return -1;
    }

    return 0;
}

void grab_stop(struct v4l2_s *v4l2)
{
    if (NULL == v4l2->grab_thread)
        return;

    v4l2->thread_active = false;
    cl_thread_destroy(v4l2->grab_thread);
}

struct v4l2_image_s *grab_image(struct v4l2_s *v4l2, bool dup)
{
    struct v4l2_image_s *img = NULL;

    if (v4l2->thread_active == false) {
        errno_set(V4L2_INACTIVE_GRAB_THREAD);
        return NULL;
    }

    pthread_mutex_lock(&v4l2->grab_mutex);

    if (v4l2->have_new_frame == false)
        pthread_cond_wait(&v4l2->grab_cond, &v4l2->grab_mutex);

    /* Copy image */
    img = new_v4l2_image_s(v4l2->current_image.format,
                           v4l2->current_image.width,
                           v4l2->current_image.height);

    if (NULL == img)
        goto end_block;

    if (dup == true) {
        img->free_data = true;
        img->data = cl_memdup(v4l2->buffers[v4l2->captured_buffer_index].start,
                              v4l2->current_image.data_size);
    } else
        img->data = v4l2->buffers[v4l2->captured_buffer_index].start;

    img->data_size = v4l2->current_image.data_size;
    v4l2->have_new_frame = false;

end_block:
    pthread_mutex_unlock(&v4l2->grab_mutex);

    return img;
}


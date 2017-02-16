
/*
 * Description:
 *
 * Author: Rodrigo Freitas
 * Created at: Wed Feb 15 21:38:26 2017
 * Project: libv4l2
 *
 * Copyright (c) 2017 All rights reserved
 */

#ifndef _LIBV4L2_V_MMAP_H
#define _LIBV4L2_V_MMAP_H          1

#ifndef LIBV4L2_COMPILE
# ifndef _LIBV4L2_H
#  error "Never use <v_mmap.h> directly; include <libv4l2.h> instead."
# endif
#endif

int mmap_init(struct v4l2_s *v4l2);
int mmap_uninit(struct v4l2_s *v4l2);

#endif



/*
 * Description:
 *
 * Author: Rodrigo Freitas
 * Created at: Fri Feb 10 09:16:19 2017
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

#ifndef _V_INTERNAL_H
#define _V_INTERNAL_H          1

#ifndef _STDINT_H
# include <stdint.h>
#endif

#ifndef _STDBOOL_H
# include <stdbool.h>
#endif

#ifndef __LINUX_VIDEODEV2_H
# include <linux/videodev2.h>
#endif

#ifndef _PTHREAD_H
# include <pthread.h>
#endif

#ifndef _STRING_H
# include <string.h>
#endif

/*
 * An internal representation of a public function. It does not affect the code
 * or the function visibility. Its objective is only to let clear what is and
 * what is not been exported from library by looking at the code.
 *
 * Every exported function must have this at the beginning of its declaration.
 * Example:
 *
 * __PUB_API__ const char *function(int arg)
 * {
 *      // Body
 * }
 */
#define __PUB_API__

#define MEMSET(x)           memset(&(x), 0, sizeof(s))

struct v4l2_image_s {
    unsigned char   *data;
    unsigned int    data_size;
    struct cref_s   ref;
};

struct v4l2_s {
    enum v4l2_model model;
    char            *device;
    int             fd;
    char            card[32];
    char            bus_info[32];
    char            driver[16];
    int             max_ctrl_range;
    uint32_t        capabilities;
    struct cref_s   ref;
};

#include "v_utils.h"
#include "v_mmap.h"

/* error.c */
void errno_clear(void);
void errno_set(enum v4l2_error_code code);

#endif


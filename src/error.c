
/*
 * Description:
 *
 * Author: Rodrigo Freitas
 * Created at: Fri Feb 10 09:06:20 2017
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

#ifndef USE_LIBCOLLECTIONS
# define tr_noop(String)    String
#endif

static const char *__description[] = {
    tr_noop("Ok")
};

static const char *__unknown_error = tr_noop("Unknown error");

#ifdef USE_LIBCOLLECTIONS
# define __errno        (*cerrno_storage())
#else
static __thread int __errno;
#endif

void errno_clear(void)
{
    __errno = V4L2_ERROR_NO_ERROR;
}

void errno_set(enum v4l2_error_code code)
{
    __errno = code;
}

enum v4l2_error_code v4l2_get_last_error(void)
{
    return __errno;
}

const char *v4l2_strerror(enum v4l2_error_code code)
{
    if (code >= V4L2_ERROR_MAX_ERROR_CODE)
        return __unknown_error;

    return __description[code];
}


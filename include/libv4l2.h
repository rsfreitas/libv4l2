
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

#ifndef _LIBV4L2_H
#define _LIBV4L2_H          1

#ifdef USE_LIBCOLLECTIONS
# include <collections.h>
#endif

#include "v4l2_lib/v_error.h"

#ifdef LIBV4L2_COMPILE
# define MAJOR_VERSION      0
# define MINOR_VERSION      1
# define RELEASE            1

# include "v4l2_lib/v_internal.h"
#endif

#include "v4l2_lib/v_utils.h"

#endif


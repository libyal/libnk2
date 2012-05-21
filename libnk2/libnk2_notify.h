/*
 * Notification function
 *
 * Copyright (c) 2009-2012, Joachim Metz <jbmetz@users.sourceforge.net>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBNK2_NOTIFY_H )
#define _LIBNK2_NOTIFY_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#include "libnk2_extern.h"
#include "libnk2_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBNK2 )

LIBNK2_EXTERN \
void libnk2_notify_set_verbose(
      int verbose );

LIBNK2_EXTERN \
int libnk2_notify_set_stream(
     FILE *stream,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_notify_stream_open(
     const char *filename,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_notify_stream_close(
     libcerror_error_t **error );

#endif

#if defined( __cplusplus )
}
#endif

#endif


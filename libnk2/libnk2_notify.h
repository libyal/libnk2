/*
 * Notification function
 *
 * Copyright (c) 2006-2009, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
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
#include <types.h>

#include <liberror.h>

#include <stdio.h>

#include "libnk2_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern int libnk2_notify_verbose;

LIBNK2_EXTERN void libnk2_set_notify_values(
                    FILE *stream,
                    int verbose );

void libnk2_notify_printf(
      char *format,
      ... );

#define libnk2_notify_verbose_printf \
	if( libnk2_notify_verbose != 0 ) libnk2_notify_printf

void libnk2_notify_error_backtrace(
      liberror_error_t *error );

void libnk2_notify_dump_data(
      void *data,
      size_t size );

#define libnk2_notify_verbose_dump_data \
	if( libnk2_notify_verbose != 0 ) libnk2_notify_dump_data

#if defined( __cplusplus )
}
#endif

#endif


/*
 * Support functions
 *
 * Copyright (c) 2008-2009, Joachim Metz <forensics@hoffmannbv.nl>,
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

#if !defined( _LIBNK2_SUPPORT_H )
#define _LIBNK2_SUPPORT_H

#include <common.h>
#include <types.h>

#include <stdio.h>

#include "libnk2_error.h"
#include "libnk2_extern.h"
#include "libnk2_file.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBNK2_EXTERN const char *libnk2_get_version(
                           void );

LIBNK2_EXTERN int libnk2_signal_abort(
                   libnk2_file_t *file );

LIBNK2_EXTERN void libnk2_error_free(
                    libnk2_error_t **error );

LIBNK2_EXTERN void libnk2_error_fprint(
                    libnk2_error_t *error,
                    FILE *stream );

LIBNK2_EXTERN void libnk2_error_backtrace_fprint(
                    libnk2_error_t *error,
                    FILE *stream );

#if defined( __cplusplus )
}
#endif

#endif


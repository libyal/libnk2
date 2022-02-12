/*
 * Error functions
 *
 * Copyright (C) 2009-2022, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _LIBNK2_INTERNAL_ERROR_H )
#define _LIBNK2_INTERNAL_ERROR_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if !defined( HAVE_LOCAL_LIBNK2 )
#include <libnk2/error.h>
#endif

#include "libnk2_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBNK2 )

LIBNK2_EXTERN \
void libnk2_error_free(
      libnk2_error_t **error );

LIBNK2_EXTERN \
int libnk2_error_fprint(
     libnk2_error_t *error,
     FILE *stream );

LIBNK2_EXTERN \
int libnk2_error_sprint(
     libnk2_error_t *error,
     char *string,
     size_t size );

LIBNK2_EXTERN \
int libnk2_error_backtrace_fprint(
     libnk2_error_t *error,
     FILE *stream );

LIBNK2_EXTERN \
int libnk2_error_backtrace_sprint(
     libnk2_error_t *error,
     char *string,
     size_t size );

#endif /* !defined( HAVE_LOCAL_LIBNK2 ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBNK2_INTERNAL_ERROR_H ) */


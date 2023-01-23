/*
 * Common output functions for the nk2tools
 *
 * Copyright (C) 2009-2023, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _NK2TOOLS_OUTPUT_H )
#define _NK2TOOLS_OUTPUT_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#include "nk2tools_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

int nk2tools_output_initialize(
     int stdio_mode,
     libcerror_error_t **error );

void nk2tools_output_copyright_fprint(
      FILE *stream );

void nk2tools_output_version_fprint(
      FILE *stream,
      const char *program );

void nk2tools_output_version_detailed_fprint(
      FILE *stream,
      const char *program );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _NK2TOOLS_OUTPUT_H ) */


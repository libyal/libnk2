/*
 * Debug functions
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

#if !defined( _LIBNK2_DEBUG_H )
#define _LIBNK2_DEBUG_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libnk2_libbfio.h"
#include "libnk2_string.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( HAVE_VERBOSE_OUTPUT )

const libnk2_character_t *libnk2_debug_get_value_type_string(
                           uint16_t value_type );

const libnk2_character_t *libnk2_debug_get_entry_type_string(
                           uint16_t entry_type,
                           uint16_t value_type );

#endif

#if defined( HAVE_DEBUG_OUTPUT )

int libnk2_debug_print_read_offsets(
     libbfio_handle_t *file_io_handle,
     liberror_error_t **error );

#endif

#if defined( __cplusplus )
}
#endif

#endif


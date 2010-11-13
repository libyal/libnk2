/*
 * Input/Output (IO) handle functions
 *
 * Copyright (c) 2009-2010, Joachim Metz <jbmetz@users.sourceforge.net>
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

#if !defined( _LIBNK2_IO_HANDLE_H )
#define _LIBNK2_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libnk2_array_type.h"
#include "libnk2_libbfio.h"
#include "libnk2_libfvalue.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint8_t nk2_file_signature[ 4 ];

typedef struct libnk2_io_handle libnk2_io_handle_t;

struct libnk2_io_handle
{
	/* The codepage of the extended ASCII strings
	 */
	int ascii_codepage;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libnk2_io_handle_initialize(
     libnk2_io_handle_t **io_handle,
     liberror_error_t **error );

int libnk2_io_handle_free(
     libnk2_io_handle_t **io_handle,
     liberror_error_t **error );

int libnk2_io_handle_read_file_header(
     libnk2_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t *number_of_items,
     liberror_error_t **error );

int libnk2_io_handle_read_items(
     libnk2_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t number_of_items,
     libnk2_array_t *items_array,
     liberror_error_t **error );

int libnk2_io_handle_read_item_values(
     libnk2_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t item_index,
     uint32_t number_of_item_values,
     libfvalue_table_t *values_table,
     liberror_error_t **error );

int libnk2_io_handle_read_file_footer(
     libnk2_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint64_t *modification_time,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif


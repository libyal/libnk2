/*
 * Input/Output (IO) handle functions
 *
 * Copyright (C) 2009-2016, Joachim Metz <joachim.metz@gmail.com>
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

#include "libnk2_libbfio.h"
#include "libnk2_libcdata.h"
#include "libnk2_libcerror.h"

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
     libcerror_error_t **error );

int libnk2_io_handle_free(
     libnk2_io_handle_t **io_handle,
     libcerror_error_t **error );

int libnk2_io_handle_clear(
     libnk2_io_handle_t *io_handle,
     libcerror_error_t **error );

int libnk2_io_handle_read_file_header(
     libnk2_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t *number_of_items,
     libcerror_error_t **error );

int libnk2_io_handle_read_items(
     libnk2_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t number_of_items,
     libcdata_array_t *items_array,
     libcerror_error_t **error );

int libnk2_io_handle_read_record_entries(
     libnk2_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t item_index,
     uint32_t number_of_record_entries,
     libcdata_array_t *entries_array,
     libcerror_error_t **error );

int libnk2_io_handle_read_file_footer(
     libnk2_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint64_t *modification_time,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBNK2_IO_HANDLE_H ) */


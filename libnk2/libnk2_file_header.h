/*
 * File header functions
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

#if !defined( _LIBNK2_FILE_HEADER_H )
#define _LIBNK2_FILE_HEADER_H

#include <common.h>
#include <types.h>

#include "libnk2_libbfio.h"
#include "libnk2_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libnk2_file_header libnk2_file_header_t;

struct libnk2_file_header
{
	/* The number of items
	 */
	uint32_t number_of_items;
};

int libnk2_file_header_initialize(
     libnk2_file_header_t **file_header,
     libcerror_error_t **error );

int libnk2_file_header_free(
     libnk2_file_header_t **file_header,
     libcerror_error_t **error );

int libnk2_file_header_read_data(
     libnk2_file_header_t *file_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libnk2_file_header_read_file_io_handle(
     libnk2_file_header_t *file_header,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBNK2_FILE_HEADER_H ) */


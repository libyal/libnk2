/*
 * Record entry functions
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

#if !defined( _LIBNK2_RECORD_ENTRY_H )
#define _LIBNK2_RECORD_ENTRY_H

#include <common.h>
#include <types.h>

#include "libnk2_extern.h"
#include "libnk2_libbfio.h"
#include "libnk2_libcerror.h"
#include "libnk2_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libnk2_internal_record_entry libnk2_internal_record_entry_t;

struct libnk2_internal_record_entry
{
	/* The entry type
	 */
	uint32_t entry_type;

	/* The value type
	 */
	uint32_t value_type;

	/* The value data array
	 */
	uint8_t value_data_array[ 8 ];

	/* The value data
	 */
	uint8_t *value_data;

	/* The value data size
	 */
	size_t value_data_size;

	/* The codepage of the extended ASCII strings
	 */
	int ascii_codepage;
};

int libnk2_record_entry_initialize(
     libnk2_record_entry_t **record_entry,
     int ascii_codepage,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_record_entry_free(
     libnk2_record_entry_t **record_entry,
     libcerror_error_t **error );

int libnk2_internal_record_entry_free(
     libnk2_internal_record_entry_t **internal_record_entry,
     libcerror_error_t **error );

int libnk2_record_entry_read_data(
     libnk2_record_entry_t *record_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libnk2_record_entry_read_file_io_handle(
     libnk2_record_entry_t *record_entry,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_record_entry_get_entry_type(
     libnk2_record_entry_t *record_entry,
     uint32_t *entry_type,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_record_entry_get_value_type(
     libnk2_record_entry_t *record_entry,
     uint32_t *value_type,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_record_entry_get_data_size(
     libnk2_record_entry_t *record_entry,
     size_t *data_size,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_record_entry_get_data(
     libnk2_record_entry_t *record_entry,
     uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_boolean(
     libnk2_record_entry_t *record_entry,
     uint8_t *value_boolean,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_16bit_integer(
     libnk2_record_entry_t *record_entry,
     uint16_t *value_16bit,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_32bit_integer(
     libnk2_record_entry_t *record_entry,
     uint32_t *value_32bit,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_64bit_integer(
     libnk2_record_entry_t *record_entry,
     uint64_t *value_64bit,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_filetime(
     libnk2_record_entry_t *record_entry,
     uint64_t *filetime,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_floatingtime(
     libnk2_record_entry_t *record_entry,
     uint64_t *floatingtime,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_size(
     libnk2_record_entry_t *record_entry,
     size64_t *value_size,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_floating_point(
     libnk2_record_entry_t *record_entry,
     double *value_floating_point,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_utf8_string_size(
     libnk2_record_entry_t *record_entry,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_utf8_string(
     libnk2_record_entry_t *record_entry,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_utf16_string_size(
     libnk2_record_entry_t *record_entry,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_utf16_string(
     libnk2_record_entry_t *record_entry,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_record_entry_get_data_as_guid(
     libnk2_record_entry_t *record_entry,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBNK2_RECORD_ENTRY_H ) */


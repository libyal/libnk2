/*
 * Item functions
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

#if !defined( _LIBNK2_ITEM_H )
#define _LIBNK2_ITEM_H

#include <common.h>
#include <types.h>

#include "libnk2_extern.h"
#include "libnk2_io_handle.h"
#include "libnk2_libbfio.h"
#include "libnk2_libcerror.h"
#include "libnk2_libfvalue.h"
#include "libnk2_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

#define LIBNK2_ITEM_FLAGS_DEFAULT			LIBNK2_ITEM_FLAG_NON_MANAGED_FILE_IO_HANDLE

enum LIBNK2_ITEM_FLAGS
{
	LIBNK2_ITEM_FLAG_NON_MANAGED_FILE_IO_HANDLE	= 0x00,
	LIBNK2_ITEM_FLAG_MANAGED_FILE_IO_HANDLE		= 0x01,
};

typedef struct libnk2_internal_item libnk2_internal_item_t;

struct libnk2_internal_item
{
	/* The IO handle
	 */
	libnk2_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* The values table
	 */
	libfvalue_table_t *values_table;

	/* The flags
	 */
	uint8_t flags;
};

int libnk2_item_initialize(
     libnk2_item_t **item,
     libnk2_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfvalue_table_t *values_table,
     uint8_t flags,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_free(
     libnk2_item_t **item,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_number_of_entries(
     libnk2_item_t *item,
     uint32_t *number_of_entries,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_entry_type(
     libnk2_item_t *item,
     int entry_index,
     uint32_t *entry_type,
     uint32_t *value_type,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_value_type(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint32_t *value_type,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_entry_value(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint32_t *value_type,
     uint8_t **value_data,
     size_t *value_data_size,
     uint8_t flags,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_entry_value_boolean(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint8_t *entry_value,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_entry_value_32bit(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint32_t *entry_value,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_entry_value_64bit(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint64_t *entry_value,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_entry_value_filetime(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint64_t *entry_value,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_entry_value_size(
     libnk2_item_t *item,
     uint32_t entry_type,
     size_t *entry_value,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_entry_value_floating_point(
     libnk2_item_t *item,
     uint32_t entry_type,
     double *entry_value,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_entry_value_utf8_string_size(
     libnk2_item_t *item,
     uint32_t entry_type,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_entry_value_utf8_string(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_entry_value_utf16_string_size(
     libnk2_item_t *item,
     uint32_t entry_type,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_entry_value_utf16_string(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_entry_value_binary_data_size(
     libnk2_item_t *item,
     uint32_t entry_type,
     size_t *size,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_entry_value_binary_data(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint8_t *binary_data,
     size_t size,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_entry_value_guid(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBNK2_ITEM_H ) */


/*
 * Item functions
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

#if !defined( _LIBNK2_ITEM_H )
#define _LIBNK2_ITEM_H

#include <common.h>
#include <types.h>

#include "libnk2_extern.h"
#include "libnk2_io_handle.h"
#include "libnk2_libbfio.h"
#include "libnk2_libcdata.h"
#include "libnk2_libcerror.h"
#include "libnk2_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libnk2_internal_item libnk2_internal_item_t;

struct libnk2_internal_item
{
	/* The record entries array
	 */
	libcdata_array_t *entries_array;
};

int libnk2_item_initialize(
     libnk2_item_t **item,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_free(
     libnk2_item_t **item,
     libcerror_error_t **error );

int libnk2_internal_item_free(
     libnk2_internal_item_t **internal_item,
     libcerror_error_t **error );

int libnk2_item_read_record_entries(
     libnk2_internal_item_t *internal_item,
     libnk2_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t item_index,
     uint32_t number_of_record_entries,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_number_of_entries(
     libnk2_item_t *item,
     int *number_of_entries,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_entry_by_index(
     libnk2_item_t *item,
     int entry_index,
     libnk2_record_entry_t **record_entry,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_item_get_entry_by_type(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint32_t value_type,
     libnk2_record_entry_t **record_entry,
     uint8_t flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBNK2_ITEM_H ) */


/*
 * Item values functions
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

#if !defined( _LIBNK2_ITEM_VALUES_H )
#define _LIBNK2_ITEM_VALUES_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libnk2_io_handle.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libnk2_item_entry libnk2_item_entry_t;

struct libnk2_item_entry
{
	/* The item entry type
	 */
	uint16_t entry_type;

	/* The item entry value type
	 */
	uint16_t value_type;

	/* The value size
	 */
	uint32_t value_size;

	/* The value data
	 */
	uint8_t *value_data;
};

typedef struct libnk2_item_values libnk2_item_values_t;

struct libnk2_item_values
{
	/* The item entries
	 */
	libnk2_item_entry_t **entry;

	/* The amount of item entries
	 */
	uint32_t amount_of_entries;
};

int libnk2_item_values_free(
     libnk2_item_values_t *item_values,
     liberror_error_t **error );

int libnk2_item_values_entries_allocate(
     libnk2_item_values_t *item_values,
     int amount_of_entries,
     liberror_error_t **error );

int libnk2_item_values_get_entry_value(
     libnk2_item_values_t *item_values,
     libnk2_io_handle_t *io_handle,
     uint32_t entry_type,
     uint32_t *value_type,
     uint8_t **value_data,
     size_t *value_data_size,
     liberror_error_t **error );

int libnk2_item_values_get_entry_value_boolean(
     libnk2_item_values_t *item_values,
     libnk2_io_handle_t *io_handle,
     uint32_t entry_type,
     uint8_t *entry_value,
     liberror_error_t **error );

int libnk2_item_values_get_entry_value_32bit(
     libnk2_item_values_t *item_values,
     libnk2_io_handle_t *io_handle,
     uint32_t entry_type,
     uint32_t *entry_value,
     liberror_error_t **error );

int libnk2_item_values_get_entry_value_64bit(
     libnk2_item_values_t *item_values,
     libnk2_io_handle_t *io_handle,
     uint32_t entry_type,
     uint64_t *entry_value,
     liberror_error_t **error );

int libnk2_item_values_get_entry_value_size(
     libnk2_item_values_t *item_values,
     libnk2_io_handle_t *io_handle,
     uint32_t entry_type,
     size_t *entry_value,
     liberror_error_t **error );

int libnk2_item_values_get_entry_value_string_size(
     libnk2_item_values_t *item_values,
     libnk2_io_handle_t *io_handle,
     uint32_t entry_type,
     size_t *size,
     int ascii_codepage,
     liberror_error_t **error );

int libnk2_item_values_get_entry_value_string(
     libnk2_item_values_t *item_values,
     libnk2_io_handle_t *io_handle,
     uint32_t entry_type,
     uint8_t *string,
     size_t size,
     int ascii_codepage,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif


/*
 * Item functions
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

#if !defined( _LIBNK2_INTERNAL_ITEM_H )
#define _LIBNK2_INTERNAL_ITEM_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libnk2_extern.h"
#include "libnk2_file.h"
#include "libnk2_item_values.h"
#include "libnk2_list_type.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libnk2_internal_item libnk2_internal_item_t;

struct libnk2_internal_item
{
	/* The internal file
	 */
	libnk2_internal_file_t *internal_file;

	/* The item values
	 */
	libnk2_item_values_t *item_values;

	/* The item reference list element
	 */
	libnk2_list_element_t *list_element;
};

int libnk2_item_initialize(
     libnk2_item_t **item,
     liberror_error_t **error );

LIBNK2_EXTERN int libnk2_item_free(
                   libnk2_item_t **item,
                   liberror_error_t **error );

int libnk2_item_free_no_detach(
     intptr_t *internal_item,
     liberror_error_t **error );

int libnk2_item_attach(
     libnk2_internal_item_t *internal_item,
     libnk2_internal_file_t *internal_file,
     libnk2_item_values_t *item_values,
     liberror_error_t **error );

int libnk2_item_detach(
     libnk2_internal_item_t *internal_item,
     liberror_error_t **error );

LIBNK2_EXTERN int libnk2_item_get_entry_value(
                   libnk2_item_t *item,
                   uint32_t entry_type,
                   uint32_t *value_type,
                   uint8_t **value_data,
                   size_t *value_data_size,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_item_get_entry_value_boolean(
                   libnk2_item_t *item,
                   uint32_t entry_type,
                   uint8_t *entry_value,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_item_get_entry_value_32bit(
                   libnk2_item_t *item,
                   uint32_t entry_type,
                   uint32_t *entry_value,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_item_get_entry_value_64bit(
                   libnk2_item_t *item,
                   uint32_t entry_type,
                   uint64_t *entry_value,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_item_get_entry_value_size(
                   libnk2_item_t *item,
                   uint32_t entry_type,
                   size_t *entry_value,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_item_get_entry_value_string_size(
                   libnk2_item_t *item,
                   uint32_t entry_type,
                   size_t *size,
                   liberror_error_t **error );

LIBNK2_EXTERN int libnk2_item_get_entry_value_string(
                   libnk2_item_t *item,
                   uint32_t entry_type,
                   uint8_t *string,
                   size_t size,
                   liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif


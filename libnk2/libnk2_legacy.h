/*
 * Legacy functions
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

#if !defined( _LIBNK2_LEGACY_H )
#define _LIBNK2_LEGACY_H

#include <common.h>
#include <types.h>

#include "libnk2_extern.h"
#include "libnk2_libcerror.h"
#include "libnk2_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBNK2 )

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

#endif /* !defined( HAVE_LOCAL_LIBNK2 ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBNK2_LEGACY_H ) */


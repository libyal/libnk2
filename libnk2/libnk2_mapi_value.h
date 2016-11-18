/*
 * MAPI value functions
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

#if !defined( _LIBNK2_MAPI_VALUE_H )
#define _LIBNK2_MAPI_VALUE_H

#include <common.h>
#include <types.h>

#include "libnk2_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

int libnk2_mapi_value_get_data_size(
     uint32_t value_type,
     size_t *value_data_size,
     libcerror_error_t **error );

int libnk2_mapi_value_data_contains_zero_bytes(
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libnk2_mapi_value_get_data_as_utf8_string_size(
     uint32_t value_type,
     const uint8_t *value_data,
     size_t value_data_size,
     int ascii_codepage,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libnk2_mapi_value_get_data_as_utf8_string(
     uint32_t value_type,
     const uint8_t *value_data,
     size_t value_data_size,
     int ascii_codepage,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int libnk2_mapi_value_get_data_as_utf16_string_size(
     uint32_t value_type,
     const uint8_t *value_data,
     size_t value_data_size,
     int ascii_codepage,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libnk2_mapi_value_get_data_as_utf16_string(
     uint32_t value_type,
     const uint8_t *value_data,
     size_t value_data_size,
     int ascii_codepage,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBNK2_MAPI_VALUE_H ) */


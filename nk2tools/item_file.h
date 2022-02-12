/*
 * Item file
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

#if !defined( _ITEM_FILE_H )
#define _ITEM_FILE_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#include "nk2tools_libcerror.h"
#include "nk2tools_libcfile.h"
#include "nk2tools_libfdatetime.h"
#include "nk2tools_libfguid.h"
#include "nk2tools_libnk2.h"

#if defined( __cplusplus )
extern "C" {
#endif

enum ITEM_FILE_FORMAT_FLAGS
{
	ITEM_FILE_FORMAT_FLAG_HEXADECIMAL		= 0x00000001UL,
	ITEM_FILE_FORMAT_FLAG_DURATION_IN_MINUTES	= 0x00000002UL,
};

typedef struct item_file item_file_t;

struct item_file
{
	/* The file handle
	 */
	libcfile_file_t *file_handle;
};

int item_file_initialize(
     item_file_t **item_file,
     libcerror_error_t **error );

int item_file_free(
     item_file_t **item_file,
     libcerror_error_t **error );

int item_file_open(
     item_file_t *item_file,
     const system_character_t *filename,
     libcerror_error_t **error );

int item_file_close(
     item_file_t *item_file,
     libcerror_error_t **error );

int item_file_write_buffer(
     item_file_t *item_file,
     const uint8_t *buffer,
     size_t buffer_size,
     libcerror_error_t **error );

int item_file_write_buffer_as_hexdump(
     item_file_t *item_file,
     const uint8_t *buffer,
     size_t buffer_size,
     libcerror_error_t **error );

int item_file_write_integer_32bit_as_decimal(
     item_file_t *item_file,
     uint32_t value_32bit,
     libcerror_error_t **error );

int item_file_write_integer_32bit_as_hexadecimal(
     item_file_t *item_file,
     uint32_t value_32bit,
     libcerror_error_t **error );

int item_file_write_floating_point(
     item_file_t *item_file,
     double floating_point,
     libcerror_error_t **error );

int item_file_write_string(
     item_file_t *item_file,
     const system_character_t *string,
     size_t string_length,
     libcerror_error_t **error );

int item_file_write_new_line(
     item_file_t *item_file,
     libcerror_error_t **error );

int item_file_write_filetime(
     item_file_t *item_file,
     libfdatetime_filetime_t *filetime,
     libcerror_error_t **error );

int item_file_write_guid(
     item_file_t *item_file,
     libfguid_identifier_t *guid,
     libcerror_error_t **error );

int item_file_write_value_description(
     item_file_t *item_file,
     const system_character_t *description,
     libcerror_error_t **error );

int item_file_write_value_integer_32bit_as_decimal(
     item_file_t *item_file,
     const system_character_t *description,
     uint32_t value_32bit,
     libcerror_error_t **error );

int item_file_write_value_integer_32bit_as_hexadecimal(
     item_file_t *item_file,
     const system_character_t *description,
     uint32_t value_32bit,
     libcerror_error_t **error );

int item_file_write_value_string(
     item_file_t *item_file,
     const system_character_t *description,
     const system_character_t *string,
     size_t string_length,
     libcerror_error_t **error );

int item_file_write_value_filetime(
     item_file_t *item_file,
     const system_character_t *description,
     libfdatetime_filetime_t *filetime,
     libcerror_error_t **error );

int item_file_write_record_entry(
     item_file_t *item_file,
     const system_character_t *description,
     libnk2_record_entry_t *record_entry,
     uint32_t format_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _ITEM_FILE_H ) */


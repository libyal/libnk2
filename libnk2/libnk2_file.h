/*
 * File functions
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

#if !defined( _LIBNK2_FILE_H )
#define _LIBNK2_FILE_H

#include <common.h>
#include <types.h>

#include "libnk2_extern.h"
#include "libnk2_io_handle.h"
#include "libnk2_libbfio.h"
#include "libnk2_libcdata.h"
#include "libnk2_libcerror.h"
#include "libnk2_types.h"

#if defined( _MSC_VER ) || defined( __BORLANDC__ ) || defined( __MINGW32_VERSION ) || defined( __MINGW64_VERSION_MAJOR )

/* This inclusion is needed otherwise some linkers
 * mess up exporting the legacy functions
 */
#include "libnk2_legacy.h"
#endif

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libnk2_internal_file libnk2_internal_file_t;

struct libnk2_internal_file
{
	/* The items array
	 */
	libcdata_array_t *items_array;

	/* The IO handle
	 */
	libnk2_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;

	/* The last modification date and time
	 */
	uint64_t modification_time;
};

LIBNK2_EXTERN \
int libnk2_file_initialize(
     libnk2_file_t **file,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_file_free(
     libnk2_file_t **file,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_file_signal_abort(
     libnk2_file_t *file,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_file_open(
     libnk2_file_t *file,
     const char *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )
LIBNK2_EXTERN \
int libnk2_file_open_wide(
     libnk2_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error );
#endif

LIBNK2_EXTERN \
int libnk2_file_open_file_io_handle(
     libnk2_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_file_close(
     libnk2_file_t *file,
     libcerror_error_t **error );

int libnk2_file_open_read(
     libnk2_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_file_get_ascii_codepage(
     libnk2_file_t *file,
     int *ascii_codepage,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_file_set_ascii_codepage(
     libnk2_file_t *file,
     int ascii_codepage,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_file_get_modification_time(
     libnk2_file_t *file,
     uint64_t *filetime,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_file_get_number_of_items(
     libnk2_file_t *file,
     int *number_of_items,
     libcerror_error_t **error );

LIBNK2_EXTERN \
int libnk2_file_get_item(
     libnk2_file_t *file,
     int item_index,
     libnk2_item_t **item,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBNK2_FILE_H ) */


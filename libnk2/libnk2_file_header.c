/*
 * File header functions
 *
 * Copyright (C) 2009-2018, Joachim Metz <joachim.metz@gmail.com>
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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libnk2_debug.h"
#include "libnk2_file_header.h"
#include "libnk2_io_handle.h"
#include "libnk2_libcerror.h"
#include "libnk2_libcnotify.h"

#include "nk2_file_header.h"

/* Creates file header
 * Make sure the value file_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_header_initialize(
     libnk2_file_header_t **file_header,
     libcerror_error_t **error )
{
	static char *function = "libnk2_file_header_initialize";

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
	if( *file_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file header value already set.",
		 function );

		return( -1 );
	}
	*file_header = memory_allocate_structure(
	                libnk2_file_header_t );

	if( *file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *file_header,
	     0,
	     sizeof( libnk2_file_header_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file_header != NULL )
	{
		memory_free(
		 *file_header );

		*file_header = NULL;
	}
	return( -1 );
}

/* Frees file header
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_header_free(
     libnk2_file_header_t **file_header,
     libcerror_error_t **error )
{
	static char *function = "libnk2_file_header_free";

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
	if( *file_header != NULL )
	{
		memory_free(
		 *file_header );

		*file_header = NULL;
	}
	return( 1 );
}

/* Reads the file header data
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_header_read_data(
     libnk2_file_header_t *file_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libnk2_file_header_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
#endif

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size < sizeof( nk2_file_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file header:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) data,
		 sizeof( nk2_file_header_t ),
		 0 );
	}
#endif
	if( memory_compare(
	     ( (nk2_file_header_t *) data )->signature,
	     nk2_file_signature,
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid file signature.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (nk2_file_header_t *) data )->number_of_items,
	 file_header->number_of_items );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (nk2_file_header_t *) data )->signature,
		 value_32bit );
		libcnotify_printf(
		 "%s: signature\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (nk2_file_header_t *) data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (nk2_file_header_t *) data )->unknown2,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown2\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: number of items\t\t\t\t: %" PRIu32 "\n",
		 function,
		 file_header->number_of_items );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
	return( 1 );
}

/* Reads the file header
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_header_read_file_io_handle(
     libnk2_file_header_t *file_header,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	uint8_t file_header_data[ sizeof( nk2_file_header_t ) ];

	static char *function = "libnk2_file_header_read_file_io_handle";
	ssize_t read_count    = 0;

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading file header at offset: 0 (0x00000000)\n",
		 function );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     0,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek file header offset: 0.",
		 function );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              file_header_data,
	              sizeof( nk2_file_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( nk2_file_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header data.",
		 function );

		return( -1 );
	}
	if( libnk2_file_header_read_data(
	     file_header,
	     file_header_data,
	     sizeof( nk2_file_header_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header.",
		 function );

		return( -1 );
	}
	return( 1 );
}

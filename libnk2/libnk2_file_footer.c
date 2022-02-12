/*
 * File footer functions
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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libnk2_debug.h"
#include "libnk2_file_footer.h"
#include "libnk2_libcerror.h"
#include "libnk2_libcnotify.h"
#include "libnk2_libfdatetime.h"

#include "nk2_file_footer.h"

/* Creates file footer
 * Make sure the value file_footer is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_footer_initialize(
     libnk2_file_footer_t **file_footer,
     libcerror_error_t **error )
{
	static char *function = "libnk2_file_footer_initialize";

	if( file_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file footer.",
		 function );

		return( -1 );
	}
	if( *file_footer != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file footer value already set.",
		 function );

		return( -1 );
	}
	*file_footer = memory_allocate_structure(
	                libnk2_file_footer_t );

	if( *file_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file footer.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *file_footer,
	     0,
	     sizeof( libnk2_file_footer_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file footer.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file_footer != NULL )
	{
		memory_free(
		 *file_footer );

		*file_footer = NULL;
	}
	return( -1 );
}

/* Frees file footer
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_footer_free(
     libnk2_file_footer_t **file_footer,
     libcerror_error_t **error )
{
	static char *function = "libnk2_file_footer_free";

	if( file_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file footer.",
		 function );

		return( -1 );
	}
	if( *file_footer != NULL )
	{
		memory_free(
		 *file_footer );

		*file_footer = NULL;
	}
	return( 1 );
}

/* Reads the file footer data
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_footer_read_data(
     libnk2_file_footer_t *file_footer,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libnk2_file_footer_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
#endif

	if( file_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file footer.",
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
	if( data_size < sizeof( nk2_file_footer_t ) )
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
		 "%s: file footer:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) data,
		 sizeof( nk2_file_footer_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint64_little_endian(
	 ( (nk2_file_footer_t *) data )->modification_time,
	 file_footer->modification_time );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (nk2_file_footer_t *) data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( libnk2_debug_print_filetime_value(
		     function,
		     "modification time\t\t\t\t",
		     ( (nk2_file_footer_t *) data )->modification_time,
		     8,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print FILETIME value.",
			 function );

			return( -1 );
		}
		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
	return( 1 );
}

/* Reads the file footer
 * Returns 1 if successful or -1 on error
 */
int libnk2_file_footer_read_file_io_handle(
     libnk2_file_footer_t *file_footer,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	uint8_t file_footer_data[ sizeof( nk2_file_footer_t ) ];

	static char *function = "libnk2_file_footer_read_file_io_handle";
	ssize_t read_count    = 0;

	if( file_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file footer.",
		 function );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              file_footer_data,
	              sizeof( nk2_file_footer_t ),
	              error );

	if( read_count != (ssize_t) sizeof( nk2_file_footer_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file footer data.",
		 function );

		return( -1 );
	}
	if( libnk2_file_footer_read_data(
	     file_footer,
	     file_footer_data,
	     sizeof( nk2_file_footer_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file footer.",
		 function );

		return( -1 );
	}
	return( 1 );
}


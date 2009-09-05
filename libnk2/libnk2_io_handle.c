/*
 * libnk2 Input/Output (IO) handle
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

#include <common.h>
#include <endian.h>
#include <memory.h>
#include <types.h>

#include <liberror.h>
#include <libnotify.h>

#include "libnk2_array_type.h"
#include "libnk2_debug.h"
#include "libnk2_definitions.h"
#include "libnk2_io_handle.h"
#include "libnk2_item_values.h"
#include "libnk2_libbfio.h"

#include "nk2_file_header.h"

const uint8_t nk2_file_signature[ 4 ] = { 0x0d, 0xf0, 0xad, 0xba };

/* Initialize an io handle
 * Make sure the value io_handle is pointing to is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_initialize(
     libnk2_io_handle_t **io_handle,
     liberror_error_t **error )
{
	static char *function = "libnk2_io_handle_initialize";

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid io handle.",
		 function );

		return( -1 );
	}
	if( *io_handle == NULL )
	{
		*io_handle = (libnk2_io_handle_t *) memory_allocate(
		                                     sizeof( libnk2_io_handle_t ) );

		if( *io_handle == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create io handle.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     *io_handle,
		     0,
		     sizeof( libnk2_io_handle_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear file.",
			 function );

			memory_free(
			 *io_handle );

			*io_handle = NULL;

			return( -1 );
		}
	}
	return( 1 );
}

/* Frees an exisisting io handle
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_free(
     libnk2_io_handle_t **io_handle,
     liberror_error_t **error )
{
	static char *function = "libnk2_io_handle_free";
	int result            = 1;

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid io handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		if( ( ( *io_handle )->handle_created_in_library != 0 )
		 && ( ( *io_handle )->file_io_handle != NULL )
		 && ( libbfio_handle_free(
		       &( ( *io_handle )->file_io_handle ),
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free file io handle.",
			 function );

			result = -1;
		}
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( result );
}

/* Opens an io handle
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_open(
     libnk2_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     int flags,
     liberror_error_t **error )
{
        static char *function = "libnk2_io_handle_open";

        if( io_handle == NULL )
        {
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
                 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
                 "%s: invalid io handle.",
                 function );

                return( -1 );
        }
	if( io_handle->file_io_handle != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid io handle - file io handle already set.",
		 function );

		return( -1 );
	}
        if( file_io_handle == NULL )
        {
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
                 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
                 "%s: invalid file io handle.",
                 function );

                return( -1 );
        }
	io_handle->file_io_handle = file_io_handle;

	if( libbfio_handle_open(
	     io_handle->file_io_handle,
	     flags,
	     error ) != 1 )
	{
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_IO,
                 LIBERROR_IO_ERROR_OPEN_FAILED,
                 "%s: unable to open file io handle.",
                 function );

                return( -1 );
	}
	return( 1 );
}

/* Closes an io handle
 * Returns 0 if successful or -1 on error
 */
int libnk2_io_handle_close(
     libnk2_io_handle_t *io_handle,
     liberror_error_t **error )
{
        static char *function = "libnk2_io_handle_close";

        if( io_handle == NULL )
        {
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
                 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
                 "%s: invalid io handle.",
                 function );

                return( -1 );
        }
#if defined( HAVE_DEBUG_OUTPUT )
	if( libnk2_debug_print_read_offsets(
	     io_handle->file_io_handle,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
                 LIBERROR_ERROR_DOMAIN_RUNTIME,
                 LIBERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print the read offsets.",
		 function );
	}
#endif
	if( libbfio_handle_close(
	     io_handle->file_io_handle,
	     error ) != 0 )
	{
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_IO,
                 LIBERROR_IO_ERROR_CLOSE_FAILED,
                 "%s: unable to close file io handle.",
                 function );

                return( -1 );
	}
	return( 0 );
}

/* Reads the file header
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_read_file_header(
     libnk2_io_handle_t *io_handle,
     uint32_t *amount_of_items,
     liberror_error_t **error )
{
	nk2_file_header_t file_header;

	static char *function = "libnk2_io_handle_read_file_header";
	ssize_t read_count    = 0;

#if defined( HAVE_VERBOSE_OUTPUT )
	uint32_t test         = 0;
#endif

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid io handle.",
		 function );

		return( -1 );
	}
	if( io_handle->file_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid io handle - missing file io handle.",
		 function );

		return( -1 );
	}
	if( amount_of_items == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid amount of items.",
		 function );

		return( -1 );
	}
	read_count = libbfio_handle_read(
	              io_handle->file_io_handle,
	              (uint8_t *) &file_header,
	              sizeof( nk2_file_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( nk2_file_header_t ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	libnotify_verbose_printf(
	 "%s: file header:\n",
	 function );
	libnotify_verbose_print_data(
	 (uint8_t *) &file_header,
	 sizeof( nk2_file_header_t ) );
#endif

	if( memory_compare(
	     file_header.signature,
	     nk2_file_signature,
	     4 ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid file signature.",
		 function );

		return( -1 );
	}
	endian_little_convert_32bit(
	 *amount_of_items,
	 file_header.amount_of_items );

#if defined( HAVE_VERBOSE_OUTPUT )
	endian_little_convert_32bit(
	 test,
	 file_header.signature );
	libnotify_verbose_printf(
	 "%s: signature\t\t: 0x%08" PRIx32 "\n",
	 function,
	 test );
	endian_little_convert_32bit(
	 test,
	 file_header.unknown1 );
	libnotify_verbose_printf(
	 "%s: unknown1\t\t: 0x%08" PRIx32 "\n",
	 function,
	 test );
	endian_little_convert_32bit(
	 test,
	 file_header.unknown2 );
	libnotify_verbose_printf(
	 "%s: unknown2\t\t: 0x%08" PRIx32 "\n",
	 function,
	 test );
	libnotify_verbose_printf(
	 "%s: amount of items\t: %" PRIu32 "\n",
	 function,
	 *amount_of_items );
	libnotify_verbose_printf(
	 "\n" );
#endif

	return( 1 );
}

/* Reads the items into the item table
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_read_items(
     libnk2_io_handle_t *io_handle,
     uint32_t amount_of_items,
     libnk2_array_t *item_table,
     liberror_error_t **error )
{
	uint8_t amount_of_item_values_data[ 4 ];

	libnk2_item_values_t *item_values = NULL;
	static char *function             = "libnk2_io_handle_read_items";
	ssize_t read_count                = 0;
	uint32_t amount_of_item_values    = 0;
	uint32_t item_iterator            = 0;
	int item_entry_index              = 0;

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid io handle.",
		 function );

		return( -1 );
	}
	if( io_handle->file_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid io handle - missing file io handle.",
		 function );

		return( -1 );
	}
	if( item_table == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item table.",
		 function );

		return( -1 );
	}
	for( item_iterator = 0; item_iterator < amount_of_items; item_iterator++ )
	{
		read_count = libbfio_handle_read(
			      io_handle->file_io_handle,
			      amount_of_item_values_data,
			      4,
			      error );

		if( read_count != (ssize_t) 4 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read amount of item values data.",
			 function );

			return( -1 );
		}
		endian_little_convert_32bit(
		 amount_of_item_values,
		 amount_of_item_values_data );

		if( amount_of_item_values == 0 )
		{
			break;
		}
#if defined( HAVE_VERBOSE_OUTPUT )
		libnotify_verbose_printf(
		 "%s: item: %03" PRIu32 " amount of item values\t: %" PRIu32 "\n",
		 function,
		 item_iterator,
		 amount_of_item_values );
#endif

		if( libnk2_item_values_initialize(
		     &item_values,
		     amount_of_item_values,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create item values.",
			 function );

			return( -1 );
		}
		if( libnk2_item_values_read(
		     item_values,
		     io_handle,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read item values.",
			 function );

			libnk2_item_values_free(
			 &item_values,
			 error );

			return( -1 );
		}
		if( libnk2_array_append_entry(
		     item_table,
		     &item_entry_index,
		     (intptr_t *) item_values,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append item values to item table.",
			 function );

			libnk2_item_values_free(
			 &item_values,
			 error );

			return( -1 );
		}
		item_values = NULL;
	}
	return( 1 );
}


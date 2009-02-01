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

#include "libnk2_debug.h"
#include "libnk2_definitions.h"
#include "libnk2_io_handle.h"
#include "libnk2_libbfio.h"
#include "libnk2_notify.h"

#include "nk2_file_header.h"
#include "nk2_item.h"

uint8_t nk2_file_signature[ 4 ] = { 0x0d, 0xf0, 0xad, 0xba };

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
		if( libbfio_file_initialize(
		     &( ( *io_handle )->file_io_handle ),
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to initialize file io handle.",
			 function );

			memory_free(
			 *io_handle );

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
		if( ( ( *io_handle )->file_io_handle != NULL )
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
     const char *filename,
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
	if( libbfio_file_set_name(
	     io_handle->file_io_handle,
	     filename,
	     narrow_string_length(
	      filename ) + 1,
	     error ) != 1 )
	{
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_RUNTIME,
                 LIBERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file io handle.",
                 function );

                return( -1 );
	}
	if( libbfio_open(
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

#if defined( LIBNK2_WIDE_CHARACTER_TYPE )

/* Opens an io handle
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_open_wide(
     libnk2_io_handle_t *io_handle,
     const wchar_t *filename,
     int flags,
     liberror_error_t **error )
{
        static char *function = "libnk2_io_handle_open_wide";

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
	if( libbfio_set_filename_wide(
	     io_handle->file_io_handle,
	     filename,
	     wide_string_length(
	      filename ) + 1,
	     error ) != 1 )
	{
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_RUNTIME,
                 LIBERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file io handle.",
                 function );

                return( -1 );
	}
	if( libbfio_open(
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

#endif

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
	if( libbfio_close(
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
	uint64_t test         = 0;

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
	read_count = libbfio_read(
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
	libnk2_notify_verbose_printf(
	 "%s: file header:\n",
	 function );
	libnk2_notify_verbose_dump_data(
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
	libnk2_notify_verbose_printf(
	 "%s: signature\t\t: 0x%08" PRIx64 "\n",
	 function,
	 test );
	endian_little_convert_32bit(
	 test,
	 file_header.unknown1 );
	libnk2_notify_verbose_printf(
	 "%s: unknown1\t\t: 0x%08" PRIx64 "\n",
	 function,
	 test );
	endian_little_convert_32bit(
	 test,
	 file_header.unknown2 );
	libnk2_notify_verbose_printf(
	 "%s: unknown2\t\t: 0x%08" PRIx64 "\n",
	 function,
	 test );
	libnk2_notify_verbose_printf(
	 "%s: amount of items\t: %" PRIu64 "\n",
	 function,
	 *amount_of_items );
	libnk2_notify_verbose_printf(
	 "\n" );
#endif

	return( 1 );
}

/* Reads an item
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_read_item(
     libnk2_io_handle_t *io_handle,
     liberror_error_t **error )
{
	uint8_t buffer[ 4 ];

	nk2_item_value_entry_t item_value_entry;

	uint8_t *value_data            = NULL;
	static char *function          = "libnk2_io_handle_read_item";
	ssize_t read_count             = 0;
	uint64_t test                  = 0;
	uint32_t amount_of_item_values = 0;
	uint32_t item_value_iterator   = 0;
	uint32_t value_data_size       = 0;
	uint16_t entry_type            = 0;
	uint16_t value_type            = 0;
	int item_index                 = 0;

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
	while( 1 )
	{
		read_count = libbfio_read(
			      io_handle->file_io_handle,
			      buffer,
			      4,
			      error );

		if( read_count != (ssize_t) 4 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read item separator.",
			 function );

			return( -1 );
		}
		endian_little_convert_32bit(
		 amount_of_item_values,
		 buffer );

		if( amount_of_item_values == 0 )
		{
			break;
		}
#if defined( HAVE_VERBOSE_OUTPUT )
		libnk2_notify_verbose_printf(
		 "%s: item\t\t\t: %d\n",
		 function,
		 item_index );
		libnk2_notify_verbose_printf(
		 "%s: amount of item values\t: %" PRIu32 "\n",
		 function,
		 amount_of_item_values );
#endif

		/* Loop through all item value entries
		 */
		for( item_value_iterator = 0; item_value_iterator < amount_of_item_values; item_value_iterator++ )
		{
			read_count = libbfio_read(
				      io_handle->file_io_handle,
				      (uint8_t *) &item_value_entry,
				      sizeof( nk2_item_value_entry_t ),
				      error );

			if( read_count != (ssize_t) sizeof( nk2_item_value_entry_t ) )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read item value entry.",
				 function );

				return( -1 );
			}
			endian_little_convert_16bit(
			 value_type,
			 item_value_entry.value_type );
			endian_little_convert_16bit(
			 entry_type,
			 item_value_entry.entry_type );

#if defined( HAVE_DEBUG_OUTPUT )
			libnk2_notify_verbose_printf(
			 "%s: item value entry:\n",
			 function );
			libnk2_notify_verbose_dump_data(
			 (uint8_t *) &item_value_entry,
			 sizeof( nk2_item_value_entry_t ) );
#endif

#if defined( HAVE_VERBOSE_OUTPUT )
			libnk2_notify_verbose_printf(
			 "%s: value type\t\t\t: 0x%04" PRIx16 " (%" PRIs_LIBNK2 ")\n",
			 function,
			 value_type,
			 libnk2_debug_get_value_type_string(
			  value_type ) );
			libnk2_notify_verbose_printf(
			 "%s: entry type\t\t\t: 0x%04" PRIx16 " (%" PRIs_LIBNK2 ")\n",
			 function,
			 entry_type,
			 libnk2_debug_get_entry_type_string(
			  entry_type,
			  value_type ) );
			endian_little_convert_32bit(
			 test,
			 item_value_entry.unknown1 );
			libnk2_notify_verbose_printf(
			 "%s: unknown1\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 test );
			endian_little_convert_32bit(
			 test,
			 item_value_entry.unknown2 );
			libnk2_notify_verbose_printf(
			 "%s: unknown2\t\t\t: 0x%04" PRIx64 "\n",
			 function,
			 test );
			endian_little_convert_32bit(
			 test,
			 item_value_entry.unknown3 );
			libnk2_notify_verbose_printf(
			 "%s: unknown3\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 test );
#endif

			/* Read the value data
			 */
			if( ( value_type == 0x001f )
			 || ( value_type == 0x0102 ) )
			{
				read_count = libbfio_read(
					      io_handle->file_io_handle,
					      buffer,
					      4,
					      error );

				if( read_count != (ssize_t) 4 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read value data size.",
					 function );

					return( -1 );
				}
				endian_little_convert_16bit(
				 value_data_size,
				 buffer );

#if defined( HAVE_VERBOSE_OUTPUT )
				libnk2_notify_verbose_printf(
				 "%s: value data size\t\t: %" PRIu32 "\n",
				 function,
				 value_data_size );
#endif

				/* TODO check if value data size > SSIZE_MAX */

				value_data = (uint8_t *) memory_allocate(
							  (size_t) value_data_size );

				if( value_data == NULL )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_MEMORY,
					 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
					 "%s: unable to create value data.",
					 function );

					return( -1 );
				}
				read_count = libbfio_read(
					      io_handle->file_io_handle,
					      value_data,
					      value_data_size,
					      error );

				if( read_count != (ssize_t) value_data_size )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read value data.",
					 function );

					memory_free(
					 value_data );

					return( -1 );
				}
#if defined( HAVE_VERBOSE_OUTPUT )
				libnk2_notify_verbose_printf(
				 "%s: value data:\n",
				 function );
				libnk2_notify_verbose_dump_data(
				 value_data,
				 value_data_size );
#endif

				memory_free(
				 value_data );
			}
#if defined( HAVE_VERBOSE_OUTPUT )
			libnk2_notify_verbose_printf(
			 "\n" );
#endif
		}
		item_index++;
	}
	return( 1 );
}


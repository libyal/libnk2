/*
 * Input/Output (IO) handle functions
 *
 * Copyright (C) 2009-2017, Joachim Metz <joachim.metz@gmail.com>
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

#include "libnk2_codepage.h"
#include "libnk2_debug.h"
#include "libnk2_definitions.h"
#include "libnk2_io_handle.h"
#include "libnk2_item.h"
#include "libnk2_libbfio.h"
#include "libnk2_libcdata.h"
#include "libnk2_libcerror.h"
#include "libnk2_libcnotify.h"
#include "libnk2_libfdatetime.h"
#include "libnk2_libfmapi.h"
#include "libnk2_record_entry.h"
#include "libnk2_unused.h"

#include "nk2_file_footer.h"
#include "nk2_file_header.h"
#include "nk2_item.h"

const uint8_t nk2_file_signature[ 4 ] = { 0x0d, 0xf0, 0xad, 0xba };

/* Creates an IO handle
 * Make sure the value io_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_initialize(
     libnk2_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libnk2_io_handle_initialize";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid IO handle value already set.",
		 function );

		return( -1 );
	}
	*io_handle = memory_allocate_structure(
	              libnk2_io_handle_t );

	if( *io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *io_handle,
	     0,
	     sizeof( libnk2_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file.",
		 function );

		goto on_error;
	}
	( *io_handle )->ascii_codepage = LIBNK2_CODEPAGE_WINDOWS_1252;

	return( 1 );

on_error:
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( -1 );
}

/* Frees an IO handle
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_free(
     libnk2_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libnk2_io_handle_free";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( 1 );
}

/* Clears the IO handle
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_clear(
     libnk2_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	static char *function = "libnk2_io_handle_clear";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( memory_set(
	     io_handle,
	     0,
	     sizeof( libnk2_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		return( -1 );
	}
	io_handle->ascii_codepage = LIBNK2_CODEPAGE_WINDOWS_1252;

	return( 1 );
}

/* Reads the file header
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_read_file_header(
     libnk2_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t *number_of_items,
     libcerror_error_t **error )
{
	nk2_file_header_t file_header;

	static char *function = "libnk2_io_handle_read_file_header";
	ssize_t read_count    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
#endif

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( number_of_items == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of items.",
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
	              (uint8_t *) &file_header,
	              sizeof( nk2_file_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( nk2_file_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header.",
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
		 (uint8_t *) &file_header,
		 sizeof( nk2_file_header_t ),
		 0 );
	}
#endif
	if( memory_compare(
	     file_header.signature,
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
	 file_header.number_of_items,
	 *number_of_items );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 file_header.signature,
		 value_32bit );
		libcnotify_printf(
		 "%s: signature\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.unknown2,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown2\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: number of items\t\t\t: %" PRIu32 "\n",
		 function,
		 *number_of_items );

		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );
}

/* Reads the items into the items array
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_read_items(
     libnk2_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t number_of_items,
     libcdata_array_t *items_array,
     libcerror_error_t **error )
{
	uint8_t number_of_record_entries_data[ 4 ];

	libnk2_item_t *item               = NULL;
	static char *function             = "libnk2_io_handle_read_items";
	ssize_t read_count                = 0;
	uint32_t item_index               = 0;
	uint32_t number_of_record_entries = 0;
	int entry_index                   = 0;

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( items_array == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid items array.",
		 function );

		return( -1 );
	}
	for( item_index = 0;
	     item_index < number_of_items;
	     item_index++ )
	{
		read_count = libbfio_handle_read_buffer(
			      file_io_handle,
			      number_of_record_entries_data,
			      4,
			      error );

		if( read_count != (ssize_t) 4 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read item: %" PRIu32 " number of record entries data.",
			 function,
			 item_index );

			goto on_error;
		}
		byte_stream_copy_to_uint32_little_endian(
		 number_of_record_entries_data,
		 number_of_record_entries );

		if( number_of_record_entries == 0 )
		{
			break;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: item: %03" PRIu32 " number of record entries\t\t: %" PRIu32 "\n",
			 function,
			 item_index,
			 number_of_record_entries );

			libcnotify_printf(
			 "\n" );
		}
#endif
		if( libnk2_item_initialize(
		     &item,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create item.",
			 function );

			goto on_error;
		}
		if( libnk2_io_handle_read_record_entries(
		     io_handle,
		     file_io_handle,
		     item_index,
		     number_of_record_entries,
		     ( (libnk2_internal_item_t *) item )->entries_array,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read record entries: %" PRIu32 ".",
			 function,
			 item_index );

			goto on_error;
		}
		if( libcdata_array_append_entry(
		     items_array,
		     &entry_index,
		     (intptr_t *) item,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append record entries to items array.",
			 function );

			goto on_error;
		}
		item = NULL;
	}
	return( 1 );

on_error:
	if( item != NULL )
	{
		libnk2_item_free(
		 &item,
		 NULL );
	}
	libcdata_array_empty(
	 items_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libnk2_internal_item_free,
	 NULL );

	return( -1 );
}

/* Reads the items value
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_read_record_entries(
     libnk2_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t item_index LIBNK2_ATTRIBUTE_UNUSED,
     uint32_t number_of_record_entries,
     libcdata_array_t *entries_array,
     libcerror_error_t **error )
{
	nk2_item_value_entry_t item_value_entry;

	libnk2_record_entry_t *record_entry = NULL;
	static char *function               = "libnk2_io_handle_read_record_entries";
	ssize_t read_count                  = 0;
	uint32_t record_entry_index         = 0;
	int entry_index                     = 0;

	LIBNK2_UNREFERENCED_PARAMETER( item_index )

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	for( record_entry_index = 0;
	     record_entry_index < number_of_record_entries;
	     record_entry_index++ )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: reading item: %03" PRIu32 " value: %03" PRIu32 "\n",
			 function,
			 item_index,
			 record_entry_index );
		}
#endif
		if( libnk2_record_entry_initialize(
		     &record_entry,
		     io_handle->ascii_codepage,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create record entry.",
			 function );

			goto on_error;
		}
		read_count = libbfio_handle_read_buffer(
			      file_io_handle,
			      (uint8_t *) &item_value_entry,
			      sizeof( nk2_item_value_entry_t ),
			      error );

		if( read_count != (ssize_t) sizeof( nk2_item_value_entry_t ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read record entry data.",
			 function );

			goto on_error;
		}
		if( libnk2_record_entry_read_data(
		     record_entry,
		     (uint8_t *) &item_value_entry,
		     sizeof( nk2_item_value_entry_t ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read record entry.",
			 function );

			goto on_error;
		}
		if( libnk2_record_entry_read_value(
		     record_entry,
		     file_io_handle,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read record entry value.",
			 function );

			goto on_error;
		}
/* TODO refactor */
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: item: %03" PRIu32 " value: %03" PRIu32 " value data:\n",
			 function,
			 item_index,
			 record_entry_index );

			if( libnk2_debug_print_mapi_value(
			     ( (libnk2_internal_record_entry_t *) record_entry )->entry_type,
			     ( (libnk2_internal_record_entry_t *) record_entry )->value_type,
			     ( (libnk2_internal_record_entry_t *) record_entry )->value_data,
			     ( (libnk2_internal_record_entry_t *) record_entry )->value_data_size,
			     io_handle->ascii_codepage,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print MAPI value.",
				 function );

				goto on_error;
			}
		}
#endif
		if( libcdata_array_append_entry(
		     entries_array,
		     &entry_index,
		     (intptr_t *) record_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append record entry to array.",
			 function );

			goto on_error;
		}
		record_entry = NULL;

		if( io_handle->abort != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_ABORT_REQUESTED,
			 "%s: abort requested.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( record_entry != NULL )
	{
		libnk2_internal_record_entry_free(
		 (libnk2_internal_record_entry_t **) &record_entry,
		 NULL );
	}
	libcdata_array_empty(
	 entries_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libnk2_internal_record_entry_free,
	 NULL );

	return( -1 );
}

/* Reads the file footer
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_read_file_footer(
     libnk2_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint64_t *modification_time,
     libcerror_error_t **error )
{
	nk2_file_footer_t file_footer;

	static char *function = "libnk2_io_handle_read_file_footer";
	ssize_t read_count    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
#endif

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( modification_time == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid modification time.",
		 function );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              (uint8_t *) &file_footer,
	              sizeof( nk2_file_footer_t ),
	              error );

	if( read_count != (ssize_t) sizeof( nk2_file_footer_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file footer.",
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
		 (uint8_t *) &file_footer,
		 sizeof( nk2_file_footer_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint64_little_endian(
	 file_footer.modification_time,
	 *modification_time );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 file_footer.unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( libnk2_debug_print_filetime_value(
		     function,
		     "modification time\t\t\t",
		     file_footer.modification_time,
		     8,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print filetime value.",
			 function );

			return( -1 );
		}
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );
}


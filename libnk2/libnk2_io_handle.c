/*
 * Input/Output (IO) handle functions
 *
 * Copyright (C) 2009-2014, Joachim Metz <joachim.metz@gmail.com>
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
#include "libnk2_libbfio.h"
#include "libnk2_libcdata.h"
#include "libnk2_libcerror.h"
#include "libnk2_libcnotify.h"
#include "libnk2_libfdatetime.h"
#include "libnk2_libfmapi.h"
#include "libnk2_libfvalue.h"
#include "libnk2_mapi.h"
#include "libnk2_unused.h"
#include "libnk2_value_identifier.h"

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
		 "%s: signature\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.unknown2,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown2\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: number of items\t: %" PRIu32 "\n",
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
	uint8_t number_of_item_values_data[ 4 ];

	libfvalue_table_t *values_table = NULL;
	static char *function           = "libnk2_io_handle_read_items";
	ssize_t read_count              = 0;
	uint32_t number_of_item_values  = 0;
	uint32_t item_iterator          = 0;
	int item_entry_index            = 0;

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
	for( item_iterator = 0;
	     item_iterator < number_of_items;
	     item_iterator++ )
	{
		read_count = libbfio_handle_read_buffer(
			      file_io_handle,
			      number_of_item_values_data,
			      4,
			      error );

		if( read_count != (ssize_t) 4 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read item: %" PRIu32 " number of item values data.",
			 function,
			 item_iterator );

			goto on_error;
		}
		byte_stream_copy_to_uint32_little_endian(
		 number_of_item_values_data,
		 number_of_item_values );

		if( number_of_item_values == 0 )
		{
			break;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: item: %03" PRIu32 " number of item values\t: %" PRIu32 "\n",
			 function,
			 item_iterator,
			 number_of_item_values );
		}
#endif
		if( libfvalue_table_initialize(
		     &values_table,
		     number_of_item_values,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create item values table.",
			 function );

			goto on_error;
		}
		if( libnk2_io_handle_read_item_values(
		     io_handle,
		     file_io_handle,
		     item_iterator,
		     number_of_item_values,
		     values_table,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read item values: %" PRIu32 ".",
			 function,
			 item_iterator );

			goto on_error;
		}
		if( libcdata_array_append_entry(
		     items_array,
		     &item_entry_index,
		     (intptr_t *) values_table,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append item values to items array.",
			 function );

			goto on_error;
		}
		values_table = NULL;
	}
	return( 1 );

on_error:
	if( values_table != NULL )
	{
		libfvalue_table_free(
		 &values_table,
		 NULL );
	}
	return( -1 );
}

/* Reads the items value
 * Returns 1 if successful or -1 on error
 */
int libnk2_io_handle_read_item_values(
     libnk2_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t item_index LIBNK2_ATTRIBUTE_UNUSED,
     uint32_t number_of_item_values,
     libfvalue_table_t *values_table,
     libcerror_error_t **error )
{
	uint8_t value_data_size_data[ 4 ];

	nk2_item_value_entry_t item_value_entry;

	libnk2_value_identifier_t *value_identifier = NULL;
	libfvalue_value_t *value                    = NULL;
	uint8_t *value_data                         = NULL;
	static char *function                       = "libnk2_io_handle_read_item_values";
	ssize_t read_count                          = 0;
	uint32_t item_value_index                   = 0;
	uint16_t value_data_size                    = 0;
	uint16_t value_boolean                      = 0;
	uint8_t value_type                          = 0;
	int value_encoding                          = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit                        = 0;
#endif

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
	if( values_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid values table.",
		 function );

		return( -1 );
	}
	if( libnk2_value_identifier_initialize(
	     &value_identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create value identifier.",
		 function );

		goto on_error;
	}
	for( item_value_index = 0;
	     item_value_index < number_of_item_values;
	     item_value_index++ )
	{
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
			 "%s: unable to read item value.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: item: %03" PRIu32 " value: %03" PRIu32 "\n",
			 function,
			 item_index,
			 item_value_index );
			libcnotify_print_data(
			 (uint8_t *) &item_value_entry,
			 sizeof( nk2_item_value_entry_t ),
			 0 );
		}
#endif
		byte_stream_copy_to_uint16_little_endian(
		 item_value_entry.value_type,
		 value_identifier->value_type );
		byte_stream_copy_to_uint16_little_endian(
		 item_value_entry.entry_type,
		 value_identifier->entry_type );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: item: %03" PRIu32 " value: %03" PRIu32 " value type\t\t: 0x%04" PRIx16 " (%s : %s)\n",
			 function,
			 item_index,
			 item_value_index,
			 value_identifier->value_type,
			 libfmapi_value_type_get_identifier(
			  value_identifier->value_type ),
			 libfmapi_value_type_get_description(
			  value_identifier->value_type ) );

			libcnotify_printf(
			 "%s: item: %03" PRIu32 " value: %03" PRIu32 " entry type\t\t: 0x%04" PRIx16 " (%s : %s)\n",
			 function,
			 item_index,
			 item_value_index,
			 value_identifier->entry_type,
			 libfmapi_property_type_get_identifier(
			  NULL,
			  value_identifier->entry_type,
			  value_identifier->value_type ),
			 libfmapi_property_type_get_description(
			  NULL,
			  value_identifier->entry_type,
			  value_identifier->value_type ) );

			byte_stream_copy_to_uint32_little_endian(
			 item_value_entry.unknown1,
			 value_32bit );
			libcnotify_printf(
			 "%s: item: %03" PRIu32 " value: %03" PRIu32 " unknown1\t\t: 0x%08" PRIx32 "\n",
			 function,
			 item_index,
			 item_value_index,
			 value_32bit );

			libcnotify_printf(
			 "%s: item: %03" PRIu32 " value: %03" PRIu32 " value data array:\n",
			 function,
			 item_index,
			 item_value_index );
			libcnotify_print_data(
			 item_value_entry.value_data_array,
			 8,
			 0 );
		}
#endif
		/* TODO add other value types to the item entry
		 */
		switch( value_identifier->value_type )
		{
			case LIBNK2_VALUE_TYPE_BOOLEAN:
				value_type      = LIBFVALUE_VALUE_TYPE_BOOLEAN;
				value_data_size = 2;
				value_encoding  = LIBFVALUE_ENDIAN_LITTLE;
				break;

			case LIBNK2_VALUE_TYPE_INTEGER_16BIT_SIGNED:
				value_type      = LIBFVALUE_VALUE_TYPE_INTEGER_16BIT;
				value_data_size = 2;
				value_encoding  = LIBFVALUE_ENDIAN_LITTLE;
				break;

			case LIBNK2_VALUE_TYPE_INTEGER_32BIT_SIGNED:
				value_type      = LIBFVALUE_VALUE_TYPE_INTEGER_32BIT;
				value_data_size = 4;
				value_encoding  = LIBFVALUE_ENDIAN_LITTLE;
				break;

			case LIBNK2_VALUE_TYPE_INTEGER_64BIT_SIGNED:
				value_type      = LIBFVALUE_VALUE_TYPE_INTEGER_64BIT;
				value_data_size = 8;
				value_encoding  = LIBFVALUE_ENDIAN_LITTLE;
				break;

			case LIBNK2_VALUE_TYPE_FLOAT_32BIT:
				value_type      = LIBFVALUE_VALUE_TYPE_FLOATING_POINT_32BIT;
				value_data_size = 4;
				value_encoding  = LIBFVALUE_ENDIAN_LITTLE;
				break;

			case LIBNK2_VALUE_TYPE_DOUBLE_64BIT:
				value_type      = LIBFVALUE_VALUE_TYPE_FLOATING_POINT_64BIT;
				value_data_size = 8;
				value_encoding  = LIBFVALUE_ENDIAN_LITTLE;
				break;

			case LIBNK2_VALUE_TYPE_ERROR:
				value_type      = LIBFVALUE_VALUE_TYPE_ENUMERATION;
				value_data_size = 4;
				value_encoding  = LIBFVALUE_ENDIAN_LITTLE;
				break;

			case LIBNK2_VALUE_TYPE_CURRENCY:
				value_type      = LIBFVALUE_VALUE_TYPE_INTEGER_64BIT;
				value_data_size = 8;
				value_encoding  = LIBFVALUE_ENDIAN_LITTLE;
				break;

			case LIBNK2_VALUE_TYPE_FLOATINGTIME:
				value_type      = LIBFVALUE_VALUE_TYPE_FLOATINGTIME;
				value_data_size = 8;
				value_encoding  = LIBFVALUE_ENDIAN_LITTLE;
				break;

			case LIBNK2_VALUE_TYPE_FILETIME:
				value_type      = LIBFVALUE_VALUE_TYPE_FILETIME;
				value_data_size = 8;
				value_encoding  = LIBFVALUE_ENDIAN_LITTLE;
				break;

			case LIBNK2_VALUE_TYPE_STRING_ASCII:
				value_type      = LIBFVALUE_VALUE_TYPE_STRING_BYTE_STREAM;
				value_data_size = 0;
				value_encoding  = io_handle->ascii_codepage;
				break;

			case LIBNK2_VALUE_TYPE_STRING_UNICODE:
				value_type      = LIBFVALUE_VALUE_TYPE_STRING_UTF16;
				value_data_size = 0;
				value_encoding  = LIBFVALUE_CODEPAGE_UTF16_LITTLE_ENDIAN;
				break;

			case LIBNK2_VALUE_TYPE_BINARY_DATA:
				value_type      = LIBFVALUE_VALUE_TYPE_BINARY_DATA;
				value_data_size = 0;
				break;

			default:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported value type: 0x%04" PRIx16 ".",
				 function,
				 value_identifier->value_type );

				goto on_error;
		}
		if( value_data_size == 0 )
		{
			/* The value data size is stored after the item value
			 */
			read_count = libbfio_handle_read_buffer(
				      file_io_handle,
				      value_data_size_data,
				      4,
				      error );

			if( read_count != (ssize_t) 4 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read value data size.",
				 function );

				goto on_error;
			}
			byte_stream_copy_to_uint16_little_endian(
			 value_data_size_data,
			 value_data_size );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: item: %03" PRIu32 " value: %03" PRIu32 " value data size\t: %" PRIu16 "\n",
			 function,
			 item_index,
			 item_value_index,
			 value_data_size );
		}
#endif
		if( libfvalue_value_type_initialize(
		     &value,
		     value_type,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create value: 0x%04" PRIx16 " 0x%04" PRIx16 ".",
			 function,
			 value_identifier->entry_type,
			 value_identifier->value_type );

			goto on_error;
		}
		if( libfvalue_value_set_identifier(
		     value,
		     (uint8_t *) value_identifier,
		     sizeof( libnk2_value_identifier_t ),
		     LIBFVALUE_VALUE_IDENTIFIER_FLAG_MANAGED,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set identifier in value: 0x%04" PRIx16 " 0x%04" PRIx16 ".",
			 function,
			 value_identifier->entry_type,
			 value_identifier->value_type );

			libfvalue_value_free(
			 &value,
			 NULL );

			goto on_error;
		}
		if( libfvalue_table_set_value_by_index(
		     values_table,
		     item_value_index,
		     value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set value: 0x%04" PRIx16 " 0x%04" PRIx16 " in values table.",
			 function,
			 value_identifier->entry_type,
			 value_identifier->value_type );

			libfvalue_value_free(
			 &value,
			 NULL );

			goto on_error;
		}
		value_data = (uint8_t *) memory_allocate(
		                          (size_t) value_data_size );

		if( value_data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create value data.",
			 function );

			goto on_error;
		}
		switch( value_identifier->value_type )
		{
			case LIBNK2_VALUE_TYPE_STRING_ASCII:
			case LIBNK2_VALUE_TYPE_STRING_UNICODE:
			case LIBNK2_VALUE_TYPE_BINARY_DATA:
				/* Read the value data
				 */
				read_count = libbfio_handle_read_buffer(
					      file_io_handle,
					      value_data,
					      (size_t) value_data_size,
					      error );

				if( read_count != (ssize_t) value_data_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read value data.",
					 function );

					memory_free(
					 value_data );

					goto on_error;
				}
				break;

			default:
				/* Copy the value data from the item value value data array
				 */
				if( memory_copy(
				     value_data,
				     item_value_entry.value_data_array,
				     value_data_size ) == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
					 "%s: unable to copy value date.",
					 function );

					memory_free(
					 value_data );

					goto on_error;
				}
				break;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: item: %03" PRIu32 " value: %03" PRIu32 " value data:\n",
			 function,
			 item_index,
			 item_value_index );

			if( libnk2_debug_mapi_value_print(
			     value_identifier->entry_type,
			     value_identifier->value_type,
			     value_data,
			     (size_t) value_data_size,
			     io_handle->ascii_codepage,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print value data.",
				 function );

				memory_free(
				 value_data );

				goto on_error;
			}
		}
#endif
/* TODO check if this is working as intended
		if( value_identifier->value_type == LIBNK2_VALUE_TYPE_BOOLEAN )
		{
			byte_stream_copy_to_uint16_little_endian(
			 value_data_size_data,
			 value_boolean );

			if( libfvalue_value_copy_from_16bit(
			     value,
			     0,
			     value_boolean,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set value: 0x%04" PRIx16 " 0x%04" PRIx16 " boolean value.",
				 function,
				 value_identifier->entry_type,
				 value_identifier->value_type );

				memory_free(
				 value_data );

				goto on_error;
			}
			memory_free(
			 value_data );
		}
		else
*/
		{
			/* The value takes over managent of the value data
			 */
			if( libfvalue_value_set_data(
			     value,
			     value_data,
			     (size_t) value_data_size,
			     value_encoding,
			     LIBFVALUE_VALUE_DATA_FLAG_MANAGED,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set value: 0x%04" PRIx16 " 0x%04" PRIx16 " data.",
				 function,
				 value_identifier->entry_type,
				 value_identifier->value_type );

				memory_free(
				 value_data );

				goto on_error;
			}
		}
		value = NULL;

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
	if( libnk2_value_identifier_free(
	     &value_identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free value identifier.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( value_identifier != NULL )
	{
		libnk2_value_identifier_free(
		 &value_identifier,
		 NULL );
	}
	libfvalue_table_empty(
	 values_table,
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

	static char *function             = "libnk2_io_handle_read_file_footer";
	ssize_t read_count                = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libcstring_system_character_t filetime_string[ 48 ];

	libfdatetime_filetime_t *filetime = NULL;
	uint32_t value_32bit              = 0;
	int result                        = 0;
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

		goto on_error;
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
		if( libfdatetime_filetime_initialize(
		     &filetime,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create filetime.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint32_little_endian(
		 file_footer.unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( libfdatetime_filetime_copy_from_byte_stream(
		     filetime,
		     file_footer.modification_time,
		     8,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to filetime.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_filetime_copy_to_utf16_string(
			  filetime,
			  (uint16_t *) filetime_string,
			  48,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			  error );
#else
		result = libfdatetime_filetime_copy_to_utf8_string(
			  filetime,
			  (uint8_t *) filetime_string,
			  48,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy filetime to string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: modification time\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n\n",
		 function,
		 filetime_string );

		libcnotify_printf(
		 "\n" );

		if( libfdatetime_filetime_free(
		     &filetime,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free filetime.",
			 function );

			goto on_error;
		}
	}
#endif
	return( 1 );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
#endif
	return( -1 );
}


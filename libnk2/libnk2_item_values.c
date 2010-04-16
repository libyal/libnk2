/*
 * Item values functions
 *
 * Copyright (c) 2010, Joachim Metz <jbmetz@users.sourceforge.net>
 * Copyright (c) 2008-2010, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations.
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

#include <liberror.h>
#include <libnotify.h>

#include "libnk2_debug.h"
#include "libnk2_definitions.h"
#include "libnk2_item_values.h"
#include "libnk2_libbfio.h"
#include "libnk2_libfmapi.h"
#include "libnk2_libuna.h"

#include "nk2_item.h"

/* Creates the item values
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_values_initialize(
     libnk2_item_values_t **item_values,
     uint32_t amount_of_entries,
     liberror_error_t **error )
{
	static char *function = "libnk2_item_values_initialize";
	size_t entries_size   = 0;

	if( item_values == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item values.",
		 function );

		return( -1 );
	}
	if( *item_values == NULL )
	{
		*item_values = (libnk2_item_values_t *) memory_allocate(
		                                         sizeof( libnk2_item_values_t ) );

		if( *item_values == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create item values.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     *item_values,
		     0,
		     sizeof( libnk2_item_values_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear item values.",
			 function );

			memory_free(
			 *item_values );

			*item_values = NULL;

			return( -1 );
		}
		if( amount_of_entries > 0 )
		{
			entries_size = sizeof( libnk2_item_entry_t ) * amount_of_entries;

			if( entries_size > (size_t) SSIZE_MAX )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid entries size value exceeds maximum.",
				 function );

				return( -1 );
			}
			( *item_values )->entry = (libnk2_item_entry_t *) memory_allocate(
			                                                   entries_size );

			if( ( *item_values )->entry == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create item values entries.",
				 function );

				return( -1 );
			}
			if( memory_set(
			     ( *item_values )->entry,
			     0,
			     entries_size ) == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_SET_FAILED,
				 "%s: unable to clear item values entries.",
				 function );

				return( -1 );
			}
			( *item_values )->amount_of_entries = amount_of_entries;
		}
	}
	return( 1 );
}

/* Frees the item values
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_values_free(
     libnk2_item_values_t **item_values,
     liberror_error_t **error )
{
	static char *function   = "libnk2_item_values_free";
	uint32_t entry_iterator = 0;

	if( item_values == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item values.",
		 function );

		return( -1 );
	}
	if( *item_values != NULL )
	{
		if( ( *item_values )->entry != NULL )
		{
			for( entry_iterator = 0; entry_iterator < ( *item_values )->amount_of_entries; entry_iterator++ )
			{
				if( ( *item_values )->entry[ entry_iterator ].value_data != NULL )
				{
					memory_free(
					 ( *item_values )->entry[ entry_iterator ].value_data );
				}
			}
			memory_free(
			 ( *item_values )->entry );
		}
		memory_free(
		 *item_values );

		*item_values = NULL;
	}
	return( 1 );
}

/* Frees the item values as a referenced value
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_values_free_as_referenced_value(
     intptr_t *item_values,
     liberror_error_t **error )
{
	static char *function = "libnk2_item_values_free_as_referenced_value";
	int result            = 1;

	if( libnk2_item_values_free(
	     (libnk2_item_values_t **) &item_values,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free item values.",
		 function );

		result = -1;
	}
	return( result );
}

/* Reads the items value
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_values_read(
     libnk2_item_values_t *item_values,
     libnk2_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     liberror_error_t **error )
{
	uint8_t value_data_size_data[ 4 ];

	nk2_item_value_entry_t item_value_entry;

	static char *function              = "libnk2_item_values_read";
	ssize_t read_count                 = 0;
	uint32_t item_value_entry_iterator = 0;

#if defined( HAVE_VERBOSE_OUTPUT )
	uint32_t value_32bit               = 0;
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t item_iterator             = 0;
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
	if( item_values == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item values.",
		 function );

		return( -1 );
	}
	/* Loop through all item value entries
	 */
	for( item_value_entry_iterator = 0;
	     item_value_entry_iterator < item_values->amount_of_entries;
	     item_value_entry_iterator++ )
	{
		read_count = libbfio_handle_read(
			      file_io_handle,
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
#if defined( HAVE_DEBUG_OUTPUT )
		if( libnotify_verbose != 0 )
		{
			libnotify_printf(
			 "%s: item: %03" PRIu32 " value entry: %03" PRIu32 "\n",
			 function,
			 item_iterator,
			 item_value_entry_iterator );
			libnotify_print_data(
			 (uint8_t *) &item_value_entry,
			 sizeof( nk2_item_value_entry_t ) );
		}
#endif

		byte_stream_copy_to_uint16_little_endian(
		 item_value_entry.value_type,
		 item_values->entry[ item_value_entry_iterator ].value_type );
		byte_stream_copy_to_uint16_little_endian(
		 item_value_entry.entry_type,
		 item_values->entry[ item_value_entry_iterator ].entry_type );

#if defined( HAVE_VERBOSE_OUTPUT )
		if( libnotify_verbose != 0 )
		{
			libnotify_printf(
			 "%s: item: %03" PRIu32 " value entry: %03" PRIu32 " value type\t\t: 0x%04" PRIx16 " (%s : %s)\n",
			 function,
			 item_iterator,
			 item_value_entry_iterator,
			 item_values->entry[ item_value_entry_iterator ].value_type,
			 libfmapi_value_type_get_identifier(
			  item_values->entry[ item_value_entry_iterator ].value_type ),
			 libfmapi_value_type_get_description(
			  item_values->entry[ item_value_entry_iterator ].value_type ) );
			libnotify_printf(
			 "%s: item: %03" PRIu32 " value entry: %03" PRIu32 " entry type\t\t: 0x%04" PRIx16 " (%s : %s)\n",
			 function,
			 item_iterator,
			 item_value_entry_iterator,
			 item_values->entry[ item_value_entry_iterator ].entry_type,
			 libfmapi_property_type_get_identifier(
			  NULL,
			  item_values->entry[ item_value_entry_iterator ].entry_type,
			  item_values->entry[ item_value_entry_iterator ].value_type ),
			 libfmapi_property_type_get_description(
			  NULL,
			  item_values->entry[ item_value_entry_iterator ].entry_type,
			  item_values->entry[ item_value_entry_iterator ].value_type ) );

			byte_stream_copy_to_uint32_little_endian(
			 item_value_entry.unknown1,
			 value_32bit );
			libnotify_printf(
			 "%s: item: %03" PRIu32 " value entry: %03" PRIu32 " unknown1\t\t: 0x%08" PRIx32 "\n",
			 function,
			 item_iterator,
			 item_value_entry_iterator,
			 value_32bit );

			libnotify_printf(
			 "%s: item: %03" PRIu32 " value entry: %03" PRIu32 " value data array:\n",
			 function,
			 item_iterator,
			 item_value_entry_iterator );
			libnotify_print_data(
			 item_value_entry.value_data_array,
			 8 );
		}
#endif

		/* TODO add other value types to the item entry
		 */

		switch( item_values->entry[ item_value_entry_iterator ].value_type )
		{
			case 0x0002:
			case 0x000b:
				item_values->entry[ item_value_entry_iterator ].value_data_size = 2;
				break;

			case 0x0003:
			case 0x0004:
			case 0x000a:
				item_values->entry[ item_value_entry_iterator ].value_data_size = 4;
				break;

			case 0x0005:
			case 0x0006:
			case 0x0007:
			case 0x0014:
			case 0x0040:
				item_values->entry[ item_value_entry_iterator ].value_data_size = 8;
				break;

			case 0x001e:
			case 0x001f:
			case 0x0102:
				/* The value data size is stored after the item value entry
				 */
				read_count = libbfio_handle_read(
					      file_io_handle,
					      value_data_size_data,
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
				byte_stream_copy_to_uint16_little_endian(
				 value_data_size_data,
				 item_values->entry[ item_value_entry_iterator ].value_data_size );

				break;

			default:
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported value type: 0x%04" PRIx32 ".",
				 function,
				 item_values->entry[ item_value_entry_iterator ].value_type );

				return( -1 );
		}
#if defined( HAVE_VERBOSE_OUTPUT )
		if( libnotify_verbose != 0 )
		{
			libnotify_printf(
			 "%s: item: %03" PRIu32 " value entry: %03" PRIu32 " value data size\t: %" PRIu32 "\n",
			 function,
			 item_iterator,
			 item_value_entry_iterator,
			 item_values->entry[ item_value_entry_iterator ].value_data_size );
		}
#endif

		if( item_values->entry[ item_value_entry_iterator ].value_data_size > (uint32_t) SSIZE_MAX )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid value data size value exceeds maximum.",
			 function );

			return( -1 );
		}

		item_values->entry[ item_value_entry_iterator ].value_data = (uint8_t *) memory_allocate(
											  (size_t) item_values->entry[ item_value_entry_iterator ].value_data_size );

		if( item_values->entry[ item_value_entry_iterator ].value_data == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create value data.",
			 function );

			return( -1 );
		}

		switch( item_values->entry[ item_value_entry_iterator ].value_type )
		{
			case 0x001e:
			case 0x001f:
			case 0x0102:
				/* Read the value data
				 */
				read_count = libbfio_handle_read(
					      file_io_handle,
					      item_values->entry[ item_value_entry_iterator ].value_data,
					      (size_t) item_values->entry[ item_value_entry_iterator ].value_data_size,
					      error );

				if( read_count != (ssize_t) item_values->entry[ item_value_entry_iterator ].value_data_size )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read value data.",
					 function );

					memory_free(
					 item_values->entry[ item_value_entry_iterator ].value_data );

					item_values->entry[ item_value_entry_iterator ].value_data      = NULL;
					item_values->entry[ item_value_entry_iterator ].value_data_size = 0;

					return( -1 );
				}
				break;

			default:
				/* Copy the value data from the item value entry value data array
				 */
				if( memory_copy(
				     item_values->entry[ item_value_entry_iterator ].value_data,
				     item_value_entry.value_data_array,
				     item_values->entry[ item_value_entry_iterator ].value_data_size ) == NULL )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_MEMORY,
					 LIBERROR_MEMORY_ERROR_COPY_FAILED,
					 "%s: unable to copy value date.",
					 function );
				}
				break;
		}
#if defined( HAVE_VERBOSE_OUTPUT )
		if( libnotify_verbose != 0 )
		{
			libnotify_printf(
			 "%s: item: %03" PRIu32 " value entry: %03" PRIu32 " value data:\n",
			 function,
			 item_iterator,
			 item_value_entry_iterator );

			if( libnk2_debug_mapi_value_print(
			     item_values->entry[ item_value_entry_iterator ].entry_type,
			     item_values->entry[ item_value_entry_iterator ].value_type,
			     item_values->entry[ item_value_entry_iterator ].value_data,
			     item_values->entry[ item_value_entry_iterator ].value_data_size,
			     LIBUNA_CODEPAGE_ASCII,
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print value data.",
				 function );

				return( -1 );
			}
		}
#endif
	}
	return( 1 );
}

/* Retrieves the amount of item entries
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_values_get_amount_of_entries(
     libnk2_item_values_t *item_values,
     uint32_t *amount_of_entries,
     liberror_error_t **error )
{
	static char *function = "libnk2_item_values_get_amount_of_entries";

	if( item_values == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item values.",
		 function );

		return( -1 );
	}
	if( amount_of_entries == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid amount of entries.",
		 function );

		return( -1 );
	}
	*amount_of_entries = item_values->amount_of_entries;

	return( 1 );
}

/* Retrieves the entry type of a specific entry from the referenced item values
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_values_get_entry_type(
     libnk2_item_values_t *item_values,
     int entry_index,
     uint32_t *entry_type,
     uint32_t *value_type,
     liberror_error_t **error )
{
	static char *function = "libnk2_item_values_get_entry_type";

	if( item_values == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item values.",
		 function );

		return( -1 );
	}
	if( item_values->entry == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item values - missing entries.",
		 function );

		return( -1 );
	}
	if( ( entry_index < 0 )
	 || ( (uint32_t) entry_index >= item_values->amount_of_entries ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_OUT_OF_RANGE,
		 "%s: invalid entry index out of range.",
		 function );

		return( -1 );
	}
	if( entry_type == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry type.",
		 function );

		return( -1 );
	}
	if( value_type == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value type.",
		 function );

		return( -1 );
	}
	*entry_type = item_values->entry[ entry_index ].entry_type;
	*value_type = item_values->entry[ entry_index ].value_type;

	return( 1 );
}

/* Retrieves the value of a specific entry from the referenced item values
 *
 * When the LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE is set
 * the value type is ignored and set. The default behavior is a strict
 * matching of the value type. In this case the value type must be filled
 * with the corresponding value type
 *
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_values_get_entry_value(
     libnk2_item_values_t *item_values,
     uint32_t entry_type,
     uint32_t *value_type,
     uint8_t **value_data, 
     size_t *value_data_size,
     uint8_t flags,
     liberror_error_t **error )
{
	static char *function    = "libnk2_item_values_get_entry_value";
	uint8_t entry_type_match = 0;
	int entry_iterator       = 0;

	if( item_values == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item values.",
		 function );

		return( -1 );
	}
	if( item_values->entry == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item values - missing entries.",
		 function );

		return( -1 );
	}
	if( value_type == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value type.",
		 function );

		return( -1 );
	}
	if( value_data == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value data.",
		 function );

		return( -1 );
	}
	if( value_data_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value data size.",
		 function );

		return( -1 );
	}
	for( entry_iterator = 0;
	     (uint32_t) entry_iterator < item_values->amount_of_entries;
	     entry_iterator++ )
	{
		if( item_values->entry[ entry_iterator ].entry_type == entry_type )
		{
			entry_type_match = 1;
		}
		if( entry_type_match != 0 )
		{
			if( ( ( flags & LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE ) == LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE )
			 || ( item_values->entry[ entry_iterator ].value_type == *value_type ) )
			{
				if( ( flags & LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE ) == LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE )
				{
					*value_type = item_values->entry[ entry_iterator ].value_type;
				}
				*value_data      = item_values->entry[ entry_iterator ].value_data;
				*value_data_size = item_values->entry[ entry_iterator ].value_data_size;

				return( 1 );
			}
		}
	}
	return( 0 );
}


/*
 * Item functions
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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libnk2_definitions.h"
#include "libnk2_io_handle.h"
#include "libnk2_item.h"
#include "libnk2_libbfio.h"
#include "libnk2_libcerror.h"
#include "libnk2_libfmapi.h"
#include "libnk2_libfvalue.h"
#include "libnk2_mapi.h"
#include "libnk2_value_identifier.h"

/* Creates an item
 * Make sure the value item is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_initialize(
     libnk2_item_t **item,
     libnk2_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfvalue_table_t *values_table,
     uint8_t flags,
     libcerror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_initialize";

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	if( *item != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid item value already set.",
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
	if( ( flags & ~( LIBNK2_ITEM_FLAG_MANAGED_FILE_IO_HANDLE ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags: 0x%02" PRIx8 ".",
		 function,
		 flags );

		return( -1 );
	}
	internal_item = memory_allocate_structure(
	                 libnk2_internal_item_t );

	if( internal_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create internal item.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_item,
	     0,
	     sizeof( libnk2_internal_item_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear internal item.",
		 function );

		memory_free(
		 internal_item );

		return( -1 );
	}
	if( ( flags & LIBNK2_ITEM_FLAG_MANAGED_FILE_IO_HANDLE ) == 0 )
	{
		internal_item->file_io_handle = file_io_handle;
	}
	else
	{
		if( libbfio_handle_clone(
		     &( internal_item->file_io_handle ),
		     file_io_handle,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy file IO handle.",
			 function );

			goto on_error;
		}
		if( libbfio_handle_set_open_on_demand(
		     internal_item->file_io_handle,
		     1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to set open on demand in file IO handle.",
			 function );

			goto on_error;
		}
	}
	internal_item->io_handle    = io_handle;
	internal_item->flags        = flags;
	internal_item->values_table = values_table;

	*item = (libnk2_item_t *) internal_item;

	return( 1 );

on_error:
	if( internal_item != NULL )
	{
		if( ( flags & LIBNK2_ITEM_FLAG_MANAGED_FILE_IO_HANDLE ) != 0 )
		{
			if( internal_item->file_io_handle != NULL )
			{
				libbfio_handle_free(
				 &( internal_item->file_io_handle ),
				 NULL );
			}
		}
		memory_free(
		 internal_item );
	}
	return( -1 );
}

/* Frees an item
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_free(
     libnk2_item_t **item,
     libcerror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_free";

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	if( *item != NULL )
	{
		internal_item = (libnk2_internal_item_t *) *item;
		*item         = NULL;

		/* The io_handle and values_table references are freed elsewhere
		 */
		if( ( internal_item->flags & LIBNK2_ITEM_FLAG_MANAGED_FILE_IO_HANDLE ) != 0 )
		{
			if( internal_item->file_io_handle != NULL )
			{
				if( libbfio_handle_close(
				     internal_item->file_io_handle,
				     error ) != 0 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_CLOSE_FAILED,
					 "%s: unable to close file IO handle.",
					 function );

					return( -1 );
				}
				if( libbfio_handle_free(
				     &( internal_item->file_io_handle ),
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free file IO handle.",
					 function );

					return( -1 );
				}
			}
		}
		memory_free(
		 internal_item );
	}
	return( 1 );
}

/* Retrieves the number of entries
 * All sets in an item contain the same number of entries
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_get_number_of_entries(
     libnk2_item_t *item,
     uint32_t *number_of_entries,
     libcerror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_get_number_of_entries";
	int number_of_values                  = 0;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( number_of_entries == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of entries.",
		 function );

		return( -1 );
	}
	if( libfvalue_table_get_number_of_values(
	     internal_item->values_table,
	     &number_of_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to get number of values from values table.",
		 function );

		return( -1 );
	}
	*number_of_entries = (uint32_t) number_of_values;

	return( 1 );
}

/* Retrieves the entry and value type of a specific entry
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_get_entry_type(
     libnk2_item_t *item,
     int entry_index,
     uint32_t *entry_type,
     uint32_t *value_type,
     libcerror_error_t **error )
{
	libfvalue_value_t *value                    = NULL;
	libnk2_internal_item_t *internal_item       = NULL;
	libnk2_value_identifier_t *value_identifier = NULL;
	static char *function                       = "libnk2_item_get_entry_type";
	size_t value_identifier_size                = 0;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( entry_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry type.",
		 function );

		return( -1 );
	}
	if( value_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value type.",
		 function );

		return( -1 );
	}
	if( libfvalue_table_get_value_by_index(
	     internal_item->values_table,
	     entry_index,
	     &value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value: %d from values table.",
		 function,
		 entry_index );

		return( -1 );
	}
	if( libfvalue_value_get_identifier(
	     value,
	     (uint8_t **) &value_identifier,
	     &value_identifier_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value: %d identifier.",
		 function,
		 entry_index );

		return( -1 );
	}
	if( value_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing value identifier: %d.",
		 function,
		 entry_index );

		return( -1 );
	}
	if( value_identifier_size != sizeof( libnk2_value_identifier_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: missing value identifier size vale out of bounds.",
		 function );

		return( -1 );
	}
	*entry_type = value_identifier->entry_type;
	*value_type = value_identifier->value_type;

	return( 1 );
}

/* Retrieves the value type of a specific entry type
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_value_type(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint32_t *value_type,
     libcerror_error_t **error )
{
	libnk2_value_identifier_t value_identifier;

	libfvalue_value_t *value              = NULL;
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_get_value_type";
	int result                            = 0;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( value_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value type.",
		 function );

		return( -1 );
	}
	value_identifier.entry_type = (uint16_t) entry_type;
	value_identifier.value_type = 0;

	result = libfvalue_table_get_value_by_identifier(
	          internal_item->values_table,
	          (uint8_t *) &value_identifier,
	          2,
	          &value,
	          LIBFVALUE_TABLE_FLAG_ALLOW_PARTIAL_MATCH,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value: 0x%04" PRIx16 " 0x%04" PRIx16 " from values table.",
		 function,
		 value_identifier.entry_type,
		 value_identifier.value_type );

		return( -1 );
	}
	else if( result != 0 )
	{
		*value_type = value_identifier.value_type;
	}
	return( result );
}

/* Retrieves the value of a specific entry
 *
 * When the LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE is set
 * the value type is ignored and set. The default behavior is a strict
 * matching of the value type. In this case the value type must be filled
 * with the corresponding value type
 *
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint32_t *value_type,
     uint8_t **value_data,
     size_t *value_data_size,
     uint8_t flags,
     libcerror_error_t **error )
{
	libnk2_value_identifier_t value_identifier;

	libfvalue_value_t *value              = NULL;
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_get_entry_value";
	size_t value_identifier_size          = 0;
	uint8_t values_table_flags            = 0;
	int encoding                          = 0;
	int result                            = 0;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( value_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value type.",
		 function );

		return( -1 );
	}
	if( ( flags & ~( LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags: 0x%02" PRIx8 ".",
		 function,
		 flags );

		return( -1 );
	}
	value_identifier.entry_type = (uint16_t) entry_type;

	if( ( flags & LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE ) == 0 )
	{
		value_identifier.value_type = 0;
		value_identifier_size       = 2;
		values_table_flags          = LIBFVALUE_TABLE_FLAG_ALLOW_PARTIAL_MATCH;
	}
	else
	{
		value_identifier.value_type = (uint16_t) *value_type;
		value_identifier_size       = sizeof( libnk2_value_identifier_t );
	}
	result = libfvalue_table_get_value_by_identifier(
	          internal_item->values_table,
	          (uint8_t *) &value_identifier,
	          value_identifier_size,
	          &value,
	          values_table_flags,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value: 0x%04" PRIx16 " 0x%04" PRIx16 " from values table.",
		 function,
		 value_identifier.entry_type,
		 value_identifier.value_type );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libfvalue_value_get_data(
		     value,
		     value_data,
		     value_data_size,
		     &encoding,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value data.",
			 function );

			return( -1 );
		}
		*value_type = value_identifier.value_type;
	}
	return( result );
}

/* Retrieves the boolean value of a specific entry
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_boolean(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint8_t *entry_value,
     libcerror_error_t **error )
{
	libnk2_value_identifier_t value_identifier;

	libfvalue_value_t *value              = NULL;
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_get_entry_value_boolean";
	int result                            = 0;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	value_identifier.entry_type = (uint16_t) entry_type;
	value_identifier.value_type = LIBNK2_VALUE_TYPE_BOOLEAN;

	result = libfvalue_table_get_value_by_identifier(
	          internal_item->values_table,
	          (uint8_t *) &value_identifier,
	          sizeof( libnk2_value_identifier_t ),
	          &value,
	          0,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value: 0x%04" PRIx16 " 0x%04" PRIx16 " from values table.",
		 function,
		 value_identifier.entry_type,
		 value_identifier.value_type );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libfvalue_value_copy_to_boolean(
		     value,
		     0,
		     entry_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy value: 0x%04" PRIx16 " 0x%04" PRIx16 " to a boolean value.",
			 function,
			 value_identifier.entry_type,
			 value_identifier.value_type );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the 32-bit value of a specific entry
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_32bit(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint32_t *entry_value,
     libcerror_error_t **error )
{
	libnk2_value_identifier_t value_identifier;

	libfvalue_value_t *value              = NULL;
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_get_entry_value_32bit";
	int result                            = 0;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	value_identifier.entry_type = (uint16_t) entry_type;
	value_identifier.value_type = LIBNK2_VALUE_TYPE_INTEGER_32BIT_SIGNED;

	result = libfvalue_table_get_value_by_identifier(
	          internal_item->values_table,
	          (uint8_t *) &value_identifier,
	          sizeof( libnk2_value_identifier_t ),
	          &value,
	          0,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value: 0x%04" PRIx16 " 0x%04" PRIx16 " from values table.",
		 function,
		 value_identifier.entry_type,
		 value_identifier.value_type );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libfvalue_value_copy_to_32bit(
		     value,
		     0,
		     entry_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy value: 0x%04" PRIx16 " 0x%04" PRIx16 " to a 32-bit value.",
			 function,
			 value_identifier.entry_type,
			 value_identifier.value_type );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the 64-bit value of a specific entry
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_64bit(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint64_t *entry_value,
     libcerror_error_t **error )
{
	libnk2_value_identifier_t value_identifier;

	libfvalue_value_t *value              = NULL;
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_get_entry_value_64bit";
	int result                            = 0;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	value_identifier.entry_type = (uint16_t) entry_type;
	value_identifier.value_type = LIBNK2_VALUE_TYPE_INTEGER_64BIT_SIGNED;

	result = libfvalue_table_get_value_by_identifier(
	          internal_item->values_table,
	          (uint8_t *) &value_identifier,
	          sizeof( libnk2_value_identifier_t ),
	          &value,
	          0,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value: 0x%04" PRIx16 " 0x%04" PRIx16 " from values table.",
		 function,
		 value_identifier.entry_type,
		 value_identifier.value_type );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libfvalue_value_copy_to_64bit(
		     value,
		     0,
		     entry_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy value: 0x%04" PRIx16 " 0x%04" PRIx16 " to a 64-bit value.",
			 function,
			 value_identifier.entry_type,
			 value_identifier.value_type );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the 64-bit filetime value of a specific entry
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_filetime(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint64_t *entry_value,
     libcerror_error_t **error )
{
	libnk2_value_identifier_t value_identifier;

	libfvalue_value_t *value              = NULL;
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_get_entry_value_filetime";
	int result                            = 0;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	value_identifier.entry_type = (uint16_t) entry_type;
	value_identifier.value_type = LIBNK2_VALUE_TYPE_FILETIME;

	result = libfvalue_table_get_value_by_identifier(
	          internal_item->values_table,
	          (uint8_t *) &value_identifier,
	          sizeof( libnk2_value_identifier_t ),
	          &value,
	          0,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value: 0x%04" PRIx16 " 0x%04" PRIx16 " from values table.",
		 function,
		 value_identifier.entry_type,
		 value_identifier.value_type );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libfvalue_value_copy_to_64bit(
		     value,
		     0,
		     entry_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy value: 0x%04" PRIx16 " 0x%04" PRIx16 " to a filetime value.",
			 function,
			 value_identifier.entry_type,
			 value_identifier.value_type );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the size value of a specific entry
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_size(
     libnk2_item_t *item,
     uint32_t entry_type,
     size_t *entry_value,
     libcerror_error_t **error )
{
	libnk2_value_identifier_t value_identifier;

	libfvalue_value_t *value                           = NULL;
	libnk2_internal_item_t *internal_item              = NULL;
	libnk2_value_identifier_t *stored_value_identifier = NULL;
	static char *function                              = "libnk2_item_get_entry_value_size";
	size_t stored_value_identifier_size                = 0;
	int result                                         = 0;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	value_identifier.entry_type = (uint16_t) entry_type;
	value_identifier.value_type = 0;

	result = libfvalue_table_get_value_by_identifier(
	          internal_item->values_table,
	          (uint8_t *) &value_identifier,
	          sizeof( libnk2_value_identifier_t ),
	          &value,
	          LIBFVALUE_TABLE_FLAG_ALLOW_PARTIAL_MATCH,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value: 0x%04" PRIx16 " 0x%04" PRIx16 " from values table.",
		 function,
		 value_identifier.entry_type,
		 value_identifier.value_type );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libfvalue_value_get_identifier(
		     value,
		     (uint8_t **) &stored_value_identifier,
		     &stored_value_identifier_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value identifier.",
			 function );

			return( -1 );
		}
		if( stored_value_identifier == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing value identifier.",
			 function );

			return( -1 );
		}
		if( ( stored_value_identifier->value_type != LIBNK2_VALUE_TYPE_INTEGER_32BIT_SIGNED )
		 && ( stored_value_identifier->value_type != LIBNK2_VALUE_TYPE_INTEGER_64BIT_SIGNED ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported string value type: 0x%04" PRIx16 ".",
			 function,
			 stored_value_identifier->value_type );

			return( -1 );
		}
#if ( SIZEOF_SIZE_T == 8 ) || defined( _WIN64 )
		result = libfvalue_value_copy_to_64bit(
		          value,
		          0,
		          (uint64_t *) entry_value,
		          error );
#else
		result = libfvalue_value_copy_to_32bit(
		          value,
		          0,
		          (uint32_t *) entry_value,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy value: 0x%04" PRIx16 " 0x%04" PRIx16 " to a size value.",
			 function,
			 value_identifier.entry_type,
			 stored_value_identifier->value_type );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the floating point value of a specific entry
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_floating_point(
     libnk2_item_t *item,
     uint32_t entry_type,
     double *entry_value,
     libcerror_error_t **error )
{
	libnk2_value_identifier_t value_identifier;

	libfvalue_value_t *value                           = NULL;
	libnk2_internal_item_t *internal_item              = NULL;
	libnk2_value_identifier_t *stored_value_identifier = NULL;
	static char *function                              = "libnk2_item_get_entry_value_floating_point";
	size_t stored_value_identifier_size                = 0;
	int result                                         = 0;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	value_identifier.entry_type = (uint16_t) entry_type;
	value_identifier.value_type = 0;

	result = libfvalue_table_get_value_by_identifier(
	          internal_item->values_table,
	          (uint8_t *) &value_identifier,
	          sizeof( libnk2_value_identifier_t ),
	          &value,
	          LIBFVALUE_TABLE_FLAG_ALLOW_PARTIAL_MATCH,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value: 0x%04" PRIx16 " 0x%04" PRIx16 " from values table.",
		 function,
		 value_identifier.entry_type,
		 value_identifier.value_type );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libfvalue_value_get_identifier(
		     value,
		     (uint8_t **) &stored_value_identifier,
		     &stored_value_identifier_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value identifier.",
			 function );

			return( -1 );
		}
		if( stored_value_identifier == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing value identifier.",
			 function );

			return( -1 );
		}
		if( ( stored_value_identifier->value_type != LIBNK2_VALUE_TYPE_FLOAT_32BIT )
		 && ( stored_value_identifier->value_type != LIBNK2_VALUE_TYPE_DOUBLE_64BIT ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported string value type: 0x%04" PRIx16 ".",
			 function,
			 stored_value_identifier->value_type );

			return( -1 );
		}
		if( libfvalue_value_copy_to_double(
		     value,
		     0,
		     entry_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy value: 0x%04" PRIx16 " 0x%04" PRIx16 " to a double value.",
			 function,
			 stored_value_identifier->entry_type,
			 stored_value_identifier->value_type );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the size of the UTF-8 encoded string of a specific entry
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_utf8_string_size(
     libnk2_item_t *item,
     uint32_t entry_type,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libnk2_value_identifier_t value_identifier;

	libfvalue_value_t *value                           = NULL;
	libnk2_internal_item_t *internal_item              = NULL;
	libnk2_value_identifier_t *stored_value_identifier = NULL;
	static char *function                              = "libnk2_item_get_entry_value_utf8_string_size";
	size_t stored_value_identifier_size                = 0;
	int result                                         = 0;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing IO handle.",
		 function );

		return( -1 );
	}
	value_identifier.entry_type = (uint16_t) entry_type;
	value_identifier.value_type = 0;

	result = libfvalue_table_get_value_by_identifier(
	          internal_item->values_table,
	          (uint8_t *) &value_identifier,
	          sizeof( libnk2_value_identifier_t ),
	          &value,
	          LIBFVALUE_TABLE_FLAG_ALLOW_PARTIAL_MATCH,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value: 0x%04" PRIx16 " 0x%04" PRIx16 " from values table.",
		 function,
		 value_identifier.entry_type,
		 value_identifier.value_type );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libfvalue_value_get_identifier(
		     value,
		     (uint8_t **) &stored_value_identifier,
		     &stored_value_identifier_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value identifier.",
			 function );

			return( -1 );
		}
		if( stored_value_identifier == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing value identifier.",
			 function );

			return( -1 );
		}
		if( ( stored_value_identifier->value_type != LIBNK2_VALUE_TYPE_STRING_ASCII )
		 && ( stored_value_identifier->value_type != LIBNK2_VALUE_TYPE_STRING_UNICODE ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported string value type: 0x%04" PRIx16 ".",
			 function,
			 stored_value_identifier->value_type );

			return( -1 );
		}
		if( libfvalue_value_get_utf8_string_size(
		     value,
		     0,
		     utf8_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value: 0x%04" PRIx16 " 0x%04" PRIx16 " UTF-8 string size.",
			 function,
			 value_identifier.entry_type,
			 stored_value_identifier->value_type );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the UTF-8 encoded string of a specific entry
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The size should include the end of string character
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_utf8_string(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libnk2_value_identifier_t value_identifier;

	libfvalue_value_t *value                           = NULL;
	libnk2_internal_item_t *internal_item              = NULL;
	libnk2_value_identifier_t *stored_value_identifier = NULL;
	static char *function                              = "libnk2_item_get_entry_value_utf8_string";
	size_t stored_value_identifier_size                = 0;
	int result                                         = 0;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing IO handle.",
		 function );

		return( -1 );
	}
	value_identifier.entry_type = (uint16_t) entry_type;
	value_identifier.value_type = 0;

	result = libfvalue_table_get_value_by_identifier(
	          internal_item->values_table,
	          (uint8_t *) &value_identifier,
	          sizeof( libnk2_value_identifier_t ),
	          &value,
	          LIBFVALUE_TABLE_FLAG_ALLOW_PARTIAL_MATCH,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value: 0x%04" PRIx16 " 0x%04" PRIx16 " from values table.",
		 function,
		 value_identifier.entry_type,
		 value_identifier.value_type );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libfvalue_value_get_identifier(
		     value,
		     (uint8_t **) &stored_value_identifier,
		     &stored_value_identifier_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value identifier.",
			 function );

			return( -1 );
		}
		if( stored_value_identifier == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing value identifier.",
			 function );

			return( -1 );
		}
		if( ( stored_value_identifier->value_type != LIBNK2_VALUE_TYPE_STRING_ASCII )
		 && ( stored_value_identifier->value_type != LIBNK2_VALUE_TYPE_STRING_UNICODE ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported string value type: 0x%04" PRIx16 ".",
			 function,
			 stored_value_identifier->value_type );

			return( -1 );
		}
		if( libfvalue_value_copy_to_utf8_string(
		     value,
		     0,
		     utf8_string,
		     utf8_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy value: 0x%04" PRIx16 " 0x%04" PRIx16 " to an UTF-8 string.",
			 function,
			 value_identifier.entry_type,
			 stored_value_identifier->value_type );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the size of the UTF-16 encoded string of a specific entry
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_utf16_string_size(
     libnk2_item_t *item,
     uint32_t entry_type,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libnk2_value_identifier_t value_identifier;

	libfvalue_value_t *value                           = NULL;
	libnk2_internal_item_t *internal_item              = NULL;
	libnk2_value_identifier_t *stored_value_identifier = NULL;
	static char *function                              = "libnk2_item_get_entry_value_utf16_string_size";
	size_t stored_value_identifier_size                = 0;
	int result                                         = 0;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing IO handle.",
		 function );

		return( -1 );
	}
	value_identifier.entry_type = (uint16_t) entry_type;
	value_identifier.value_type = 0;

	result = libfvalue_table_get_value_by_identifier(
	          internal_item->values_table,
	          (uint8_t *) &value_identifier,
	          sizeof( libnk2_value_identifier_t ),
	          &value,
	          LIBFVALUE_TABLE_FLAG_ALLOW_PARTIAL_MATCH,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value: 0x%04" PRIx16 " 0x%04" PRIx16 " from values table.",
		 function,
		 value_identifier.entry_type,
		 value_identifier.value_type );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libfvalue_value_get_identifier(
		     value,
		     (uint8_t **) &stored_value_identifier,
		     &stored_value_identifier_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value identifier.",
			 function );

			return( -1 );
		}
		if( stored_value_identifier == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing value identifier.",
			 function );

			return( -1 );
		}
		if( ( stored_value_identifier->value_type != LIBNK2_VALUE_TYPE_STRING_ASCII )
		 && ( stored_value_identifier->value_type != LIBNK2_VALUE_TYPE_STRING_UNICODE ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported string value type: 0x%04" PRIx16 ".",
			 function,
			 stored_value_identifier->value_type );

			return( -1 );
		}
		if( libfvalue_value_get_utf16_string_size(
		     value,
		     0,
		     utf16_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value: 0x%04" PRIx16 " 0x%04" PRIx16 " UTF-16 string size.",
			 function,
			 value_identifier.entry_type,
			 stored_value_identifier->value_type );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the UTF-16 encoded string of a specific entry
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The size should include the end of string character
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_utf16_string(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libnk2_value_identifier_t value_identifier;

	libfvalue_value_t *value                           = NULL;
	libnk2_internal_item_t *internal_item              = NULL;
	libnk2_value_identifier_t *stored_value_identifier = NULL;
	static char *function                              = "libnk2_item_get_entry_value_utf16_string";
	size_t stored_value_identifier_size                = 0;
	int result                                         = 0;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing IO handle.",
		 function );

		return( -1 );
	}
	value_identifier.entry_type = (uint16_t) entry_type;
	value_identifier.value_type = 0;

	result = libfvalue_table_get_value_by_identifier(
	          internal_item->values_table,
	          (uint8_t *) &value_identifier,
	          sizeof( libnk2_value_identifier_t ),
	          &value,
	          LIBFVALUE_TABLE_FLAG_ALLOW_PARTIAL_MATCH,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value: 0x%04" PRIx16 " 0x%04" PRIx16 " from values table.",
		 function,
		 value_identifier.entry_type,
		 value_identifier.value_type );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libfvalue_value_get_identifier(
		     value,
		     (uint8_t **) &stored_value_identifier,
		     &stored_value_identifier_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value identifier.",
			 function );

			return( -1 );
		}
		if( stored_value_identifier == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing value identifier.",
			 function );

			return( -1 );
		}
		if( ( stored_value_identifier->value_type != LIBNK2_VALUE_TYPE_STRING_ASCII )
		 && ( stored_value_identifier->value_type != LIBNK2_VALUE_TYPE_STRING_UNICODE ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported string value type: 0x%04" PRIx16 ".",
			 function,
			 stored_value_identifier->value_type );

			return( -1 );
		}
		if( libfvalue_value_copy_to_utf16_string(
		     value,
		     0,
		     utf16_string,
		     utf16_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy value: 0x%04" PRIx16 " 0x%04" PRIx16 " to an UTF-16 string.",
			 function,
			 value_identifier.entry_type,
			 stored_value_identifier->value_type );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the binary data size of a specific entry
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_binary_data_size(
     libnk2_item_t *item,
     uint32_t entry_type,
     size_t *size,
     libcerror_error_t **error )
{
	libnk2_value_identifier_t value_identifier;

	libfvalue_value_t *value              = NULL;
	libnk2_internal_item_t *internal_item = NULL;
	uint8_t *value_data                   = NULL;
	static char *function                 = "libnk2_item_get_entry_value_binary_data_size";
	int encoding                          = 0;
	int result                            = 0;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	value_identifier.entry_type = (uint16_t) entry_type;
	value_identifier.value_type = LIBNK2_VALUE_TYPE_BINARY_DATA;

	result = libfvalue_table_get_value_by_identifier(
	          internal_item->values_table,
	          (uint8_t *) &value_identifier,
	          sizeof( libnk2_value_identifier_t ),
	          &value,
	          0,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value: 0x%04" PRIx16 " 0x%04" PRIx16 " from values table.",
		 function,
		 value_identifier.entry_type,
		 value_identifier.value_type );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libfvalue_value_get_data(
		     value,
		     &value_data,
		     size,
		     &encoding,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value: 0x%04" PRIx16 " 0x%04" PRIx16 " binary data size.",
			 function,
			 value_identifier.entry_type,
			 value_identifier.value_type );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the binary data value of a specific entry
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_binary_data(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint8_t *binary_data,
     size_t size,
     libcerror_error_t **error )
{
	libnk2_value_identifier_t value_identifier;

	libfvalue_value_t *value              = NULL;
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_get_entry_value_binary_data";
	int result                            = 0;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	value_identifier.entry_type = (uint16_t) entry_type;
	value_identifier.value_type = LIBNK2_VALUE_TYPE_BINARY_DATA;

	result = libfvalue_table_get_value_by_identifier(
	          internal_item->values_table,
	          (uint8_t *) &value_identifier,
	          sizeof( libnk2_value_identifier_t ),
	          &value,
	          0,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value: 0x%04" PRIx16 " 0x%04" PRIx16 " from values table.",
		 function,
		 value_identifier.entry_type,
		 value_identifier.value_type );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libfvalue_value_copy_data(
		     value,
		     binary_data,
		     size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy value: 0x%04" PRIx16 " 0x%04" PRIx16 " to binary data.",
			 function,
			 value_identifier.entry_type,
			 value_identifier.value_type );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the GUID value of a specific entry
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_guid(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error )
{
	libnk2_value_identifier_t value_identifier;

	libfvalue_value_t *value              = NULL;
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_get_entry_value_guid";
	int result                            = 0;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	value_identifier.entry_type = (uint16_t) entry_type;
	value_identifier.value_type = LIBNK2_VALUE_TYPE_GUID;

	result = libfvalue_table_get_value_by_identifier(
	          internal_item->values_table,
	          (uint8_t *) &value_identifier,
	          sizeof( libnk2_value_identifier_t ),
	          &value,
	          0,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value: 0x%04" PRIx16 " 0x%04" PRIx16 " from values table.",
		 function,
		 value_identifier.entry_type,
		 value_identifier.value_type );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libfvalue_value_copy_data(
		     value,
		     guid,
		     size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy value: 0x%04" PRIx16 " 0x%04" PRIx16 " to GUID.",
			 function,
			 value_identifier.entry_type,
			 value_identifier.value_type );

			return( -1 );
		}
	}
	return( result );
}


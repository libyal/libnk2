/*
 * Item functions
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
#include <memory.h>
#include <types.h>

#include <liberror.h>

#include "libnk2_definitions.h"
#include "libnk2_item.h"
#include "libnk2_item_values.h"
#include "libnk2_libfmapi.h"
#include "libnk2_mapi.h"
#include "libnk2_value_type.h"

/* Initializes the item and its values
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_initialize(
     libnk2_item_t **item,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_initialize";

	if( item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	if( *item == NULL )
	{
		internal_item = (libnk2_internal_item_t *) memory_allocate(
		                                            sizeof( libnk2_internal_item_t ) );

		if( internal_item == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create internal item.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     internal_item,
		     0,
		     sizeof( libnk2_internal_item_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear internal item.",
			 function );

			memory_free(
			 internal_item );

			return( -1 );
		}
		*item = (libnk2_item_t *) internal_item;
	}
	return( 1 );
}

/* Frees an item
 * Detaches the reference from the file if necessary
 * Return 1 if successful or -1 on error
 */
int libnk2_item_free(
     libnk2_item_t **item,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_free";

	if( item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	if( *item != NULL )
	{
		internal_item = (libnk2_internal_item_t *) *item;
		*item         = NULL;

		/* The internal_file and item_values references
		 * are freed elsewhere
		 */
		if( libnk2_item_detach(
		     internal_item,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_REMOVE_FAILED,
			 "%s: unable to detach internal item.",
			 function );

			return( -1 );
		}
		memory_free(
		 internal_item );
	}
	return( 1 );
}

/* Attaches the item to the file
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_attach(
     libnk2_internal_item_t *internal_item,
     libbfio_handle_t *file_io_handle,
     libnk2_internal_file_t *internal_file,
     libnk2_item_values_t *item_values,
     uint8_t flags,
     liberror_error_t **error )
{
	static char *function = "libnk2_item_attach";

	if( internal_item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal item.",
		 function );

		return( -1 );
	}
	if( internal_item->internal_file != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid internal item - already attached to file.",
		 function );

		return( -1 );
	}
	if( ( flags & ~( LIBNK2_ITEM_FLAG_MANAGED_FILE_IO_HANDLE ) ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags: 0x%02" PRIx8 ".",
		 function,
		 flags );

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
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy file io handle.",
			 function );

			return( -1 );
		}
		if( libbfio_handle_set_open_on_demand(
		     internal_item->file_io_handle,
		     1,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to set open on demand in file io handle.",
			 function );

			return( -1 );
		}
	}
	internal_item->internal_file = internal_file;
	internal_item->flags         = flags;
	internal_item->item_values   = item_values;

	return( 1 );
}

/* Detaches the item from its file reference
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_detach(
     libnk2_internal_item_t *internal_item,
     liberror_error_t **error )
{
	static char *function = "libnk2_item_detach";

	if( internal_item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal item.",
		 function );

		return( -1 );
	}
	if( ( internal_item->flags & LIBNK2_ITEM_FLAG_MANAGED_FILE_IO_HANDLE ) != 0 )
	{
		if( internal_item->file_io_handle != NULL )
		{
			if( libbfio_handle_close(
			     internal_item->file_io_handle,
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
			if( libbfio_handle_free(
			     &( internal_item->file_io_handle ),
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free file io handle.",
				 function );

				return( -1 );
			}
		}
	}
	internal_item->internal_file = NULL;
	internal_item->flags         = 0;
	internal_item->item_values   = NULL;

	return( 1 );
}

/* Retrieves the amount of entries of the referenced item
 * All sets in an item contain the same amount of entries
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_get_amount_of_entries(
     libnk2_item_t *item,
     uint32_t *amount_of_entries,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_get_amount_of_entries";

	if( item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	if( libnk2_item_values_get_amount_of_entries(
	     internal_item->item_values,
	     amount_of_entries,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to get amount of entries.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the entry and value type of a specific entry from the referenced item
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_get_entry_type(
     libnk2_item_t *item,
     int entry_index,
     uint32_t *entry_type,
     uint32_t *value_type,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_get_entry_type";

	if( item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	if( libnk2_item_values_get_entry_type(
	     internal_item->item_values,
	     entry_index,
	     entry_type,
	     value_type,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to get entry type.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the value of a specific entry from the referenced item
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
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	static char *function                 = "libnk2_item_get_entry_value";
	int result                            = 0;

	if( item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	result = libnk2_item_values_get_entry_value(
	          internal_item->item_values,
	          entry_type,
	          value_type,
	          value_data, 
	          value_data_size,
	          flags,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry value.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Retrieves the boolean value of a specific entry from the referenced item
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_boolean(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint8_t *entry_value,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	uint8_t *value_data                   = NULL;
	static char *function                 = "libnk2_item_get_entry_value_boolean";
	size_t value_data_size                = 0;
	uint32_t value_type                   = LIBNK2_VALUE_TYPE_BOOLEAN;
	int result                            = 0;

	if( item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	result = libnk2_item_values_get_entry_value(
	          internal_item->item_values,
	          entry_type,
	          &value_type,
	          &value_data,
	          &value_data_size,
	          0,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry value.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		if( libnk2_value_type_copy_to_boolean(
		     value_data,
		     value_data_size,
		     entry_value,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to set boolean entry value.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the 32-bit value of a specific entry from the referenced item
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_32bit(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint32_t *entry_value,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	uint8_t *value_data                   = NULL;
	static char *function                 = "libnk2_item_get_entry_value_32bit";
	size_t value_data_size                = 0;
	uint32_t value_type                   = LIBNK2_VALUE_TYPE_INTEGER_32BIT_SIGNED;
	int result                            = 0;

	if( item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	result = libnk2_item_values_get_entry_value(
	          internal_item->item_values,
	          entry_type,
	          &value_type,
	          &value_data,
	          &value_data_size,
	          0,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry value.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		if( libnk2_value_type_copy_to_32bit(
		     value_data,
		     value_data_size,
		     entry_value,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to set 32-bit entry value.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the 64-bit value of a specific entry from the referenced item
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_64bit(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint64_t *entry_value,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	uint8_t *value_data                   = NULL;
	static char *function                 = "libnk2_item_get_entry_value_64bit";
	size_t value_data_size                = 0;
	uint32_t value_type                   = LIBNK2_VALUE_TYPE_INTEGER_64BIT_SIGNED;
	int result                            = 0;

	if( item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	result = libnk2_item_values_get_entry_value(
	          internal_item->item_values,
	          entry_type,
	          &value_type,
	          &value_data,
	          &value_data_size,
	          0,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry value.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		if( libnk2_value_type_copy_to_64bit(
		     value_data,
		     value_data_size,
		     entry_value,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to set 64-bit entry value.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the 64-bit filetime value of a specific entry from the referenced item
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_filetime(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint64_t *entry_value,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	uint8_t *value_data                   = NULL;
	static char *function                 = "libnk2_item_get_entry_value_filetime";
	size_t value_data_size                = 0;
	uint32_t value_type                   = LIBNK2_VALUE_TYPE_FILETIME;
	int result                            = 0;

	if( item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	result = libnk2_item_values_get_entry_value(
	          internal_item->item_values,
	          entry_type,
	          &value_type,
	          &value_data,
	          &value_data_size,
	          0,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry value.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		if( libnk2_value_type_copy_to_64bit(
		     value_data,
		     value_data_size,
		     entry_value,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to set filetime entry value.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the size value of a specific entry from the referenced item
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_size(
     libnk2_item_t *item,
     uint32_t entry_type,
     size_t *entry_value,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	uint8_t *value_data                   = NULL;
	static char *function                 = "libnk2_item_get_entry_value_size";
	size_t value_data_size                = 0;
	uint32_t value_type                   = 0;
	int result                            = 0;

	if( item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	result = libnk2_item_values_get_entry_value(
	          internal_item->item_values,
	          entry_type,
	          &value_type,
	          &value_data,
	          &value_data_size,
	          LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry value.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		if( libnk2_value_type_copy_to_size(
		     value_data,
		     value_data_size,
		     entry_value,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to set size entry value.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the UTF-8 string size of a specific entry from the referenced item
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_utf8_string_size(
     libnk2_item_t *item,
     uint32_t entry_type,
     size_t *utf8_string_size,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	uint8_t *value_data                   = NULL;
	static char *function                 = "libnk2_item_get_entry_value_utf8_string_size";
	size_t value_data_size                = 0;
	uint32_t value_type                   = 0;
	uint8_t is_ascii_string               = 0;
	int result                            = 0;

	if( item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	result = libnk2_item_values_get_entry_value(
	          internal_item->item_values,
	          entry_type,
	          &value_type,
	          &value_data,
	          &value_data_size,
	          LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry value.",
		 function );
	}
	else if( result == 1 )
	{
		if( ( value_type != LIBNK2_VALUE_TYPE_STRING_ASCII )
		 && ( value_type != LIBNK2_VALUE_TYPE_STRING_UNICODE ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported string value type: 0x%04" PRIx32 ".",
			 function,
			 value_type );

			return( -1 );
		}
		if( value_type == LIBNK2_VALUE_TYPE_STRING_ASCII )
		{
			is_ascii_string = 1;
		}
		if( libnk2_value_type_get_utf8_string_size(
		     value_data,
		     value_data_size,
		     is_ascii_string,
		     internal_item->internal_file->ascii_codepage,
		     utf8_string_size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to set UTF-8 string size entry value.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the UTF-8 string value of a specific entry from the referenced item
 * The string is formatted in UTF-8
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The size should include the end of string character
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_utf8_string(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	uint8_t *value_data                   = NULL;
	static char *function                 = "libnk2_item_get_entry_value_utf8_string";
	size_t value_data_size                = 0;
	uint32_t value_type                   = 0;
	uint8_t is_ascii_string               = 0;
	int result                            = 0;

	if( item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	result = libnk2_item_values_get_entry_value(
	          internal_item->item_values,
	          entry_type,
	          &value_type,
	          &value_data,
	          &value_data_size,
	          LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry value.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		if( ( value_type != LIBNK2_VALUE_TYPE_STRING_ASCII )
		 && ( value_type != LIBNK2_VALUE_TYPE_STRING_UNICODE ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported string value type: 0x%04" PRIx32 ".",
			 function,
			 value_type );

			return( -1 );
		}
		if( value_type == LIBNK2_VALUE_TYPE_STRING_ASCII )
		{
			is_ascii_string = 1;
		}
		if( libnk2_value_type_copy_to_utf8_string(
		     value_data,
		     value_data_size,
		     is_ascii_string,
		     internal_item->internal_file->ascii_codepage,
		     utf8_string,
		     utf8_string_size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to set UTF-8 string entry value.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the UTF-16 string size of a specific entry from the referenced item
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_utf16_string_size(
     libnk2_item_t *item,
     uint32_t entry_type,
     size_t *utf16_string_size,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	uint8_t *value_data                   = NULL;
	static char *function                 = "libnk2_item_get_entry_value_utf16_string_size";
	size_t value_data_size                = 0;
	uint32_t value_type                   = 0;
	uint8_t is_ascii_string               = 0;
	int result                            = 0;

	if( item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	result = libnk2_item_values_get_entry_value(
	          internal_item->item_values,
	          entry_type,
	          &value_type,
	          &value_data,
	          &value_data_size,
	          LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry value.",
		 function );
	}
	else if( result == 1 )
	{
		if( ( value_type != LIBNK2_VALUE_TYPE_STRING_ASCII )
		 && ( value_type != LIBNK2_VALUE_TYPE_STRING_UNICODE ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported string value type: 0x%04" PRIx32 ".",
			 function,
			 value_type );

			return( -1 );
		}
		if( value_type == LIBNK2_VALUE_TYPE_STRING_ASCII )
		{
			is_ascii_string = 1;
		}
		if( libnk2_value_type_get_utf16_string_size(
		     value_data,
		     value_data_size,
		     is_ascii_string,
		     internal_item->internal_file->ascii_codepage,
		     utf16_string_size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to set UTF-16 string size entry value.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the UTF-16 string value of a specific entry from the referenced item
 * The string is formatted in UTF-16
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The size should include the end of string character
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_utf16_string(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	uint8_t *value_data                   = NULL;
	static char *function                 = "libnk2_item_get_entry_value_utf16_string";
	size_t value_data_size                = 0;
	uint32_t value_type                   = 0;
	uint8_t is_ascii_string               = 0;
	int result                            = 0;

	if( item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	result = libnk2_item_values_get_entry_value(
	          internal_item->item_values,
	          entry_type,
	          &value_type,
	          &value_data,
	          &value_data_size,
	          LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry value.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		if( ( value_type != LIBNK2_VALUE_TYPE_STRING_ASCII )
		 && ( value_type != LIBNK2_VALUE_TYPE_STRING_UNICODE ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported string value type: 0x%04" PRIx32 ".",
			 function,
			 value_type );

			return( -1 );
		}
		if( value_type == LIBNK2_VALUE_TYPE_STRING_ASCII )
		{
			is_ascii_string = 1;
		}
		if( libnk2_value_type_copy_to_utf16_string(
		     value_data,
		     value_data_size,
		     is_ascii_string,
		     internal_item->internal_file->ascii_codepage,
		     utf16_string,
		     utf16_string_size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to set UTF-16 string entry value.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the binary data size of a specific entry from the referenced item
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_binary_data_size(
     libnk2_item_t *item,
     uint32_t entry_type,
     size_t *size,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	uint8_t *value_data                   = NULL;
	static char *function                 = "libnk2_item_get_entry_value_binary_data_size";
	size_t value_data_size                = 0;
	uint32_t value_type                   = LIBNK2_VALUE_TYPE_BINARY_DATA;
	int result                            = 0;

	if( item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	result = libnk2_item_values_get_entry_value(
	          internal_item->item_values,
	          entry_type,
	          &value_type,
	          &value_data,
	          &value_data_size,
	          0,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry value.",
		 function );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libnk2_value_type_get_binary_data_size(
		     value_data,
		     value_data_size,
		     size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to set binary data size.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the binary data value of a specific entry from the referenced item
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_binary_data(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint8_t *binary_data,
     size_t size,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	uint8_t *value_data                   = NULL;
	static char *function                 = "libnk2_item_get_entry_value_binary_data";
	size_t value_data_size                = 0;
	uint32_t value_type                   = LIBNK2_VALUE_TYPE_BINARY_DATA;
	int result                            = 0;

	if( item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	result = libnk2_item_values_get_entry_value(
	          internal_item->item_values,
	          entry_type,
	          &value_type,
	          &value_data,
	          &value_data_size,
	          0,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry value.",
		 function );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libnk2_value_type_copy_to_binary_data(
		     value_data,
		     value_data_size,
		     binary_data,
		     size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to set binary data.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves the GUID value of a specific entry from the referenced item
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_get_entry_value_guid(
     libnk2_item_t *item,
     uint32_t entry_type,
     uint8_t *guid,
     size_t size,
     liberror_error_t **error )
{
	libnk2_internal_item_t *internal_item = NULL;
	uint8_t *value_data                   = NULL;
	static char *function                 = "libnk2_item_get_entry_value_guid";
	size_t value_data_size                = 0;
	uint32_t value_type                   = LIBNK2_VALUE_TYPE_GUID;
	int result                            = 0;

	if( item == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libnk2_internal_item_t *) item;

	if( internal_item->internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing internal file.",
		 function );

		return( -1 );
	}
	result = libnk2_item_values_get_entry_value(
	          internal_item->item_values,
	          entry_type,
	          &value_type,
	          &value_data,
	          &value_data_size,
	          0,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry value.",
		 function );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libnk2_value_type_copy_to_binary_data(
		     value_data,
		     value_data_size,
		     guid,
		     size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to set GUID.",
			 function );

			return( -1 );
		}
	}
	return( result );
}


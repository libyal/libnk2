/*
 * Item values functions
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
#include <libfmapi.h>

#include "libnk2_definitions.h"
#include "libnk2_item_values.h"

/* Frees item values
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_values_free(
     libnk2_item_values_t *item_values,
     liberror_error_t **error )
{
	static char *function = "libnk2_item_values_free";

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
	if( item_values->entry != NULL )
	{
		memory_free(
		 item_values->entry );
	}
	memory_free(
	 item_values );

	return( 1 );
}

/* Creates the item values entries
 * Returns 1 if successful or -1 on error
 */
int libnk2_item_values_entries_allocate(
     libnk2_item_values_t *item_values,
     int amount_of_entries,
     liberror_error_t **error )
{
	static char *function = "libnk2_item_values_entries_allocate";
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
	if( item_values->entry != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid item values - entries already set.",
		 function );

		return( -1 );
	}
	if( amount_of_entries <= 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid amount of entries value zero or less.",
		 function );

		return( -1 );
	}
	entries_size = sizeof( libnk2_item_entry_t * ) * amount_of_entries;

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
	item_values->entry = (libnk2_item_entry_t **) memory_allocate(
	                                               entries_size );

	if( item_values->entry == NULL )
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
	     item_values->entry,
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
	item_values->amount_of_entries = (uint32_t) amount_of_entries;

	return( 1 );
}

/* Retrieves the value of a specific entry from the referenced item values
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_values_get_entry_value(
     libnk2_item_values_t *item_values,
     libnk2_io_handle_t *io_handle,
     uint32_t entry_type,
     uint32_t *value_type,
     uint8_t **value_data, 
     size_t *value_data_size,
     liberror_error_t **error )
{
	static char *function = "libnk2_item_values_get_entry_value";
	int result            = 0;

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
	if( item_values->entry != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid entry value data.",
		 "%s: invalid item values - missing entries.",
		 function );

		return( -1 );
	}
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

	/* TODO */
	return( result );
}

/* Retrieves the boolean value of a specific entry from the referenced item
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_values_get_entry_value_boolean(
     libnk2_item_values_t *item_values,
     libnk2_io_handle_t *io_handle,
     uint32_t entry_type,
     uint8_t *entry_value,
     liberror_error_t **error )
{
	uint8_t *value_data    = NULL;
	static char *function  = "libnk2_item_values_get_entry_value_boolean";
	uint32_t value_type    = 0;
	size_t value_data_size = 0;
	int result             = 0;

	if( entry_value == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry value.",
		 function );

		return( -1 );
	}
	result = libnk2_item_values_get_entry_value(
	          item_values,
	          io_handle,
	          entry_type,
	          &value_type,
	          &value_data,
	          &value_data_size,
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
		if( value_data == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid entry value data.",
			 function );

			return( -1 );
		}
		if( value_type != LIBNK2_VALUE_TYPE_BOOLEAN )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupport boolean value type: 0x%04" PRIx32 ".",
			 function,
			 value_type );

			return( -1 );
		}
		/* The value data size of a boolean value is 1
		 */
		if( value_data_size != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid entry value data size.",
			 function );

			return( -1 );
		}
		*entry_value = *value_data;
	}
	return( result );
}

/* Retrieves the 32-bit value of a specific entry from the referenced item
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_values_get_entry_value_32bit(
     libnk2_item_values_t *item_values,
     libnk2_io_handle_t *io_handle,
     uint32_t entry_type,
     uint32_t *entry_value,
     liberror_error_t **error )
{
	uint8_t *value_data    = NULL;
	static char *function  = "libnk2_item_values_get_entry_value_32bit";
	uint32_t value_type    = 0;
	size_t value_data_size = 0;
	int result             = 0;

	if( entry_value == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry value.",
		 function );

		return( -1 );
	}
	result = libnk2_item_values_get_entry_value(
	          item_values,
	          io_handle,
	          entry_type,
	          &value_type,
	          &value_data,
	          &value_data_size,
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
		if( value_data == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid entry value data.",
			 function );

			return( -1 );
		}
		if( value_type != LIBNK2_VALUE_TYPE_INTEGER_32BIT_SIGNED )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupport 32-bit value type: 0x%04" PRIx32 ".",
			 function,
			 value_type );

			return( -1 );
		}
		/* The value data size of a 32-bit value is 4
		 */
		if( value_data_size != 4 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid entry value data size.",
			 function );

			return( -1 );
		}
		endian_little_convert_32bit(
		 *entry_value,
		 value_data );
	}
	return( result );
}

/* Retrieves the 64-bit value of a specific entry from the referenced item
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_values_get_entry_value_64bit(
     libnk2_item_values_t *item_values,
     libnk2_io_handle_t *io_handle,
     uint32_t entry_type,
     uint64_t *entry_value,
     liberror_error_t **error )
{
	uint8_t *value_data    = NULL;
	static char *function  = "libnk2_item_values_get_entry_value_64bit";
	uint32_t value_type    = 0;
	size_t value_data_size = 0;
	int result             = 0;

	if( entry_value == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry value.",
		 function );

		return( -1 );
	}
	result = libnk2_item_values_get_entry_value(
	          item_values,
	          io_handle,
	          entry_type,
	          &value_type,
	          &value_data,
	          &value_data_size,
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
		if( value_data == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid entry value data.",
			 function );

			return( -1 );
		}
		if( ( value_type != LIBNK2_VALUE_TYPE_INTEGER_64BIT_SIGNED )
		 && ( value_type != LIBNK2_VALUE_TYPE_FILETIME ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupport 64-bit value type: 0x%04" PRIx32 ".",
			 function,
			 value_type );

			return( -1 );
		}
		/* The value data size of a 64-bit value is 8
		 */
		if( value_data_size != 8 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid entry value data size.",
			 function );

			return( -1 );
		}
		endian_little_convert_64bit(
		 *entry_value,
		 value_data );
	}
	return( result );
}

/* Retrieves the size value of a specific entry from the referenced item
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_values_get_entry_value_size(
     libnk2_item_values_t *item_values,
     libnk2_io_handle_t *io_handle,
     uint32_t entry_type,
     size_t *entry_value,
     liberror_error_t **error )
{
	uint8_t *value_data    = NULL;
	static char *function  = "libnk2_item_values_get_entry_value_size";
	uint32_t value_type    = 0;
	size_t value_data_size = 0;
	int result             = 0;

	if( entry_value == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry value.",
		 function );

		return( -1 );
	}
	result = libnk2_item_values_get_entry_value(
	          item_values,
	          io_handle,
	          entry_type,
	          &value_type,
	          &value_data,
	          &value_data_size,
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
		if( value_data == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid entry value data.",
			 function );

			return( -1 );
		}
		if( ( value_type != LIBNK2_VALUE_TYPE_INTEGER_32BIT_SIGNED )
		 && ( value_type != LIBNK2_VALUE_TYPE_INTEGER_64BIT_SIGNED ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupport size value type: 0x%04" PRIx32 ".",
			 function,
			 value_type );

			return( -1 );
		}
		/* The value data size of a size value is 4 or 8
		 */
		if( ( value_data_size != 4 )
		 && ( value_data_size != 8 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid entry value data size.",
			 function );

			return( -1 );
		}
		if( value_data_size == 4 )
		{
			endian_little_convert_32bit(
			 *entry_value,
			 value_data );
		}
		else if( value_data_size == 8 )
		{
			endian_little_convert_64bit(
			 *entry_value,
			 value_data );
		}
	}
	return( result );
}

/* Retrieves the string size of a specific entry from the referenced item
 * Length includes the end of string character
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_values_get_entry_value_string_size(
     libnk2_item_values_t *item_values,
     libnk2_io_handle_t *io_handle,
     uint32_t entry_type,
     size_t *size,
     int ascii_codepage,
     liberror_error_t **error )
{
	uint8_t *value_data    = NULL;
	static char *function  = "libnk2_item_values_get_entry_value_string_size";
	size_t value_data_size = 0;
	uint32_t value_type    = 0;
	int result             = 0;

	if( size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
	result = libnk2_item_values_get_entry_value(
	          item_values,
	          io_handle,
	          entry_type,
	          &value_type,
	          &value_data,
	          &value_data_size,
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
			 "%s: unsupport string value type: 0x%04" PRIx32 ".",
			 function,
			 value_type );

			return( -1 );
		}
		/* Internally an empty string is represented by a NULL reference
		 */
		if( value_data == NULL )
		{
			*size = 0;
		}
		else
		{
			if( ( value_type == LIBNK2_VALUE_TYPE_STRING_ASCII )
			 && ( libuna_utf8_string_size_from_byte_stream(
			       value_data,
			       value_data_size,
			       ascii_codepage,
			       size,
			       error ) != 1 ) )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to determine string size.",
				 function );

				return( -1 );
			}
			else if( ( value_type == LIBNK2_VALUE_TYPE_STRING_UNICODE )
			      && ( libuna_utf8_string_size_from_utf16_stream(
			            value_data,
			            value_data_size,
			            LIBNK2_ENDIAN_LITTLE,
			            size,
			            error ) != 1 ) )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to determine string size.",
				 function );

				return( -1 );
			}
		}
	}
	return( result );
}

/* Retrieves the string value of a specific entry from the referenced item
 * Returns 1 if successful, 0 if the item does not contain such value or -1 on error
 */
int libnk2_item_values_get_entry_value_string(
     libnk2_item_values_t *item_values,
     libnk2_io_handle_t *io_handle,
     uint32_t entry_type,
     uint8_t *string,
     size_t size,
     int ascii_codepage,
     liberror_error_t **error )
{
	uint8_t *value_data    = NULL;
	static char *function  = "libnk2_item_values_get_entry_value_string";
	uint32_t value_type    = 0;
	size_t value_data_size = 0;
	int result             = 0;

	if( string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( size == 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
	if( size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
	result = libnk2_item_values_get_entry_value(
	          item_values,
	          io_handle,
	          entry_type,
	          &value_type,
	          &value_data,
	          &value_data_size,
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
			 "%s: unsupport string value type: 0x%04" PRIx32 ".",
			 function,
			 value_type );

			return( -1 );
		}
		/* Internally an empty string is represented by a NULL reference
		 */
		if( value_data == NULL )
		{
			string[ 0 ] = 0;
		}
		else if( ( value_type == LIBNK2_VALUE_TYPE_STRING_ASCII )
		      && ( libuna_utf8_string_copy_from_byte_stream(
		            string,
		            size,
		            value_data,
		            value_data_size,
		            ascii_codepage,
		            error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to set string.",
			 function );

			return( -1 );
		}
		else if( ( value_type == LIBNK2_VALUE_TYPE_STRING_UNICODE )
		      && ( libuna_utf8_string_copy_from_utf16_stream(
			    string,
			    size,
			    value_data,
			    value_data_size,
			    LIBNK2_ENDIAN_LITTLE,
			    error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to set string.",
			 function );

			return( -1 );
		}
	}
	return( result );
}


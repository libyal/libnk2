/*
 * Legacy functions
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
#include <types.h>

#include "libnk2_definitions.h"
#include "libnk2_item.h"
#include "libnk2_legacy.h"
#include "libnk2_libcerror.h"
#include "libnk2_record_entry.h"
#include "libnk2_mapi.h"
#include "libnk2_types.h"
#include "libnk2_unused.h"

#if !defined( HAVE_LOCAL_LIBNK2 )

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
	libnk2_record_entry_t *record_entry = NULL;
	static char *function               = "libnk2_item_get_entry_type";

	if( libnk2_item_get_entry_by_index(
	     item,
	     entry_index,
	     &record_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve record entry: %d.",
		 function,
		 entry_index );

		return( -1 );
	}
	if( libnk2_record_entry_get_entry_type(
	     record_entry,
	     entry_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry type.",
		 function );

		return( -1 );
	}
	if( libnk2_record_entry_get_value_type(
	     record_entry,
	     value_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value type.",
		 function );

		return( -1 );
	}
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
	libnk2_record_entry_t *record_entry = NULL;
	static char *function               = "libnk2_item_get_value_type";
	int result                          = 0;

	result = libnk2_item_get_entry_by_type(
	          item,
	          entry_type,
	          0,
	          &record_entry,
	          LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve record entry: 0x%04" PRIx16 ".",
		 function,
		 entry_type );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libnk2_record_entry_get_value_type(
		     record_entry,
		     value_type,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value type.",
			 function );

			return( -1 );
		}
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
     libnk2_item_t *item LIBNK2_ATTRIBUTE_UNUSED,
     uint32_t entry_type LIBNK2_ATTRIBUTE_UNUSED,
     uint32_t *value_type LIBNK2_ATTRIBUTE_UNUSED,
     uint8_t **value_data LIBNK2_ATTRIBUTE_UNUSED,
     size_t *value_data_size LIBNK2_ATTRIBUTE_UNUSED,
     uint8_t flags LIBNK2_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	static char *function = "libnk2_item_get_entry_value";

	LIBNK2_UNREFERENCED_PARAMETER( item )
	LIBNK2_UNREFERENCED_PARAMETER( entry_type )
	LIBNK2_UNREFERENCED_PARAMETER( value_type )
	LIBNK2_UNREFERENCED_PARAMETER( value_data )
	LIBNK2_UNREFERENCED_PARAMETER( value_data_size )
	LIBNK2_UNREFERENCED_PARAMETER( flags )

	libcerror_error_set(
	 error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "%s: access to library internal allocated memory no longer supported.",
	 function );

	return( -1 );
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
	libnk2_record_entry_t *record_entry = NULL;
	static char *function               = "libnk2_item_get_entry_value_boolean";
	int result                          = 0;

	result = libnk2_item_get_entry_by_type(
	          item,
	          entry_type,
	          LIBNK2_VALUE_TYPE_BOOLEAN,
	          &record_entry,
	          0,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve record entry: 0x%04" PRIx16 " 0x%04" PRIx16 ".",
		 function,
		 entry_type,
		 LIBNK2_VALUE_TYPE_BOOLEAN );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libnk2_record_entry_get_data_as_boolean(
		     record_entry,
		     entry_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve boolean value.",
			 function );

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
	libnk2_record_entry_t *record_entry = NULL;
	static char *function               = "libnk2_item_get_entry_value_32bit";
	int result                          = 0;

	result = libnk2_item_get_entry_by_type(
	          item,
	          entry_type,
	          LIBNK2_VALUE_TYPE_INTEGER_32BIT_SIGNED,
	          &record_entry,
	          0,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve record entry: 0x%04" PRIx16 " 0x%04" PRIx16 ".",
		 function,
		 entry_type,
		 LIBNK2_VALUE_TYPE_INTEGER_32BIT_SIGNED );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libnk2_record_entry_get_data_as_32bit_integer(
		     record_entry,
		     entry_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve 32-bit integer value.",
			 function );

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
	libnk2_record_entry_t *record_entry = NULL;
	static char *function               = "libnk2_item_get_entry_value_64bit";
	int result                          = 0;

	result = libnk2_item_get_entry_by_type(
	          item,
	          entry_type,
	          LIBNK2_VALUE_TYPE_INTEGER_64BIT_SIGNED,
	          &record_entry,
	          0,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve record entry: 0x%04" PRIx16 " 0x%04" PRIx16 ".",
		 function,
		 entry_type,
		 LIBNK2_VALUE_TYPE_INTEGER_64BIT_SIGNED );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libnk2_record_entry_get_data_as_64bit_integer(
		     record_entry,
		     entry_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve 64-bit integer value.",
			 function );

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
	libnk2_record_entry_t *record_entry = NULL;
	static char *function               = "libnk2_item_get_entry_value_filetime";
	int result                          = 0;

	result = libnk2_item_get_entry_by_type(
	          item,
	          entry_type,
	          LIBNK2_VALUE_TYPE_FILETIME,
	          &record_entry,
	          0,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve record entry: 0x%04" PRIx16 " 0x%04" PRIx16 ".",
		 function,
		 entry_type,
		 LIBNK2_VALUE_TYPE_FILETIME );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libnk2_record_entry_get_data_as_filetime(
		     record_entry,
		     entry_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve filetime value.",
			 function );

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
	libnk2_record_entry_t *record_entry = NULL;
	static char *function               = "libnk2_item_get_entry_value_size";
	size64_t value_size                 = 0;
	int result                          = 0;

	if( entry_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry value.",
		 function );

		return( -1 );
	}
	result = libnk2_item_get_entry_by_type(
	          item,
	          entry_type,
	          0,
	          &record_entry,
	          LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve record entry: 0x%04" PRIx16 " 0x%04" PRIx16 ".",
		 function,
		 entry_type,
		 0 );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libnk2_record_entry_get_data_as_size(
		     record_entry,
		     &value_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve filetime value.",
			 function );

			return( -1 );
		}
		*entry_value = (size_t) value_size;
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
	libnk2_record_entry_t *record_entry = NULL;
	static char *function               = "libnk2_item_get_entry_value_floating_point";
	int result                          = 0;

	result = libnk2_item_get_entry_by_type(
	          item,
	          entry_type,
	          0,
	          &record_entry,
	          LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve record entry: 0x%04" PRIx16 " 0x%04" PRIx16 ".",
		 function,
		 entry_type,
		 0 );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libnk2_record_entry_get_data_as_floating_point(
		     record_entry,
		     entry_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve floating point value.",
			 function );

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
	libnk2_record_entry_t *record_entry = NULL;
	static char *function               = "libnk2_item_get_entry_value_utf8_string_size";
	int result                          = 0;

	result = libnk2_item_get_entry_by_type(
	          item,
	          entry_type,
	          0,
	          &record_entry,
	          LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve record entry: 0x%04" PRIx16 " 0x%04" PRIx16 ".",
		 function,
		 entry_type,
		 0 );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libnk2_record_entry_get_data_as_utf8_string_size(
		     record_entry,
		     utf8_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve size of UTF-8 string.",
			 function );

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
	libnk2_record_entry_t *record_entry = NULL;
	static char *function               = "libnk2_item_get_entry_value_utf8_string";
	int result                          = 0;

	result = libnk2_item_get_entry_by_type(
	          item,
	          entry_type,
	          0,
	          &record_entry,
	          LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve record entry: 0x%04" PRIx16 " 0x%04" PRIx16 ".",
		 function,
		 entry_type,
		 0 );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libnk2_record_entry_get_data_as_utf8_string(
		     record_entry,
		     utf8_string,
		     utf8_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-8 string.",
			 function );

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
	libnk2_record_entry_t *record_entry = NULL;
	static char *function               = "libnk2_item_get_entry_value_utf16_string_size";
	int result                          = 0;

	result = libnk2_item_get_entry_by_type(
	          item,
	          entry_type,
	          0,
	          &record_entry,
	          LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve record entry: 0x%04" PRIx16 " 0x%04" PRIx16 ".",
		 function,
		 entry_type,
		 0 );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libnk2_record_entry_get_data_as_utf16_string_size(
		     record_entry,
		     utf16_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve size of UTF-16 string.",
			 function );

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
	libnk2_record_entry_t *record_entry = NULL;
	static char *function               = "libnk2_item_get_entry_value_utf16_string";
	int result                          = 0;

	result = libnk2_item_get_entry_by_type(
	          item,
	          entry_type,
	          0,
	          &record_entry,
	          LIBNK2_ENTRY_VALUE_FLAG_MATCH_ANY_VALUE_TYPE,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve record entry: 0x%04" PRIx16 " 0x%04" PRIx16 ".",
		 function,
		 entry_type,
		 0 );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libnk2_record_entry_get_data_as_utf16_string(
		     record_entry,
		     utf16_string,
		     utf16_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-16 string.",
			 function );

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
	libnk2_record_entry_t *record_entry = NULL;
	static char *function               = "libnk2_item_get_entry_value_binary_data_size";
	int result                          = 0;

	result = libnk2_item_get_entry_by_type(
	          item,
	          entry_type,
	          LIBNK2_VALUE_TYPE_BINARY_DATA,
	          &record_entry,
	          0,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve record entry: 0x%04" PRIx16 " 0x%04" PRIx16 ".",
		 function,
		 entry_type,
		 LIBNK2_VALUE_TYPE_BINARY_DATA );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libnk2_record_entry_get_data_size(
		     record_entry,
		     size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data size.",
			 function );

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
	libnk2_record_entry_t *record_entry = NULL;
	static char *function               = "libnk2_item_get_entry_value_binary_data";
	int result                          = 0;

	result = libnk2_item_get_entry_by_type(
	          item,
	          entry_type,
	          LIBNK2_VALUE_TYPE_BINARY_DATA,
	          &record_entry,
	          0,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve record entry: 0x%04" PRIx16 " 0x%04" PRIx16 ".",
		 function,
		 entry_type,
		 LIBNK2_VALUE_TYPE_BINARY_DATA );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libnk2_record_entry_get_data(
		     record_entry,
		     binary_data,
		     size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data.",
			 function );

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
	libnk2_record_entry_t *record_entry = NULL;
	static char *function               = "libnk2_item_get_entry_value_guid";
	int result                          = 0;

	result = libnk2_item_get_entry_by_type(
	          item,
	          entry_type,
	          LIBNK2_VALUE_TYPE_GUID,
	          &record_entry,
	          0,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve record entry: 0x%04" PRIx16 " 0x%04" PRIx16 ".",
		 function,
		 entry_type,
		 LIBNK2_VALUE_TYPE_GUID );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libnk2_record_entry_get_data_as_guid(
		     record_entry,
		     guid,
		     size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve GUID.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

#endif /* !defined( HAVE_LOCAL_LIBNK2 ) */


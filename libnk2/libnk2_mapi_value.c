/*
 * MAPI value functions
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
#include <types.h>

#include "libnk2_libcerror.h"
#include "libnk2_libuna.h"
#include "libnk2_mapi.h"
#include "libnk2_mapi_value.h"

/* Retrieves the value data size
 * Returns 1 if successful or -1 on error
 */
int libnk2_mapi_value_get_data_size(
     uint32_t value_type,
     size_t *value_data_size,
     libcerror_error_t **error )
{
	static char *function = "libnk2_mapi_value_get_data_size";

	if( value_data_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value data size.",
		 function );

		return( -1 );
	}
	/* TODO add other value types to the item entry
	 */
	switch( value_type )
	{
		case LIBNK2_VALUE_TYPE_BOOLEAN:
		case LIBNK2_VALUE_TYPE_INTEGER_16BIT_SIGNED:
			*value_data_size = 2;
			break;

		case LIBNK2_VALUE_TYPE_INTEGER_32BIT_SIGNED:
		case LIBNK2_VALUE_TYPE_FLOAT_32BIT:
		case LIBNK2_VALUE_TYPE_ERROR:
			*value_data_size = 4;
			break;

		case LIBNK2_VALUE_TYPE_INTEGER_64BIT_SIGNED:
		case LIBNK2_VALUE_TYPE_DOUBLE_64BIT:
		case LIBNK2_VALUE_TYPE_CURRENCY:
		case LIBNK2_VALUE_TYPE_FLOATINGTIME:
		case LIBNK2_VALUE_TYPE_FILETIME:
			*value_data_size = 8;
			break;

		case LIBNK2_VALUE_TYPE_STRING_ASCII:
		case LIBNK2_VALUE_TYPE_STRING_UNICODE:
		case LIBNK2_VALUE_TYPE_BINARY_DATA:
			*value_data_size = 0;
			break;

		default:
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported value type: 0x%04" PRIx32 ".",
			 function,
			 value_type );

			return( -1 );
	}
	return( 1 );
}

/* Determines if there are zero bytes in a string, trailing zero bytes not included
 * Returns 1 if the data contains zero bytes, 0 if not or -1 on error
 */
int libnk2_mapi_value_data_contains_zero_bytes(
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function   = "libnk2_mapi_value_data_contains_zero_bytes";
	size_t data_offset      = 0;
	uint8_t zero_byte_found = 0;

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
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	for( data_offset = 0;
	     data_offset < data_size;
	     data_offset++ )
	{
		if( zero_byte_found == 0 )
		{
			if( data[ data_offset ] == 0 )
			{
				zero_byte_found = 1;
			}
		}
		else
		{
			if( data[ data_offset ] != 0 )
			{
				return( 1 );
			}
		}
	}
	return( 0 );
}

/* Retrieves the size of the MAPI value formatted as an UTF-8 string
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libnk2_mapi_value_get_data_as_utf8_string_size(
     uint32_t value_type,
     const uint8_t *value_data,
     size_t value_data_size,
     int ascii_codepage,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	static char *function   = "libnk2_mapi_value_get_data_as_utf8_string_size";
	uint8_t is_ascii_string = 0;
	int result              = 0;

	if( utf8_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string size.",
		 function );

		return( -1 );
	}
	if( ( value_data == NULL )
	 || ( value_data_size == 0 ) )
	{
		*utf8_string_size = 0;

		return( 1 );
	}
	if( value_type == LIBNK2_VALUE_TYPE_STRING_ASCII )
	{
		is_ascii_string = 1;
	}
	/* Codepage 1200 represents Unicode
	 * If the codepage is 1200 find out if the string is encoded in UTF-8 or UTF-16 little-endian
	 */
	if( ( is_ascii_string != 0 )
	 && ( ascii_codepage == 1200 ) )
	{
		result = libnk2_mapi_value_data_contains_zero_bytes(
			  value_data,
			  value_data_size,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine if value data contains zero bytes.",
			 function );

			return( -1 );
		}
		else if( result != 0 )
		{
			is_ascii_string = 0;
		}
	}
	/* String is in UTF-16 little-endian
	 */
	if( is_ascii_string == 0 )
	{
		result = libuna_utf8_string_size_from_utf16_stream(
		          value_data,
		          value_data_size,
		          LIBUNA_ENDIAN_LITTLE,
		          utf8_string_size,
		          error );
	}
	/* Codepage 65000 represents UTF-7
	 */
	else if( ascii_codepage == 65000 )
	{
		result = libuna_utf8_string_size_from_utf7_stream(
			  value_data,
			  value_data_size,
			  utf8_string_size,
			  error );
	}
	/* Codepage 1200 or 65001 represents UTF-8
	 */
	else if( ( ascii_codepage == 1200 )
	      || ( ascii_codepage == 65001 ) )
	{
		result = libuna_utf8_string_size_from_utf8_stream(
			  value_data,
			  value_data_size,
			  utf8_string_size,
			  error );
	}
	else
	{
		/* TODO currently libuna uses the same numeric values for the codepages as NK2
		 * add a mapping function if this implementation changes
		 */
		result = libuna_utf8_string_size_from_byte_stream(
			  value_data,
			  value_data_size,
			  ascii_codepage,
			  utf8_string_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of value data as UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the MAPI value formatted as an UTF-8 string value
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libnk2_mapi_value_get_data_as_utf8_string(
     uint32_t value_type,
     const uint8_t *value_data,
     size_t value_data_size,
     int ascii_codepage,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	static char *function   = "libnk2_mapi_value_get_data_as_utf8_string";
	uint8_t is_ascii_string = 0;
	int result              = 0;

	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid UTF-8 string size value zero or less.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( value_data == NULL )
	 || ( value_data_size == 0 ) )
	{
		utf8_string[ 0 ] = 0;

		return( 1 );
	}
	if( value_type == LIBNK2_VALUE_TYPE_STRING_ASCII )
	{
		is_ascii_string = 1;
	}
	/* Codepage 1200 represents Unicode
	 * If the codepage is 1200 find out if the string is encoded in UTF-8 or UTF-16 little-endian
	 */
	if( ( is_ascii_string != 0 )
	 && ( ascii_codepage == 1200 ) )
	{
		result = libnk2_mapi_value_data_contains_zero_bytes(
			  value_data,
			  value_data_size,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine if value data contains zero bytes.",
			 function );

			return( -1 );
		}
		else if( result != 0 )
		{
			is_ascii_string = 0;
		}
	}
	/* String is in UTF-16 little-endian
	 */
	if( is_ascii_string == 0 )
	{
		result = libuna_utf8_string_copy_from_utf16_stream(
		          utf8_string,
		          utf8_string_size,
		          value_data,
		          value_data_size,
		          LIBUNA_ENDIAN_LITTLE,
		          error );
	}
	/* Codepage 65000 represents UTF-7
	 */
	else if( ascii_codepage == 65000 )
	{
		result = libuna_utf8_string_copy_from_utf7_stream(
		          utf8_string,
		          utf8_string_size,
		          value_data,
		          value_data_size,
		          error );
	}
	/* Codepage 1200 or 65001 represents UTF-8
	 */
	else if( ( ascii_codepage == 1200 )
	      || ( ascii_codepage == 65001 ) )
	{
		result = libuna_utf8_string_copy_from_utf8_stream(
		          utf8_string,
		          utf8_string_size,
		          value_data,
		          value_data_size,
		          error );
	}
	else
	{
		/* TODO currently libuna uses the same numeric values for the codepages as NK2
		 * add a mapping function if this implementation changes
		 */
		result = libuna_utf8_string_copy_from_byte_stream(
		          utf8_string,
		          utf8_string_size,
		          value_data,
		          value_data_size,
		          ascii_codepage,
		          error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value data to UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the MAPI value formatted as an UTF-16 string
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libnk2_mapi_value_get_data_as_utf16_string_size(
     uint32_t value_type,
     const uint8_t *value_data,
     size_t value_data_size,
     int ascii_codepage,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function   = "libnk2_mapi_value_get_data_as_utf16_string_size";
	uint8_t is_ascii_string = 0;
	int result              = 0;

	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	if( ( value_data == NULL )
	 || ( value_data_size == 0 ) )
	{
		*utf16_string_size = 0;

		return( 1 );
	}
	if( value_type == LIBNK2_VALUE_TYPE_STRING_ASCII )
	{
		is_ascii_string = 1;
	}
	/* Codepage 1200 represents Unicode
	 * If the codepage is 1200 find out if the string is encoded in UTF-8 or UTF-16 little-endian
	 */
	if( ( is_ascii_string != 0 )
	 && ( ascii_codepage == 1200 ) )
	{
		result = libnk2_mapi_value_data_contains_zero_bytes(
			  value_data,
			  value_data_size,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine if value data contains zero bytes.",
			 function );

			return( -1 );
		}
		else if( result != 0 )
		{
			is_ascii_string = 0;
		}
	}
	/* String is in UTF-16 little-endian
	 */
	if( is_ascii_string == 0 )
	{
		result = libuna_utf16_string_size_from_utf16_stream(
		          value_data,
		          value_data_size,
		          LIBUNA_ENDIAN_LITTLE,
		          utf16_string_size,
		          error );
	}
	/* Codepage 65000 represents UTF-7
	 */
	else if( ascii_codepage == 65000 )
	{
		result = libuna_utf16_string_size_from_utf7_stream(
			  value_data,
			  value_data_size,
			  utf16_string_size,
			  error );
	}
	/* Codepage 1200 or 65001 represents UTF-8
	 */
	else if( ( ascii_codepage == 1200 )
	      || ( ascii_codepage == 65001 ) )
	{
		result = libuna_utf16_string_size_from_utf8_stream(
			  value_data,
			  value_data_size,
			  utf16_string_size,
			  error );
	}
	else
	{
		/* TODO currently libuna uses the same numeric values for the codepages as NK2
		 * add a mapping function if this implementation changes
		 */
		result = libuna_utf16_string_size_from_byte_stream(
			  value_data,
			  value_data_size,
			  ascii_codepage,
			  utf16_string_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of value data as UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the MAPI value formatted as an UTF-16 string value
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libnk2_mapi_value_get_data_as_utf16_string(
     uint32_t value_type,
     const uint8_t *value_data,
     size_t value_data_size,
     int ascii_codepage,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	static char *function   = "libnk2_mapi_value_get_data_as_utf16_string";
	uint8_t is_ascii_string = 0;
	int result              = 0;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid UTF-16 string size value zero or less.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( value_data == NULL )
	 || ( value_data_size == 0 ) )
	{
		utf16_string[ 0 ] = 0;

		return( 1 );
	}
	if( value_type == LIBNK2_VALUE_TYPE_STRING_ASCII )
	{
		is_ascii_string = 1;
	}
	/* Codepage 1200 represents Unicode
	 * If the codepage is 1200 find out if the string is encoded in UTF-8 or UTF-16 little-endian
	 */
	if( ( is_ascii_string != 0 )
	 && ( ascii_codepage == 1200 ) )
	{
		result = libnk2_mapi_value_data_contains_zero_bytes(
			  value_data,
			  value_data_size,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine if value data contains zero bytes.",
			 function );

			return( -1 );
		}
		else if( result != 0 )
		{
			is_ascii_string = 0;
		}
	}
	/* String is in UTF-16 little-endian
	 */
	if( is_ascii_string == 0 )
	{
		result = libuna_utf16_string_copy_from_utf16_stream(
		          utf16_string,
		          utf16_string_size,
		          value_data,
		          value_data_size,
		          LIBUNA_ENDIAN_LITTLE,
		          error );
	}
	/* Codepage 65000 represents UTF-7
	 */
	else if( ascii_codepage == 65000 )
	{
		result = libuna_utf16_string_copy_from_utf7_stream(
		          utf16_string,
		          utf16_string_size,
		          value_data,
		          value_data_size,
		          error );
	}
	/* Codepage 1200 or 65001 represents UTF-8
	 */
	else if( ( ascii_codepage == 1200 )
	      || ( ascii_codepage == 65001 ) )
	{
		result = libuna_utf16_string_copy_from_utf8_stream(
		          utf16_string,
		          utf16_string_size,
		          value_data,
		          value_data_size,
		          error );
	}
	else
	{
		/* TODO currently libuna uses the same numeric values for the codepages as NK2
		 * add a mapping function if this implementation changes
		 */
		result = libuna_utf16_string_copy_from_byte_stream(
		          utf16_string,
		          utf16_string_size,
		          value_data,
		          value_data_size,
		          ascii_codepage,
		          error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value data to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}


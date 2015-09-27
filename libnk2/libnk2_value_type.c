/*
 * Values type functions
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

#include "libnk2_definitions.h"
#include "libnk2_libuna.h"
#include "libnk2_value_type.h"

/* Converts the value data into a boolean value
 * Returns 1 if successful or -1 on error
 */
int libnk2_value_type_copy_to_boolean(
     uint8_t *value_data,
     size_t value_data_size,
     uint8_t *value_boolean,
     liberror_error_t **error )
{
	static char *function = "libnk2_value_type_copy_to_boolean";

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
	if( value_boolean == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value boolean.",
		 function );

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
		 "%s: invalid value data size.",
		 function );

		return( -1 );
	}
	*value_boolean = value_data[ 0 ];

	return( 1 );
}

/* Converts the value data into a 16-bit value
 * Returns 1 if successful or -1 on error
 */
int libnk2_value_type_copy_to_16bit(
     uint8_t *value_data,
     size_t value_data_size,
     uint16_t *value_16bit,
     liberror_error_t **error )
{
	static char *function = "libnk2_value_type_copy_to_16bit";

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
	if( value_16bit == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value 16-bit.",
		 function );

		return( -1 );
	}
	/* The value data size of a 16-bit value is 2
	 */
	if( value_data_size != 2 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid value data size.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint16_little_endian(
	 value_data,
	 *value_16bit );

	return( 1 );
}

/* Converts the value data into a 32-bit value
 * Returns 1 if successful or -1 on error
 */
int libnk2_value_type_copy_to_32bit(
     uint8_t *value_data,
     size_t value_data_size,
     uint32_t *value_32bit,
     liberror_error_t **error )
{
	static char *function = "libnk2_value_type_copy_to_32bit";

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
	if( value_32bit == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value 32-bit.",
		 function );

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
		 "%s: invalid value data size.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 value_data,
	 *value_32bit );

	return( 1 );
}

/* Converts the value data into a 64-bit value
 * Returns 1 if successful or -1 on error
 */
int libnk2_value_type_copy_to_64bit(
     uint8_t *value_data,
     size_t value_data_size,
     uint64_t *value_64bit,
     liberror_error_t **error )
{
	static char *function = "libnk2_value_type_copy_to_64bit";

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
	if( value_64bit == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value 64-bit.",
		 function );

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
		 "%s: invalid value data size.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint64_little_endian(
	 value_data,
	 *value_64bit );

	return( 1 );
}

/* Converts the value data into a size value
 * Returns 1 if successful or -1 on error
 */
int libnk2_value_type_copy_to_size(
     uint8_t *value_data,
     size_t value_data_size,
     size_t *value_size,
     liberror_error_t **error )
{
	static char *function = "libnk2_value_type_copy_to_size";

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
	if( value_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value size.",
		 function );

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
		 "%s: invalid value data size.",
		 function );

		return( -1 );
	}
	if( value_data_size == 4 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 value_data,
		 *value_size );
	}
	else if( value_data_size == 8 )
	{
		byte_stream_copy_to_uint64_little_endian(
		 value_data,
		 *value_size );
	}
	return( 1 );
}

/* Converts the value data into a floating point value
 * Returns 1 if successful or -1 on error
 */
int libnk2_value_type_copy_to_floating_point(
     uint8_t *value_data,
     size_t value_data_size,
     double *value_floating_point,
     liberror_error_t **error )
{
	byte_stream_float64_t value_double;
	byte_stream_float32_t value_float;

	static char *function = "libnk2_value_type_copy_to_floating_point";

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
	if( value_floating_point == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value floating point.",
		 function );

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
		 "%s: invalid value data size.",
		 function );

		return( -1 );
	}
	if( value_data_size == 4 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 value_data,
		 value_float.integer );

		*value_floating_point = (double) value_float.floating_point;
	}
	else if( value_data_size == 8 )
	{
		byte_stream_copy_to_uint64_little_endian(
		 value_data,
		 value_double.integer );

		*value_floating_point = value_double.floating_point;
	}
	return( 1 );
}

/* Determines the UTF-8 string size from the value data
 * Returns 1 if successful or -1 on error
 */
int libnk2_value_type_get_utf8_string_size(
     uint8_t *value_data,
     size_t value_data_size,
     uint8_t is_ascii_string,
     uint32_t ascii_codepage,
     size_t *utf8_string_size,
     liberror_error_t **error )
{
	static char *function = "libnk2_value_type_get_utf8_string_size";

	if( utf8_string_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string size.",
		 function );

		return( -1 );
	}
	/* Internally an empty string is represented by a NULL reference
	 */
	if( value_data == NULL )
	{
		*utf8_string_size = 0;
	}
	else if( is_ascii_string != 0 )
	{
		/* Codepage 65000 represents UTF-7
		 */
		if( ascii_codepage == 65000 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported codepage: UTF-7.",
			 function );

			return( -1 );
		}
		/* Codepage 65001 represents UTF-8
		 */
		else if( ascii_codepage == 65001 )
		{
			if( libuna_utf8_string_size_from_utf8_stream(
			     value_data,
			     value_data_size,
			     utf8_string_size,
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to determine UTF-8 string size.",
				 function );

				return( -1 );
			}
		}
		else
		{
			/* TODO currently libuna uses the same numeric values for the codepages as NK2
			 * add a mapping function if this implementation changes
			 */
			if( libuna_utf8_string_size_from_byte_stream(
			     value_data,
			     value_data_size,
			     (int) ascii_codepage,
			     utf8_string_size,
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to determine UTF-8 string size.",
				 function );

				return( -1 );
			}
		}
	}
	else
	{
		if( libuna_utf8_string_size_from_utf16_stream(
		     value_data,
		     value_data_size,
		     LIBUNA_ENDIAN_LITTLE,
		     utf8_string_size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine UTF-8 string size.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Converts the value data into a UTF-8 string
 * Returns 1 if successful or -1 on error
 */
int libnk2_value_type_copy_to_utf8_string(
     uint8_t *value_data,
     size_t value_data_size,
     uint8_t is_ascii_string,
     uint32_t ascii_codepage,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liberror_error_t **error )
{
	static char *function = "libnk2_value_type_copy_to_utf8_string";

	if( utf8_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size == 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid UTF-8 string size.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	/* Internally an empty string is represented by a NULL reference
	 */
	if( value_data == NULL )
	{
		utf8_string[ 0 ] = 0;
	}
	else if( is_ascii_string != 0 )
	{
		/* Codepage 65000 represents UTF-7
		 */
		if( ascii_codepage == 65000 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported codepage: UTF-7.",
			 function );

			return( -1 );
		}
		/* Codepage 65001 represents UTF-8
		 */
		else if( ascii_codepage == 65001 )
		{
			if( libuna_utf8_string_copy_from_utf8_stream(
			     utf8_string,
			     utf8_string_size,
			     value_data,
			     value_data_size,
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to determine UTF-8 string size.",
				 function );

				return( -1 );
			}
		}
		else
		{
			/* TODO currently libuna uses the same numeric values for the codepages as NK2
			 * add a mapping function if this implementation changes
			 */
			if( libuna_utf8_string_copy_from_byte_stream(
			     utf8_string,
			     utf8_string_size,
			     value_data,
			     value_data_size,
			     (int) ascii_codepage,
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_CONVERSION,
				 LIBERROR_CONVERSION_ERROR_GENERIC,
				 "%s: unable to set UTF-8 string.",
				 function );

				return( -1 );
			}
		}
	}
	else
	{
		if( libuna_utf8_string_copy_from_utf16_stream(
		     utf8_string,
		     utf8_string_size,
		     value_data,
		     value_data_size,
		     LIBUNA_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to set UTF-8 string.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Determines the UTF-16 string size from the value data
 * Returns 1 if successful or -1 on error
 */
int libnk2_value_type_get_utf16_string_size(
     uint8_t *value_data,
     size_t value_data_size,
     uint8_t is_ascii_string,
     uint32_t ascii_codepage,
     size_t *utf16_string_size,
     liberror_error_t **error )
{
	static char *function = "libnk2_value_type_get_utf16_string_size";

	if( utf16_string_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	/* Internally an empty string is represented by a NULL reference
	 */
	if( value_data == NULL )
	{
		*utf16_string_size = 0;
	}
	else if( is_ascii_string != 0 )
	{
		/* Codepage 65000 represents UTF-7
		 */
		if( ascii_codepage == 65000 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported codepage: UTF-7.",
			 function );

			return( -1 );
		}
		/* Codepage 65001 represents UTF-8
		 */
		else if( ascii_codepage == 65001 )
		{
			if( libuna_utf16_string_size_from_utf8(
			     value_data,
			     value_data_size,
			     utf16_string_size,
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to determine UTF-16 string size.",
				 function );

				return( -1 );
			}
		}
		else
		{
			/* TODO currently libuna uses the same numeric values for the codepages as NK2
			 * add a mapping function if this implementation changes
			 */
			if( libuna_utf16_string_size_from_byte_stream(
			     value_data,
			     value_data_size,
			     (int) ascii_codepage,
			     utf16_string_size,
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to determine UTF-16 string size.",
				 function );

				return( -1 );
			}
		}
	}
	else
	{
		if( libuna_utf16_string_size_from_utf16_stream(
		     value_data,
		     value_data_size,
		     LIBUNA_ENDIAN_LITTLE,
		     utf16_string_size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine UTF-16 string size.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Converts the value data into a UTF-16 string
 * Returns 1 if successful or -1 on error
 */
int libnk2_value_type_copy_to_utf16_string(
     uint8_t *value_data,
     size_t value_data_size,
     uint8_t is_ascii_string,
     uint32_t ascii_codepage,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     liberror_error_t **error )
{
	static char *function = "libnk2_value_type_copy_to_utf16_string";

	if( utf16_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	/* Internally an empty string is represented by a NULL reference
	 */
	if( value_data == NULL )
	{
		utf16_string[ 0 ] = 0;
	}
	else if( is_ascii_string != 0 )
	{
		/* Codepage 65000 represents UTF-7
		 */
		if( ascii_codepage == 65000 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported codepage: UTF-7.",
			 function );

			return( -1 );
		}
		/* Codepage 65001 represents UTF-8
		 */
		else if( ascii_codepage == 65001 )
		{
			if( libuna_utf16_string_copy_from_utf8(
			     utf16_string,
			     utf16_string_size,
			     value_data,
			     value_data_size,
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_CONVERSION,
				 LIBERROR_CONVERSION_ERROR_GENERIC,
				 "%s: unable to set UTF-16 string.",
				 function );

				return( -1 );
			}
		}
		else
		{
			/* TODO currently libuna uses the same numeric values for the codepages as NK2
			 * add a mapping function if this implementation changes
			 */
			if( libuna_utf16_string_copy_from_byte_stream(
			     utf16_string,
			     utf16_string_size,
			     value_data,
			     value_data_size,
			     (int) ascii_codepage,
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_CONVERSION,
				 LIBERROR_CONVERSION_ERROR_GENERIC,
				 "%s: unable to set UTF-16 string.",
				 function );

				return( -1 );
			}
		}
	}
	else
	{
		if( libuna_utf16_string_copy_from_utf16_stream(
		     utf16_string,
		     utf16_string_size,
		     value_data,
		     value_data_size,
		     LIBUNA_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to set UTF-16 string.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Determines the binary data size from the value data
 * Returns 1 if successful or -1 on error
 */
int libnk2_value_type_get_binary_data_size(
     uint8_t *value_data,
     size_t value_data_size,
     size_t *binary_data_size,
     liberror_error_t **error )
{
	static char *function = "libnk2_value_type_get_binary_data_size";

	if( binary_data_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary data size.",
		 function );

		return( -1 );
	}
	/* Internally an empty binary data is represented by a NULL reference
	 */
	if( value_data == NULL )
	{
		*binary_data_size = 0;
	}
	else
	{
		*binary_data_size = value_data_size;
	}
	return( 1 );
}

/* Converts the value data into binary data
 * Returns 1 if successful or -1 on error
 */
int libnk2_value_type_copy_to_binary_data(
     uint8_t *value_data,
     size_t value_data_size,
     uint8_t *binary_data,
     size_t binary_data_size,
     liberror_error_t **error )
{
	static char *function = "libnk2_value_type_copy_to_binary_data";

	if( binary_data == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary data.",
		 function );

		return( -1 );
	}
	if( binary_data_size == 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid binary data size.",
		 function );

		return( -1 );
	}
	if( binary_data_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid binary data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	/* Internally empty binary data is represented by a NULL reference
	 */
	if( value_data != NULL )
	{
		if( binary_data_size < value_data_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: binary data is too small.",
			 function );

			return( -1 );
		}
		if( memory_copy(
		     binary_data,
		     value_data,
		     value_data_size ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to set binary data.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}


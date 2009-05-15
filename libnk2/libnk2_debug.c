/*
 * Debug functions
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
#include <memory.h>
#include <types.h>

#include <liberror.h>
#include <libfmapi.h>

#include "libnk2_debug.h"
#include "libnk2_definitions.h"
#include "libnk2_libbfio.h"
#include "libnk2_notify.h"
#include "libnk2_string.h"

#if defined( HAVE_DEBUG_OUTPUT )

/* Prints the MAPI value
 * Returns 1 if successful or -1 on error
 */
int libnk2_debug_mapi_value_print(
     uint32_t entry_type,
     uint32_t value_type,
     uint8_t *value_data,
     size_t value_data_size,
     int ascii_codepage,
     liberror_error_t **error )
{
	libnk2_character_t filetime_string[ LIBFMAPI_FILETIME_STRING_SIZE ];
	libnk2_character_t guid_string[ LIBFMAPI_GUID_STRING_SIZE ];

	libnk2_character_t *value_string    = NULL;
	static char *function               = "libnk2_debug_mapi_value_print";
	libfmapi_filetime_t filetime        = LIBFMAPI_FILETIME_ZERO;
	size_t value_string_size            = 0;
	double value_double                 = 0.0;
	float value_float                   = 0.0;
	uint64_t value_64bit                = 0;
	uint32_t value_32bit                = 0;

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
	switch( value_type )
	{
		case 0x0004:
			endian_little_convert_64bit(
			 value_64bit,
			 value_data );

			if( memory_copy(
			     &value_float,
			     &value_32bit,
			     sizeof( uint32_t ) ) == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to convert 32-bit value into float.",
				 function );

				return( -1 );
			}
			libnk2_notify_verbose_printf(
			 "Floating point value\t: %f\n",
			 value_float );
			libnk2_notify_verbose_printf(
			 "\n" );

			break;

		case 0x0005:
			endian_little_convert_64bit(
			 value_64bit,
			 value_data );

			if( memory_copy(
			     &value_double,
			     &value_64bit,
			     sizeof( uint64_t ) ) == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to convert 64-bit value into double.",
				 function );

				return( -1 );
			}
			libnk2_notify_verbose_printf(
			 "Floating point double value\t: %f\n",
			 value_double );
			libnk2_notify_verbose_printf(
			 "\n" );

			break;

		case 0x0014:
			endian_little_convert_64bit(
			 value_64bit,
			 value_data );

			libnk2_notify_verbose_printf(
			 "64-bit value\t: %" PRIu64 "\n",
			 value_64bit );
			libnk2_notify_verbose_printf(
			 "\n" );

			break;

		case 0x0040:
			if( libfmapi_filetime_from_byte_stream(
			     &filetime,
			     value_data,
			     value_data_size,
			     LIBNK2_ENDIAN_LITTLE,
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_CONVERSION,
				 LIBERROR_CONVERSION_ERROR_GENERIC,
				 "%s: unable to create filetime.",
				 function );

				if( ( error != NULL )
				 && ( *error != NULL ) )
				{
			                libnk2_notify_error_backtrace(
			                 *error );
				}
				liberror_error_free(
				 error );

				libnk2_notify_verbose_dump_data(
				 value_data,
				 value_data_size );

				break;
			}
			if( libfmapi_filetime_to_string(
			     &filetime,
			     filetime_string,
			     LIBFMAPI_FILETIME_STRING_SIZE,
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_CONVERSION,
				 LIBERROR_CONVERSION_ERROR_GENERIC,
				 "%s: unable to create filetime string.",
				 function );

				if( ( error != NULL )
				 && ( *error != NULL ) )
				{
			                libnk2_notify_error_backtrace(
			                 *error );
				}
				liberror_error_free(
				 error );

				libnk2_notify_verbose_dump_data(
				 value_data,
				 value_data_size );

				break;
			}
			libnk2_notify_verbose_printf(
			 "Filetime\t: %s\n",
			 filetime_string );
			libnk2_notify_verbose_printf(
			 "\n" );

			break;

		case 0x0048:
			if( value_data_size == 16 )
			{
				if( libfmapi_guid_to_string(
				     (libfmapi_guid_t *) value_data,
				     LIBNK2_ENDIAN_LITTLE,
				     guid_string,
				     LIBFMAPI_GUID_STRING_SIZE,
				     error ) != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_CONVERSION,
					 LIBERROR_CONVERSION_ERROR_GENERIC,
					 "%s: unable to create guid string.",
					 function );

					return( -1 );
				}
				libnk2_notify_verbose_printf(
				 "GUID\t: %s\n",
				 guid_string );
				libnk2_notify_verbose_printf(
				 "\n" );
			}
			else
			{
				libnk2_notify_verbose_dump_data(
				 value_data,
				 value_data_size );
			}
			break;

		case 0x001e:
			if( libnk2_string_size_from_byte_stream(
			     value_data,
			     value_data_size,
			     ascii_codepage,
			     &value_string_size,
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_CONVERSION,
				 LIBERROR_CONVERSION_ERROR_GENERIC,
				 "%s: unable to determine string size.",
				 function );

				if( ( error != NULL )
				 && ( *error != NULL ) )
				{
			                libnk2_notify_error_backtrace(
			                 *error );
				}
				liberror_error_free(
				 error );

				libnk2_notify_verbose_dump_data(
				 value_data,
				 value_data_size );
			}
			else
			{
				value_string = (libnk2_character_t *) memory_allocate(
								       sizeof( libnk2_character_t ) * value_string_size );

				if( value_string == NULL )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_MEMORY,
					 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
					 "%s: unable to create value string.",
					 function );

					return( -1 );
				}
				if( libnk2_string_copy_from_byte_stream(
				     value_string,
				     (size_t) value_string_size,
				     value_data,
				     value_data_size,
				     ascii_codepage,
				     error ) == 1 )
				{
					libnk2_notify_verbose_printf(
					 "ASCII string\t: " );

					libnk2_notify_verbose_printf(
					 "%s\n\n",
					 value_string );
				}
				memory_free(
				 value_string );
			}
			break;

		case 0x001f:
			if( libnk2_string_size_from_utf16_stream(
			     value_data,
			     value_data_size,
			     LIBNK2_ENDIAN_LITTLE,
			     &value_string_size,
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_CONVERSION,
				 LIBERROR_CONVERSION_ERROR_GENERIC,
				 "%s: unable to determine string size.",
				 function );

				if( ( error != NULL )
				 && ( *error != NULL ) )
				{
			                libnk2_notify_error_backtrace(
			                 *error );
				}
				liberror_error_free(
				 error );

				libnk2_notify_verbose_dump_data(
				 value_data,
				 value_data_size );
			}
			else
			{
				value_string = (libnk2_character_t *) memory_allocate(
								       sizeof( libnk2_character_t ) * value_string_size );
				

				if( value_string == NULL )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_MEMORY,
					 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
					 "%s: unable to create value string.",
					 function );

					return( -1 );
				}
				if( libnk2_string_copy_from_utf16_stream(
				     value_string,
				     (size_t) value_string_size,
				     value_data,
				     value_data_size,
				     LIBNK2_ENDIAN_LITTLE,
				     error ) == 1 )
				{
					libnk2_notify_verbose_printf(
					 "Unicode string\t: " );

					libnk2_notify_verbose_printf(
					 "%s\n\n",
					 value_string );
				}
				memory_free(
				 value_string );
			}
			break;

		case 0x0102:
			switch( entry_type )
			{
				default:
					libnk2_notify_verbose_dump_data(
					 value_data,
					 value_data_size );
					break;
			}
			break;

		case 0x1102:
			switch( entry_type )
			{
				default:
					libnk2_notify_verbose_dump_data(
					 value_data,
					 value_data_size );
					break;
			};
			break;

		default:
			libnk2_notify_verbose_dump_data(
			 value_data,
			 value_data_size );
			break;
	};
	return( 1 );
}

/* Prints the read offsets
 * Returns 1 if successful or -1 on error
 */
int libnk2_debug_print_read_offsets(
     libbfio_handle_t *file_io_handle,
     liberror_error_t **error )
{
	static char *function = "libnk2_debug_print_read_offsets";
	off64_t offset        = 0;
	size64_t size         = 0;
	int amount_of_offsets = 0;
	int offset_iterator   = 0;

	if( file_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file io handle.",
		 function );

		return( -1 );
	}
	if( libbfio_handle_get_amount_of_offsets_read(
	     file_io_handle,
	     &amount_of_offsets,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve amount of offsets read.",
		 function );

		return( -1 );
	}
	libnk2_notify_verbose_printf(
	 "Offsets read:\n" );

	for( offset_iterator = 0; offset_iterator < amount_of_offsets; offset_iterator++ )
	{
		if( libbfio_handle_get_offset_read(
		     file_io_handle,
		     offset_iterator,
		     &offset,
		     &size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve offset: %d.",
			 function,
			 ( offset_iterator + 1 ) );

			return( -1 );
		}
		libnk2_notify_verbose_printf(
		 "%08" PRIu64 " ( 0x%08" PRIx64 " ) - %08" PRIu64 " ( 0x%08" PRIx64 " ) size: %" PRIu64 "\n",
		 offset,
		 offset,
		 ( offset + size ),
		 ( offset + size ),
		 size );
	}
	libnk2_notify_verbose_printf(
	 "\n" );

	return( 1 );
}

#endif


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
#include <endian.h>
#include <memory.h>
#include <types.h>

#include "libnk2_debug.h"
#include "libnk2_definitions.h"
#include "libnk2_guid.h"
#include "libnk2_libbfio.h"
#include "libnk2_notify.h"
#include "libnk2_string.h"

#if defined( HAVE_VERBOSE_OUTPUT )

/* Retrieves a string describing the value type
 */
const libnk2_character_t *libnk2_debug_get_value_type_string(
                           uint16_t value_type )
{
	switch( value_type )
	{
		case 0x0000:
			return( _LIBNK2_STRING( "Unspecified (PT_UNSPECIFIED)" ) );
		case 0x0001:
			return( _LIBNK2_STRING( "NULL (PT_NULL)" ) );
		case 0x0002:
			return( _LIBNK2_STRING( "Integer 16-bit signed (PT_SHORT)" ) );
		case 0x0003:
			return( _LIBNK2_STRING( "Integer 32-bit signed (PT_LONG)" ) );
		case 0x0004:
			return( _LIBNK2_STRING( "Floating point single precision (32-bit) (PT_FLOAT)" ) );
		case 0x0005:
			return( _LIBNK2_STRING( "Floating point double precision (64-bit) (PT_DOUBLE)" ) );
		case 0x0006:
			return( _LIBNK2_STRING( "Currency (64-bit) (PT_CURRENCY)" ) );
		case 0x0007:
			return( _LIBNK2_STRING( "Application Time (64-bit) (PT_APPTIME)" ) );
		case 0x000a:
			return( _LIBNK2_STRING( "Error value (32-bit) (PT_ERROR)" ) );
		case 0x000b:
			return( _LIBNK2_STRING( "Boolean (16-bit) (PT_BOOLEAN) (0 == false, 0 != true)" ) );
		case 0x000d:
			return( _LIBNK2_STRING( "Embedded Object (PT_OBJECT)" ) );
		case 0x0014:
			return( _LIBNK2_STRING( "Integer 64-bit signed (PT_I8)" ) );
		case 0x001e:
			return( _LIBNK2_STRING( "(extended) ASCII string (PT_STRING8)" ) );
		case 0x001f:
			return( _LIBNK2_STRING( "Unicode string (PT_UNICODE)" ) );
		case 0x0040:
			return( _LIBNK2_STRING( "Windows Filetime (64-bit) (PT_SYSTIME)" ) );
		case 0x0048:
			return( _LIBNK2_STRING( "GUID (128-bit) (PT_CLSID)" ) );
		case 0x0102:
			return( _LIBNK2_STRING( "Binary data (PT_BINARY)" ) );
		case 0x1000:
			return( _LIBNK2_STRING( "Array of Unspecified values (PT_MV_UNSPECIFIED)" ) );
		case 0x1001:
			return( _LIBNK2_STRING( "Array of NULL values (PT_MV_NULL)" ) );
		case 0x1002:
			return( _LIBNK2_STRING( "Array of Integer 16-bit signed values (PT_MV_SHORT)" ) );
		case 0x1003:
			return( _LIBNK2_STRING( "Array of Integer 32-bit signed values (PT_MV_LONG)" ) );
		case 0x1004:
			return( _LIBNK2_STRING( "Array of Floating point single precision (32-bit) (PT_MV_FLOAT)" ) );
		case 0x1005:
			return( _LIBNK2_STRING( "Array of Floating point double precision (64-bit) (PT_MV_DOUBLE)" ) );
		case 0x1006:
			return( _LIBNK2_STRING( "Array of Currency (64-bit) values (PT_MV_CURRENCY)" ) );
		case 0x1007:
			return( _LIBNK2_STRING( "Array of Application Time (64-bit) values (PT_MV_APPTIME)" ) );
		case 0x100a:
			return( _LIBNK2_STRING( "Array of Error value (32-bit) values (PT_MV_ERROR)" ) );
		case 0x100b:
			return( _LIBNK2_STRING( "Array of Boolean (16-bit) (PT_MV_BOOLEAN))" ) );
		case 0x100d:
			return( _LIBNK2_STRING( "Array of Embedded Object values (PT_MV_OBJECT)" ) );
		case 0x1014:
			return( _LIBNK2_STRING( "Array of 64bit values (PT_MV_I8)" ) );
		case 0x101e:
			return( _LIBNK2_STRING( "Array of (extended) ASCII strings (PT_MV_STRING8)" ) );
		case 0x101f:
			return( _LIBNK2_STRING( "Array of Unicode strings (PT_MV_UNICODE)" ) );
		case 0x1040:
			return( _LIBNK2_STRING( "Array of Windows Filetime (64-bit) values (PT_MV_SYSTIME)" ) );
		case 0x1048:
			return( _LIBNK2_STRING( "Array of GUID (128-bit) values (PT_MV_CLSID)" ) );
		case 0x1102:
			return( _LIBNK2_STRING( "Array of Binary data (PT_MV_BINARY)" ) );
	};
	return( _LIBNK2_STRING( "Unknown" ) );
}

/* Retrieves a string describing the entry type
 */
const libnk2_character_t *libnk2_debug_get_entry_type_string(
                           uint16_t entry_type,
                           uint16_t value_type )
{
	switch( entry_type )
	{
		case 0x0c15:
			switch( value_type )
			{
				case 0x0003:
					return( _LIBNK2_STRING( "Recipient type (PR_RECIPIENT_TYPE)" ) );
			}
			break;

		case 0x0fff:
			switch( value_type )
			{
				case 0x0102:
					return( _LIBNK2_STRING( "Entry identifier (PR_ENTRYID)" ) );
			}
			break;

		case 0x3001:
			switch( value_type )
			{
				case 0x001f:
					return( _LIBNK2_STRING( "Display name (PR_DISPLAY_NAME)" ) );
			}
			break;

		case 0x3002:
			switch( value_type )
			{
				case 0x001f:
					return( _LIBNK2_STRING( "Address type (PR_ADDRTYPE)" ) );
			}
			break;

		case 0x3003:
			switch( value_type )
			{
				case 0x001f:
					return( _LIBNK2_STRING( "E-mail address (PR_EMAIL_ADDRESS)" ) );
			}
			break;

		case 0x300b:
			switch( value_type )
			{
				case 0x0102:
					return( _LIBNK2_STRING( "Search key (PR_SEARCH_KEY)" ) );
			}
			break;

		case 0x5ff6:
			switch( value_type )
			{
				case 0x001f:
					return( _LIBNK2_STRING( "Recipient display name (PR_RECIPIENT_DISPLAY_NAME)" ) );
			}
			break;

		case 0x5ff7:
			switch( value_type )
			{
				case 0x0102:
					return( _LIBNK2_STRING( "Recipient entry identifier (PR_RECIPIENT_ENTRYID)" ) );
			}
			break;

		case 0x5ffd:
			switch( value_type )
			{
				case 0x0003:
					return( _LIBNK2_STRING( "Recipient flags (PR_RECIPIENTS_FLAGS)" ) );
			}
			break;

		case 0x5fff:
			switch( value_type )
			{
				case 0x0003:
					return( _LIBNK2_STRING( "Recipient track status (PR_RECIPIENT_TRACKSTATUS)" ) );
			}
			break;
	};
	return( _LIBNK2_STRING( "Unknown" ) );
}

#endif

#if defined( HAVE_DEBUG_OUTPUT )

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
	if( libbfio_get_amount_of_offsets_read(
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
		if( libbfio_get_offset_read(
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


/*
 * Common input functions for the nk2tools
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
#include <types.h>

/* If libtool DLL support is enabled set LIBNK2_DLL_IMPORT
 * before including libnk2.h
 */
#if defined( _WIN32 ) && defined( DLL_EXPORT )
#define LIBNK2_DLL_IMPORT
#endif

#include <libnk2.h>

#include "notify.h"
#include "nk2common.h"
#include "nk2input.h"
#include "system_string.h"

/* Determines the codepage from an argument string
 * Returns 1 if successful or -1 on error
 */
int nk2input_determine_ascii_codepage(
     const system_character_t *argument,
     int *ascii_codepage )
{
	static char *function = "nk2input_determine_ascii_codepage";
	int result            = -1;

	if( argument == NULL )
	{
		notify_warning_printf( "%s: invalid argument string.\n",
		 function );

		return( -1 );
	}
	if( ascii_codepage == NULL )
	{
		notify_warning_printf( "%s: invalid ASCII codepage.\n",
		 function );

		return( -1 );
	}
	if( system_string_compare(
	     argument,
	     _SYSTEM_CHARACTER_T_STRING( "ascii" ),
	          4 ) == 0 )
	{
		*ascii_codepage = LIBNK2_CODEPAGE_ASCII;
		result          = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1250" ),
	          12 ) == 0 )
	{
		*ascii_codepage = LIBNK2_CODEPAGE_WINDOWS_1250;
		result          = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1251" ),
	          12 ) == 0 )
	{
		*ascii_codepage = LIBNK2_CODEPAGE_WINDOWS_1251;
		result          = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1252" ),
	          12 ) == 0 )
	{
		*ascii_codepage = LIBNK2_CODEPAGE_WINDOWS_1252;
		result          = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1253" ),
	          12 ) == 0 )
	{
		*ascii_codepage = LIBNK2_CODEPAGE_WINDOWS_1253;
		result          = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1254" ),
	          12 ) == 0 )
	{
		*ascii_codepage = LIBNK2_CODEPAGE_WINDOWS_1254;
		result          = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1255" ),
	          12 ) == 0 )
	{
		*ascii_codepage = LIBNK2_CODEPAGE_WINDOWS_1255;
		result          = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1256" ),
	          12 ) == 0 )
	{
		*ascii_codepage = LIBNK2_CODEPAGE_WINDOWS_1256;
		result          = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1257" ),
	          12 ) == 0 )
	{
		*ascii_codepage = LIBNK2_CODEPAGE_WINDOWS_1257;
		result          = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1258" ),
	          12 ) == 0 )
	{
		*ascii_codepage = LIBNK2_CODEPAGE_WINDOWS_1258;
		result          = 1;
	}
	return( result );
}

/* Determines the export format from an argument string
 * Returns 1 if successful or -1 on error
 */
int nk2input_determine_export_format(
     const system_character_t *argument,
     int *export_format )
{
	static char *function = "nk2input_determine_export_format";
	int result            = 1;

	if( argument == NULL )
	{
		notify_warning_printf( "%s: invalid argument string.\n",
		 function );

		return( -1 );
	}
	if( export_format == NULL )
	{
		notify_warning_printf( "%s: invalid export format.\n",
		 function );

		return( -1 );
	}
	if( system_string_compare(
	     argument,
	     _SYSTEM_CHARACTER_T_STRING( "all" ),
	     3 ) == 0 )
	{
		*export_format = NK2COMMON_EXPORT_FORMAT_ALL;
		result         = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "htm" ),
	          3 ) == 0 )
	{
		*export_format = NK2COMMON_EXPORT_FORMAT_HTML;
		result         = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "html" ),
	          4 ) == 0 )
	{
		*export_format = NK2COMMON_EXPORT_FORMAT_HTML;
		result         = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "rtf" ),
	          3 ) == 0 )
	{
		*export_format = NK2COMMON_EXPORT_FORMAT_RTF;
		result         = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "txt" ),
	          3 ) == 0 )
	{
		*export_format = NK2COMMON_EXPORT_FORMAT_TEXT;
		result         = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "text" ),
	          4 ) == 0 )
	{
		*export_format = NK2COMMON_EXPORT_FORMAT_TEXT;
		result         = 1;
	}
	return( result );
}


/*
 * Common output functions for the nk2tools
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

#include <errno.h>

#include <stdio.h>

#if defined( HAVE_STDARG_H )
#include <stdarg.h>
#elif defined( HAVE_VARARGS_H )
#include <varargs.h>
#else
#error No variable argument support available
#endif

#if defined( HAVE_LOCAL_LIBUNA )
#include <libuna_definitions.h>
#elif defined( HAVE_LIBUNA_H )
#include <libuna.h>
#endif

/* If libtool DLL support is enabled set LIBNK2_DLL_IMPORT
 * before including libnk2.h
 */
#if defined( _WIN32 ) && defined( DLL_EXPORT )
#define LIBNK2_DLL_IMPORT
#endif

#include <libnk2.h>

#include "error_string.h"
#include "nk2output.h"
#include "system_string.h"

/* Prints the copyright information
 */
void nk2output_copyright_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf(
	 stream,
	 "Copyright (c) 2009, Joachim Metz, Hoffmann Investigations <%s> and contributors.\n"
	 "This is free software; see the source for copying conditions. There is NO\n"
	 "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n",
	 PACKAGE_BUGREPORT );
}

/* Prints the version information
 */
void nk2output_version_fprint(
      FILE *stream,
      const char *program )
{
	if( stream == NULL )
	{
		return;
	}
	if( program == NULL )
	{
		return;
	}
        fprintf(
	 stream,
	 "%s %s (libnk2 %s",
         program,
	 LIBNK2_VERSION_STRING,
	 LIBNK2_VERSION_STRING );

	fprintf(
	 stream,
	 ", libuna %s",
	 LIBUNA_VERSION_STRING );

        fprintf(
	 stream,
	 ")\n\n" );
}

#if defined( HAVE_STDARG_H )
#define VARIABLE_ARGUMENTS_FUNCTION( function, type, argument ) \
        function( FILE *stream, type argument, ... )
#define VARIABLE_ARGUMENTS_START( argument_list, type, name ) \
        va_start( argument_list, name )
#define VARIABLE_ARGUMENTS_END( argument_list ) \
        va_end( argument_list )

#elif defined( HAVE_VARARGS_H )
#define VARIABLE_ARGUMENTS_FUNCTION( function, type, argument ) \
        function( FILE *stream, va_alist ) va_dcl
#define VARIABLE_ARGUMENTS_START( argument_list, type, name ) \
        { type name; va_start( argument_list ); name = va_arg( argument_list, type )
#define VARIABLE_ARGUMENTS_END( argument_list ) \
        va_end( argument_list ); }

#endif

void VARIABLE_ARGUMENTS_FUNCTION(
      nk2output_error_fprint,
      char *,
      format )
{
	va_list argument_list;

#if defined( HAVE_STRERROR_R ) || defined( HAVE_STRERROR )
        system_character_t *error_string = NULL;
#endif

	if( stream == NULL )
	{
		return;
	}
	VARIABLE_ARGUMENTS_START(
	 argument_list,
	 char *,
       	 format );

	vfprintf(
       	 stream,
	 format,
       	 argument_list );

	VARIABLE_ARGUMENTS_END(
       	 argument_list );

#if defined( HAVE_STRERROR_R ) || defined( HAVE_STRERROR )
	if( errno != 0 )
	{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER_T )
		error_string = error_string_wcserror(
		                errno );
#else
		error_string = error_string_strerror(
		                errno );
#endif

		if( error_string != NULL )
		{
			fprintf(
			 stream, " with error: %" PRIs_SYSTEM "",
			 error_string );

			memory_free(
			 error_string );
		}
	}
#endif
	fprintf( stream, "\n" );
}

#undef VARIABLE_ARGUMENTS_FUNCTION
#undef VARIABLE_ARGUMENTS_START
#undef VARIABLE_ARGUMENTS_END


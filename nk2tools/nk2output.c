/*
 * Common output functions for the nk2tools
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

#if defined( HAVE_LOCAL_LIBUNA )
#include <libuna_definitions.h>
#elif defined( HAVE_LIBUNA_H )
#include <libuna.h>
#endif

#if defined( HAVE_LOCAL_LIBBFIO )
#include <libbfio_definitions.h>
#elif defined( HAVE_LIBBFIO_H )
#include <libbfio.h>
#endif

#if defined( HAVE_LOCAL_LIBFDATETIME )
#include <libfdatetime_definitions.h>
#elif defined( HAVE_LIBFDATETIME_H )
#include <libfdatetime.h>
#endif

#if defined( HAVE_LOCAL_LIBFMAPI )
#include <libfmapi_definitions.h>
#elif defined( HAVE_LIBFMAPI_H )
#include <libfmapi.h>
#endif

/* If libtool DLL support is enabled set LIBNK2_DLL_IMPORT
 * before including libnk2.h
 */
#if defined( _WIN32 ) && defined( DLL_EXPORT )
#define LIBNK2_DLL_IMPORT
#endif

#include <libnk2.h>

#include <libsystem.h>

#include "nk2output.h"

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
	 "Copyright (c) 2009-2010, Joachim Metz <%s> and contributors.\n"
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
	 ", libbfio %s",
	 LIBBFIO_VERSION_STRING );

	fprintf(
	 stream,
	 ", libfdatetime %s",
	 LIBFDATETIME_VERSION_STRING );

	fprintf(
	 stream,
	 ", libfmapi %s",
	 LIBFMAPI_VERSION_STRING );

        fprintf(
	 stream,
	 ")\n\n" );
}


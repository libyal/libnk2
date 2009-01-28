/*
 * Support functions
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

#include "libnk2_definitions.h"
#include "libnk2_notify.h"
#include "libnk2_support.h"

/* Returns the library version
 */
const char *libnk2_get_version(
             void )
{
	return( (const char *) LIBNK2_VERSION_STRING );
}

/* Signals the libnk2 file to abort its current activity
 * Returns 1 if successful or -1 on error
 */
int libnk2_signal_abort(
     libnk2_file_t *file )
{
	liberror_error_t *error = NULL;
	static char *function   = "libnk2_signal_abort";

	if( file == NULL )
	{
		liberror_error_set(
		 &error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		libnk2_notify_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		return( -1 );
	}
	( (libnk2_internal_file_t *) file )->abort = 1;

	return( 1 );
}

/* Free an error and its elements
 */
void libnk2_error_free(
      libnk2_error_t **error )
{
	liberror_error_free(
	 (liberror_error_t **) error );
}

/* Prints a descriptive string of the error to the stream
 */
void libnk2_error_fprint(
      libnk2_error_t *error,
      FILE *stream )
{
	liberror_error_fprint(
	 (liberror_error_t *) error,
	 stream );
}

/* Prints a backtrace of the error to the stream
 */
void libnk2_error_backtrace_fprint(
      libnk2_error_t *error,
      FILE *stream )
{
	liberror_error_backtrace_fprint(
	 (liberror_error_t *) error,
	 stream );
}

